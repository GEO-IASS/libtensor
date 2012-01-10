#ifndef LIBTENSOR_DIRECT_BLOCK_TENSOR_H
#define LIBTENSOR_DIRECT_BLOCK_TENSOR_H

#include <libvmm/cond_map.h>
#include "../defs.h"
#include "../exception.h"
#include "../mp/default_sync_policy.h"
#include "../mp/task_i.h"
#include "../mp/task_batch.h"
#include "abs_index.h"
#include "block_map.h"
#include "direct_block_tensor_base.h"
#include "direct_block_tensor_operation.h"

namespace libtensor {

/**	\brief Direct block %tensor
	\tparam N Tensor order.
	\tparam T Tensor element type.
	\tparam Alloc Memory allocator type.
	\tparam Sync Synchronization policy

	\ingroup libtensor_core
 **/
template<size_t N, typename T, typename Alloc,
	typename Sync = default_sync_policy>
class direct_block_tensor : public direct_block_tensor_base<N, T> {
public:
	static const char *k_clazz; //!< Class name

private:
	typedef typename Sync::mutex_t mutex_t; //!< Mutex type

	class auto_lock {
	private:
		mutex_t *m_lock;
		bool m_locked;

	public:
		auto_lock(mutex_t *l) : m_lock(l), m_locked(false) {
			lock();
		}

		~auto_lock() {
			unlock();
		}

		void lock() {
			if(m_lock && !m_locked) {
				m_lock->lock();
				m_locked = true;
			}
		}

		void unlock() {
			if(m_lock && m_locked) {
				m_locked = false;
				m_lock->unlock();
			}
		}
	};

	class task : public task_i {
	private:
	    direct_block_tensor_operation<N, T> &m_op;
	    index<N> m_idx;
	    dense_tensor_i<N, T> &m_blk;

	public:
	    task(direct_block_tensor_operation<N, T> &op, const index<N> &idx,
	        dense_tensor_i<N, T> &blk) : m_op(op), m_idx(idx), m_blk(blk) { }
	    virtual ~task() { }
	    void perform(cpu_pool &cpus) throw(exception) {
	        m_op.compute_block(m_blk, m_idx, cpus);
	    }
	};

public:
	typedef direct_block_tensor_base<N,T> base_t; //!< Base class type
	typedef T element_t; //!< Tensor element type
	typedef std::map<size_t,unsigned char> map_t;
	typedef std::pair<size_t,unsigned char> pair_t;

private:
	dimensions<N> m_bidims; //!< Block %index dims
	mutex_t *m_lock; //!< Mutex lock
	block_map<N, T, Alloc> m_map; //!< Block map
	std::map<size_t, size_t> m_count; //!< Block count
	std::set<size_t> m_inprogress; //!< Computations in progress
	libvmm::cond_map<size_t, size_t> m_cond; //!< Conditionals

public:
	//!	\name Construction and destruction
	//@{

	direct_block_tensor(direct_block_tensor_operation<N, T> &op);
	virtual ~direct_block_tensor() { }

	//@}

	using direct_block_tensor_base<N, T>::get_bis;

protected:
	//!	\name Implementation of libtensor::block_tensor_i<N, T>
	//@{

	virtual bool on_req_is_zero_block(const index<N> &idx)
		throw(exception);
	virtual dense_tensor_i<N, T> &on_req_block(const index<N> &idx)
		throw(exception);
	virtual void on_ret_block(const index<N> &idx) throw(exception);
	virtual dense_tensor_i<N, T> &on_req_aux_block(const index<N> &idx)
		throw(exception);
	virtual void on_ret_aux_block(const index<N> &idx) throw(exception);
	virtual void on_req_sync_on() throw(exception);
	virtual void on_req_sync_off() throw(exception);

	//@}

	using direct_block_tensor_base<N, T>::get_op;

private:
	//! \brief Performs calculation of the given block
	void perform(const index<N>& idx) throw(exception);
};


template<size_t N, typename T, typename Alloc, typename Sync>
const char *direct_block_tensor<N, T, Alloc, Sync>::k_clazz =
	"direct_block_tensor<N, T, Alloc, Sync>";


template<size_t N, typename T, typename Alloc, typename Sync>
direct_block_tensor<N, T, Alloc, Sync>::direct_block_tensor(
	direct_block_tensor_operation<N, T> &op) :

	direct_block_tensor_base<N, T>(op),
	m_bidims(get_bis().get_block_index_dims()),
	m_lock(0) {

}


template<size_t N, typename T, typename Alloc, typename Sync>
bool direct_block_tensor<N, T, Alloc, Sync>::on_req_is_zero_block(
	const index<N> &idx) throw(exception) {

	auto_lock lock(m_lock);

	return !get_op().get_schedule().contains(idx);
}


template<size_t N, typename T, typename Alloc, typename Sync>
dense_tensor_i<N, T> &direct_block_tensor<N, T, Alloc, Sync>::on_req_block(
	const index<N> &idx) throw(exception) {

	static const char *method = "on_req_block(const index<N>&)";

	auto_lock lock(m_lock);

#ifdef LIBTENSOR_DEBUG
	if(!get_op().get_schedule().contains(idx)) {
		throw bad_parameter(g_ns, k_clazz, method, __FILE__, __LINE__,
			"idx");
	}
#endif // LIBTENSOR_DEBUG

	abs_index<N> aidx(idx, m_bidims);
	typename std::map<size_t, size_t>::iterator icnt =
		m_count.insert(std::pair<size_t, size_t>(
			aidx.get_abs_index(), 0)).first;
	bool newblock = icnt->second++ == 0;
	bool inprogress = m_inprogress.count(aidx.get_abs_index()) > 0;

	if(newblock) {
		dimensions<N> blkdims = get_op().get_bis().get_block_dims(idx);
		m_map.create(aidx.get_abs_index(), blkdims);
	}

	dense_tensor_i<N, T> &blk = m_map.get(aidx.get_abs_index());

	if(newblock) {

		std::set<size_t>::iterator i =
			m_inprogress.insert(aidx.get_abs_index()).first;
		lock.unlock();
		task t(get_op(), idx, blk);
		task_batch tb;
		tb.push(t);
		tb.wait();
		lock.lock();
		m_inprogress.erase(i);
		m_cond.signal(aidx.get_abs_index());

	} else if(inprogress) {

		libvmm::loaded_cond<size_t> cond(0);
		m_cond.insert(aidx.get_abs_index(), &cond);
		lock.unlock();
		cond.wait();
		lock.lock();
		m_cond.erase(aidx.get_abs_index(), &cond);
	}

	return blk;
}


template<size_t N, typename T, typename Alloc, typename Sync>
void direct_block_tensor<N, T, Alloc, Sync>::on_ret_block(const index<N> &idx)
	throw(exception) {

	static const char *method = "on_ret_block(const index<N>&)";

	auto_lock lock(m_lock);

	abs_index<N> aidx(idx, m_bidims);
	typename std::map<size_t, size_t>::iterator icnt =
		m_count.find(aidx.get_abs_index());
	if(icnt == m_count.end()) {
		throw bad_parameter(g_ns, k_clazz, method, __FILE__, __LINE__,
			"idx");
	}

	if(--icnt->second == 0) {
		m_map.remove(aidx.get_abs_index());
		m_count.erase(icnt);
	}
}


template<size_t N, typename T, typename Alloc, typename Sync>
dense_tensor_i<N, T> &direct_block_tensor<N, T, Alloc, Sync>::on_req_aux_block(
	const index<N> &idx) throw(exception) {

	static const char *method = "on_req_aux_block(const index<N>&)";

	throw immut_violation(g_ns, k_clazz, method, __FILE__, __LINE__,
		"invalid_req");
}


template<size_t N, typename T, typename Alloc, typename Sync>
void direct_block_tensor<N, T, Alloc, Sync>::on_ret_aux_block(
	const index<N> &idx) throw(exception) {

	static const char *method = "on_ret_aux_block(const index<N>&)";

	throw immut_violation(g_ns, k_clazz, method, __FILE__, __LINE__,
		"invalid_req");
}


template<size_t N, typename T, typename Alloc, typename Sync>
void direct_block_tensor<N, T, Alloc, Sync>::on_req_sync_on() throw(exception) {

	if(m_lock == 0) m_lock = new mutex_t;
	get_op().sync_on();
}


template<size_t N, typename T, typename Alloc, typename Sync>
void direct_block_tensor<N, T, Alloc, Sync>::on_req_sync_off()
	throw(exception) {

	delete m_lock; m_lock = 0;
	get_op().sync_off();
}


} // namespace libtensor

#endif // LIBTENSOR_DIRECT_BLOCK_TENSOR_H
