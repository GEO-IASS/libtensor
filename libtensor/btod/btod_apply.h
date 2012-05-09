#ifndef LIBTENSOR_BTOD_APPLY_H
#define LIBTENSOR_BTOD_APPLY_H

#include <libtensor/core/allocator.h>
#include <libtensor/block_tensor/btod/btod_traits.h>
#include <libtensor/block_tensor/bto/bto_apply.h>
#include <libtensor/block_tensor/bto/impl/bto_apply_impl.h>
#include <libtensor/dense_tensor/tod_apply.h>

namespace libtensor {


template<typename Functor, typename Alloc>
struct btod_apply_traits : public bto_traits<double> {

    template<size_t N> struct tensor_type {
        typedef dense_tensor<N, double, Alloc> type;
    };

    typedef Functor functor_type;

    template<size_t N> struct to_apply_type {
        typedef tod_apply<N, Functor> type;
    };

    static double zero() { return 0.0; }
};


template<size_t N, typename Functor, typename Alloc = std_allocator<double> >
class btod_apply : public bto_apply<N, btod_apply_traits<Functor, Alloc> > {
private:
    typedef bto_apply<N, btod_apply_traits<Functor, Alloc> > bto_apply_t;
    typedef typename bto_apply_t::scalar_tr_t scalar_tr_t;

public:
    btod_apply(block_tensor_i<N, double> &bta,
            const Functor &fn, double c = 1.0) :
        bto_apply_t(bta, fn, scalar_tr_t(c)) {
    }

    btod_apply(block_tensor_i<N, double> &bta, const Functor &fn,
            const permutation<N> &p, double c = 1.0) :
        bto_apply_t(bta, fn, p, scalar_tr_t(c)) {
    }

    virtual ~btod_apply() { }

private:
    btod_apply(const btod_apply<N, Functor, Alloc>&);
    btod_apply<N, Functor, Alloc> &
    operator=(const btod_apply<N, Functor, Alloc>&);
};


} // namespace libtensor

#endif // LIBTENSOR_BTOD_APPLY_H
from forbidden input %tensor blocks. Forbidden
	%tensor blocks are then treated as if they where zero.

	\ingroup libtensor_btod
 **/
template<size_t N, typename Functor, typename Alloc = std_allocator<double> >
class btod_apply :
	public additive_btod<N>,
	public timings< btod_apply<N, Functor, Alloc> > {
public:
	static const char *k_clazz; //!< Class name

private:
	Functor m_fn; //!< Functor to apply to each element
	block_tensor_i<N, double> &m_bta; //!< Source block %tensor
	permutation<N> m_perm; //!< Permutation
	double m_c; //!< Scaling coefficient
	block_index_space<N> m_bis; //!< Block %index space of output
	dimensions<N> m_bidims; //!< Block %index dimensions
	symmetry<N, double> m_sym; //!< Symmetry of output
	assignment_schedule<N, double> m_sch;

public:
	//!	\name Construction and destruction
	//@{

	/**	\brief Initializes the element-wise operation
		\param bt Source block %tensor.
		\param f Functor instance.
		\param c Scaling coefficient.
	 **/
	btod_apply(block_tensor_i<N, double> &bta,
			const Functor &fn, double c = 1.0);

	/**	\brief Initializes the permuted element-wise operation
		\param bt Source block %tensor.
		\param f Functor instance.
		\param p Permutation.
		\param c Scaling coefficient.
	 **/
	btod_apply(block_tensor_i<N, double> &bta,
			const Functor &fn, const permutation<N> &p, double c = 1.0);

	/**	\brief Virtual destructor
	 **/
	virtual ~btod_apply() { }
	//@}

	//!	\name Implementation of
	//!		libtensor::direct_block_tensor_operation<N, double>
	//@{
	virtual const block_index_space<N> &get_bis() const {
		return m_bis;
	}

	virtual const symmetry<N, double> &get_symmetry() const {
		return m_sym;
	}

	using additive_btod<N>::perform;

	virtual void sync_on();
	virtual void sync_off();

	//@}

	//!	\name Implementation of libtensor::btod_additive<N>
	//@{
	virtual const assignment_schedule<N, double> &get_schedule() const {
		return m_sch;
	}
	//@}

protected:
	virtual void compute_block(bool zero, tensor_i<N, double> &blk,
		const index<N> &ib, const transf<N, double> &tr, double c,
		cpu_pool &cpus);

private:
	static block_index_space<N> mk_bis(const block_index_space<N> &bis,
		const permutation<N> &perm);
	void make_schedule();

private:
	btod_apply(const btod_apply<N, Functor>&);
	btod_apply<N, Functor> &operator=(const btod_apply<N, Functor>&);

};

template<size_t N, typename Functor, typename Alloc>
const char *btod_apply<N, Functor, Alloc>::k_clazz =
		"btod_apply<N, Functor, Alloc>";


template<size_t N, typename Functor, typename Alloc>
btod_apply<N, Functor, Alloc>::btod_apply(
		block_tensor_i<N, double> &bta, const Functor &fn, double c) :

	m_bta(bta), m_fn(fn), m_c(c), m_bis(m_bta.get_bis()),
	m_bidims(m_bis.get_block_index_dims()), m_sym(m_bis), m_sch(m_bidims) {

	block_tensor_ctrl<N, double> ctrla(m_bta);
	so_apply<N, double>(ctrla.req_const_symmetry(),
			m_perm, m_fn.is_asym(), m_fn.sign()).perform(m_sym);
	make_schedule();
}


template<size_t N, typename Functor, typename Alloc>
btod_apply<N, Functor, Alloc>::btod_apply(block_tensor_i<N, double> &bta,
		const Functor &fn, const permutation<N> &p, double c) :

		m_bta(bta), m_fn(fn), m_perm(p), m_c(c),
		m_bis(mk_bis(m_bta.get_bis(), m_perm)),
		m_bidims(m_bis.get_block_index_dims()), m_sym(m_bis), m_sch(m_bidims) {

	block_tensor_ctrl<N, double> ctrla(m_bta);
	so_apply<N, double>(ctrla.req_const_symmetry(),
			m_perm, m_fn.is_asym(), m_fn.sign()).perform(m_sym);
	make_schedule();
}


template<size_t N, typename Functor, typename Alloc>
void btod_apply<N, Functor, Alloc>::sync_on() {

	block_tensor_ctrl<N, double> ctrla(m_bta);
	ctrla.req_sync_on();
}


template<size_t N, typename Functor, typename Alloc>
void btod_apply<N, Functor, Alloc>::sync_off() {

	block_tensor_ctrl<N, double> ctrla(m_bta);
	ctrla.req_sync_off();
}

/*
template<size_t N, typename Functor, typename Alloc>
void btod_apply<N, Functor, Alloc>::compute_block(
		tensor_i<N, double> &blk, const index<N> &ib) {

	block_tensor_ctrl<N, double> ctrla(m_bta);
	dimensions<N> bidimsa = m_bta.get_bis().get_block_index_dims();

	permutation<N> pinv(m_perm, true);

	//	Corresponding index in A
	index<N> ia(ib);
	ia.permute(pinv);

	// Find the orbit the index belongs to
	orbit<N, double> oa(ctrla.req_const_symmetry(), ia);
	// If the orbit of A is not allowed, we assume it all elements are 0.0
	if (! oa.is_allowed()) {
		tod_set<N>(m_fn(0.0)).perform(blk);
		return;
	}
	//	Find the canonical index in A
	abs_index<N> acia(oa.get_abs_canonical_index(), bidimsa);

	//	Transformation for block from canonical A to B
	transf<N, double> tra(oa.get_transf(ia));
	tra.permute(m_perm);
	tra.scale(m_c);

	if(!ctrla.req_is_zero_block(acia.get_index())) {
		tensor_i<N, double> &blka = ctrla.req_block(acia.get_index());
		tod_apply<N, Functor>(blka, m_fn,
				tra.get_perm(), tra.get_coeff()).perform(blk);
		ctrla.ret_block(acia.get_index());
	} else {
		tod_set<N>(m_fn(0.0)).perform(blk);
	}
}*/


template<size_t N, typename Functor, typename Alloc>
void btod_apply<N, Functor, Alloc>::compute_block(bool zero,
    tensor_i<N, double> &blk, const index<N> &ib, const transf<N, double> &tr,
    double c, cpu_pool &cpus) {

	static const char *method =
			"compute_block(bool, tensor_i<N, double> &, const index<N> &, "
			"const transf<N, double> &, double, cpu_pool&)";

	if(zero) tod_set<N>().perform(cpus, blk);

	block_tensor_ctrl<N, double> ctrla(m_bta);
	dimensions<N> bidimsa = m_bta.get_bis().get_block_index_dims();

	permutation<N> pinv(m_perm, true);

	//	Corresponding index in A
	index<N> ia(ib);
	ia.permute(pinv);

	// Find the orbit the index belongs to
	orbit<N, double> oa(ctrla.req_const_symmetry(), ia);

	// If the orbit of A is not allowed, we assume it all elements are 0.0
	if (! oa.is_allowed()) {
		double val = m_fn(0.0) * c;
		if (val != 0.0) {
			tensor<N, double, Alloc> tblk(blk.get_dims());
			tod_set<N>(val).perform(cpus, tblk);
			tod_copy<N>(tblk).perform(cpus, false, 1.0, blk);
		}
		return;
	}

	//	Find the canonical index in A
	abs_index<N> acia(oa.get_abs_canonical_index(), bidimsa);

	//	Transformation for block from canonical A to B
	transf<N, double> tra(oa.get_transf(ia));
	tra.permute(m_perm);
	tra.scale(m_c);
	tra.transform(tr);

	if(! ctrla.req_is_zero_block(acia.get_index())) {
		tensor_i<N, double> &blka = ctrla.req_block(acia.get_index());
		tod_apply<N, Functor>(blka, m_fn,
				tra.get_perm(), tra.get_coeff()).perform(cpus, false, c, blk);
		ctrla.ret_block(acia.get_index());
	}
	else {
		double val = m_fn(0.0) * c * tra.get_coeff();
		if (val != 0.0) {
			tensor<N, double, Alloc> tblk(blk.get_dims());
			tod_set<N>(val).perform(cpus, tblk);
			tod_copy<N>(tblk).perform(cpus, false, 1.0, blk);
		}
	}
}


template<size_t N, typename Functor, typename Alloc>
void btod_apply<N, Functor, Alloc>::make_schedule() {

	block_tensor_ctrl<N, double> ctrla(m_bta);
	dimensions<N> bidimsa = m_bta.get_bis().get_block_index_dims();

	bool is_zero = (m_fn(0.0) == 0.0);
	permutation<N> pinv(m_perm, ! m_perm.is_identity());

	orbit_list<N, double> ol(m_sym);
	for(typename orbit_list<N, double>::iterator io = ol.begin();
			io != ol.end(); io++) {

		// If m_fn(0.0) yields 0.0 only non-zero blocks of tensor A need to
		// be considered
		if (is_zero) {
			index<N> ia(ol.get_index(io)); ia.permute(pinv);

			orbit<N, double> oa(ctrla.req_const_symmetry(), ia);
			if (! oa.is_allowed()) continue;

			abs_index<N> acia(oa.get_abs_canonical_index(), bidimsa);
			if (ctrla.req_is_zero_block(acia.get_index())) continue;

			m_sch.insert(ol.get_abs_index(io));
		}
		else {
			m_sch.insert(ol.get_abs_index(io));
		}
	}
}


template<size_t N, typename Functor, typename Alloc>
block_index_space<N>
btod_apply<N, Functor, Alloc>::mk_bis(const block_index_space<N> &bis,
		const permutation<N> &perm) {

	block_index_space<N> bis1(bis);
	bis1.permute(perm);
	return bis1;
}



} // namespace libtensor

#endif // LIBTENSOR_BTOD_APPLY_H
