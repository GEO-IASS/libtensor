#ifndef LIBTENSOR_BTOD_DIRSUM_H
#define LIBTENSOR_BTOD_DIRSUM_H

#include <map>
#include "../defs.h"
#include "../timings.h"
#include "../core/block_tensor_i.h"
#include "../core/orbit.h"
#include "../core/orbit_list.h"
#include "additive_btod.h"

namespace libtensor {

template<size_t N, size_t M>
class btod_dirsum_symmetry_builder_base;

template<size_t N, size_t M>
class btod_dirsum_symmetry_builder;

template<size_t N>
class btod_dirsum_symmetry_builder<N, N>;

template<size_t N, size_t M>
class btod_dirsum_clazz {
public:
	static const char *k_clazz;
};


/**	\brief Computes the direct sum of two block tensors
	\tparam N Order of the first %tensor.
	\tparam M Order of the second %tensor.

	Given two tensors \f$ a_{ij\cdots} \f$ and \f$ b_{mn\cdots} \f$,
	the operation computes
	\f$ c_{ij\cdots mn\cdots} = k_a a_{ij\cdots} + k_b b_{mn\cdots} \f$.

	The order of %tensor indexes in the result can be specified using
	a permutation.

	\ingroup libtensor_btod
 **/
template<size_t N, size_t M>
class btod_dirsum :
	public additive_btod<N + M>,
	public timings< btod_dirsum<N, M> > {

public:
	static const char *k_clazz; //!< Class name

public:
	enum {
	    k_ordera = N, //!< Order of first argument (A)
	    k_orderb = M, //!< Order of second argument (B)
	    k_orderc = N + M //!< Order of result (C)
	};

private:
	struct schrec {
		size_t absidxa, absidxb;
		bool zeroa, zerob;
		double ka, kb;
		permutation<k_orderc> permc;
	};
	typedef std::map<size_t, schrec> schedule_t;

private:
	block_tensor_i<k_ordera, double> &m_bta; //!< First %tensor (A)
	block_tensor_i<k_orderb, double> &m_btb; //!< Second %tensor (B)
	double m_ka; //!< Coefficient A
	double m_kb; //!< Coefficient B
	permutation<k_orderc> m_permc; //!< Permutation of the result
	btod_dirsum_symmetry_builder<k_ordera, k_orderb>
		m_sym_bld; //!< Builder for result symmetry and block index space
	dimensions<k_ordera> m_bidimsa; //!< Block %index dims of A
	dimensions<k_orderb> m_bidimsb; //!< Block %index dims of B
	dimensions<k_orderc> m_bidimsc; //!< Block %index dims of the result
	schedule_t m_op_sch; //!< Direct sum schedule
	assignment_schedule<k_orderc, double> m_sch; //!< Assignment schedule

public:
	/**	\brief Initializes the operation
	 **/
	btod_dirsum(block_tensor_i<k_ordera, double> &bta, double ka,
		block_tensor_i<k_orderb, double> &btb, double kb);

	/**	\brief Initializes the operation
	 **/
	btod_dirsum(block_tensor_i<k_ordera, double> &bta, double ka,
		block_tensor_i<k_orderb, double> &btb, double kb,
		const permutation<k_orderc> &permc);

	/**	\brief Virtual destructor
	 **/
	virtual ~btod_dirsum() { }

	virtual const block_index_space<N + M> &get_bis() const {
		return m_sym_bld.get_bis();
	}

	virtual const symmetry<N + M, double> &get_symmetry() const {
		return m_sym_bld.get_symmetry();
	}

	virtual const assignment_schedule<N + M, double> &get_schedule() const {
		return m_sch;
	}

	virtual void sync_on();
	virtual void sync_off();

	virtual void compute_block(bool zero, tensor_i<N + M, double> &blk,
		const index<N + M> &i, const transf<N + M, double> &tr,
		double c, cpu_pool &cpus);

	using additive_btod<N + M>::perform;

private:
	void make_schedule();
	void make_schedule(const orbit<k_ordera, double> &oa, bool zeroa,
		const orbit<k_orderb, double> &ob, bool zerob,
		const orbit_list<k_orderc, double> &olc);

	void compute_block(tensor_i<N + M, double> &blkc,
		const schrec &rec, const transf<N + M, double> &trc,
		bool zeroc, double kc, cpu_pool &cpus);

	void do_block_dirsum(block_tensor_ctrl<k_ordera, double> &ctrla,
		block_tensor_ctrl<k_orderb, double> &ctrlb,
		tensor_i<k_orderc, double> &blkc, double kc,
		const index<k_ordera> &ia, double ka,
		const index<k_orderb> &ib, double kb,
		const permutation<k_orderc> &permc, bool zero);

	void do_block_scatter_a(block_tensor_ctrl<k_ordera, double> &ctrla,
		tensor_i<k_orderc, double> &blkc, double kc,
		const index<k_ordera> &ia, double ka,
		const permutation<k_orderc> permc, bool zero);

	void do_block_scatter_b(block_tensor_ctrl<k_orderb, double> &ctrlb,
		tensor_i<k_orderc, double> &blkc, double kc,
		const index<k_orderb> &ib, double kb,
		const permutation<k_orderc> permc, bool zero);

};

template<size_t N, size_t M>
class btod_dirsum_symmetry_builder_base {
private:
	block_index_space<N + M> m_bis;
	symmetry<N + M, double> m_sym;

public:
	btod_dirsum_symmetry_builder_base(
			const block_index_space<N> &bisa,
			const block_index_space<M> &bisb,
			const permutation<N + M> &permc) :
		m_bis(make_bis(bisa, bisb, permc)), m_sym(m_bis) { }

	const block_index_space<N + M> &get_bis() const {
		return m_bis;
	}

	const symmetry<N + M, double> &get_symmetry() const {
		return m_sym;
	}

protected:

	symmetry<N + M, double> &get_sym() {
		return m_sym;
	}

	void make_symmetry(
			block_tensor_i<N, double> &bta,
			block_tensor_i<M, double> &btb,
			const permutation<N + M> &permc);

	static block_index_space<N + M> make_bis(
			const block_index_space<N> &bisa,
			const block_index_space<M> &bisb,
			const permutation<N + M> &permc);
};

/** \brief Builds the %symmetry and block %index space for btod_dirsum

 	\sa btod_dirsum<N, M>

 	\ingroup libtensor_btod
 **/
template<size_t N, size_t M>
class btod_dirsum_symmetry_builder :
	public btod_dirsum_symmetry_builder_base<N, M> {
public:
	btod_dirsum_symmetry_builder(
			block_tensor_i<N, double> &bta, double ka,
			block_tensor_i<M, double> &btb, double kb,
			const permutation<N + M> &permc);
};

/** \brief Builds the %symmetry and block %index space for btod_dirsum
 	 	 (specialized for same-order A and B)

 	\sa btod_dirsum<N, M>

 	\ingroup libtensor_btod
 **/
template<size_t N>
class btod_dirsum_symmetry_builder<N, N> :
	public btod_dirsum_symmetry_builder_base<N, N> {
public:
	btod_dirsum_symmetry_builder(
			block_tensor_i<N, double> &bta, double ka,
			block_tensor_i<N, double> &btb, double kb,
			const permutation<N + N> &permc);

private:
	void make_symmetry(
			block_tensor_i<N, double> &bta, double ka,
			block_tensor_i<N, double> &btb, double kb,
			const permutation<N + N> &permc);
};

} // namespace libtensor

#ifdef LIBTENSOR_INSTANTIATE_TEMPLATES

namespace libtensor {

    extern template class btod_dirsum<1, 1>;
    extern template class btod_dirsum<1, 2>;
    extern template class btod_dirsum<1, 3>;
    extern template class btod_dirsum<1, 4>;
    extern template class btod_dirsum<1, 5>;
    extern template class btod_dirsum<2, 1>;
    extern template class btod_dirsum<2, 2>;
    extern template class btod_dirsum<2, 3>;
    extern template class btod_dirsum<2, 4>;
    extern template class btod_dirsum<3, 1>;
    extern template class btod_dirsum<3, 2>;
    extern template class btod_dirsum<3, 3>;
    extern template class btod_dirsum<4, 1>;
    extern template class btod_dirsum<4, 2>;
    extern template class btod_dirsum<5, 1>;

} // namespace libtensor

#else // LIBTENSOR_INSTANTIATE_TEMPLATES
#include "btod_dirsum_impl.h"
#endif // LIBTENSOR_INSTANTIATE_TEMPLATES



#endif // LIBTENOSR_BTOD_DIRSUM_H
