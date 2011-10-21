#ifndef LIBTENSOR_TOD_EWMULT2_H
#define LIBTENSOR_TOD_EWMULT2_H

#include "../defs.h"
#include "../timings.h"
#include "../core/tensor_i.h"
#include "loop_list_elem.h"
#include "tod_additive.h"
#include "bad_dimensions.h"

namespace libtensor {


/**	\brief General element-wise multiplication of two tensors
	\tparam N First argument's %tensor order less the number of shared
		indexes.
	\tparam M Second argument's %tensor order less the number of shared
		indexes.
	\tparam K Number of shared indexes.

	This operation computes the generalized element-wise (Hadamard) product
	of two tensors. It takes two arguments and performs the following
	$$ c_{ij\cdots mn\cdots pq\cdots} =
		a_{ij\cdots pq\cdots} b_{mn\cdots pq\cdots} $$
	Both arguments have $K > 0$ shared indexes $pq\cdots$. In addition,
	the first argument has $N \ge 0$ and the second argument has $M \ge 0$
	extra indexes that are not subject to the operation. The result
	has $N+M+K$ indexes. $N$, $M$ and $K$ are the template parameters of
	the operation.

	The arguments A and B may be given in a permuted form. In this case
	permutations should be specified upon construction. The permutations for
	A and B rearrange the indexes to the standard form: $ij\cdots pq\cdots$
	and $mn\cdots pq\cdots$, respectively. The permutation for C transforms
	the standard index ordering $ij\cdots mn\cdots pq\cdots$ to the desired
	form.

	The output tensor C specified upon calling perform() must agree in
	dimensions with the input tensors A and B taking all permutations into
	account. A and B themselves must agree in the dimensions of the shared
	indexes. Any disagreement will raise bad_dimensions.

	\sa tod_contract2

	\ingroup libtensor_tod
 **/
template<size_t N, size_t M, size_t K>
class tod_ewmult2 :
	public tod_additive<N + M + K>,
	public timings< tod_ewmult2<N, M, K> > {

public:
	static const char *k_clazz; //!< Class name

public:
	enum {
	    k_ordera = N + K, //!< Order of first argument (A)
	    k_orderb = M + K, //!< Order of second argument (B)
	    k_orderc = N + M + K //!< Order of result (C)
	};

private:
	tensor_i<k_ordera, double> &m_ta; //!< First argument (A)
	permutation<k_ordera> m_perma; //!< Permutation of first argument (A)
	tensor_i<k_orderb, double> &m_tb; //!< Second argument (B)
	permutation<k_orderb> m_permb; //!< Permutation of second argument (B)
	permutation<k_orderc> m_permc; //!< Permutation of result (C)
	double m_d; //!< Scaling coefficient
	dimensions<k_orderc> m_dimsc; //!< Result dimensions

public:
	//!	\name Construction and destruction
	//@{

	/**	\brief Initializes the operation
		\param ta First argument (A).
		\param tb Second argument (B).
		\param d Scaling coefficient.
	 **/
	tod_ewmult2(tensor_i<k_ordera, double> &ta,
		tensor_i<k_orderb, double> &tb, double d = 1.0);

	/**	\brief Initializes the operation
		\param ta First argument (A).
		\param perma Permutation of A.
		\param tb Second argument (B).
		\param permb Permutation of B.
		\param permc Permutation of result (C).
		\param d Scaling coefficient.
	 **/
	tod_ewmult2(tensor_i<k_ordera, double> &ta,
		const permutation<k_ordera> &perma,
		tensor_i<k_orderb, double> &tb,
		const permutation<k_orderb> &permb,
		const permutation<k_orderc> &permc, double d = 1.0);

	/**	\brief Virtual destructor
	 **/
	virtual ~tod_ewmult2();

	//@}


	//!	\name Implementation of tod_additive<N + M + K>
	//@{

	virtual void prefetch();
    virtual void perform(cpu_pool &cpus, bool zero, double c,
        tensor_i<k_orderc, double> &t);
	void perform(cpu_pool &cpus, tensor_i<k_orderc, double> &tc);
	void perform(cpu_pool &cpus, tensor_i<k_orderc, double> &tc, double d);

	//@}

private:
	/**	\brief Computes the dimensions of the result tensor
	 **/
	static dimensions<N + M + K> make_dimsc(
		const dimensions<k_ordera> &dimsa,
		const permutation<k_ordera> &perma,
		const dimensions<k_orderb> &dimsb,
		const permutation<k_orderb> &permb,
		const permutation<k_orderc> &permc);

};


} // namespace libtensor

#ifdef LIBTENSOR_INSTANTIATE_TEMPLATES

namespace libtensor {

    extern template class tod_ewmult2<0, 0, 1>;
    extern template class tod_ewmult2<0, 0, 2>;
    extern template class tod_ewmult2<0, 0, 3>;
    extern template class tod_ewmult2<0, 0, 4>;
    extern template class tod_ewmult2<0, 0, 5>;
    extern template class tod_ewmult2<0, 0, 6>;

    extern template class tod_ewmult2<0, 1, 1>;
    extern template class tod_ewmult2<0, 1, 2>;
    extern template class tod_ewmult2<0, 1, 3>;
    extern template class tod_ewmult2<0, 1, 4>;
    extern template class tod_ewmult2<0, 1, 5>;
    extern template class tod_ewmult2<1, 0, 1>;
    extern template class tod_ewmult2<1, 0, 2>;
    extern template class tod_ewmult2<1, 0, 3>;
    extern template class tod_ewmult2<1, 0, 4>;
    extern template class tod_ewmult2<1, 0, 5>;

    extern template class tod_ewmult2<0, 2, 1>;
    extern template class tod_ewmult2<0, 2, 2>;
    extern template class tod_ewmult2<0, 2, 3>;
    extern template class tod_ewmult2<0, 2, 4>;
    extern template class tod_ewmult2<1, 1, 1>;
    extern template class tod_ewmult2<1, 1, 2>;
    extern template class tod_ewmult2<1, 1, 3>;
    extern template class tod_ewmult2<1, 1, 4>;
    extern template class tod_ewmult2<2, 0, 1>;
    extern template class tod_ewmult2<2, 0, 2>;
    extern template class tod_ewmult2<2, 0, 3>;
    extern template class tod_ewmult2<2, 0, 4>;

    extern template class tod_ewmult2<0, 3, 1>;
    extern template class tod_ewmult2<0, 3, 2>;
    extern template class tod_ewmult2<0, 3, 3>;
    extern template class tod_ewmult2<1, 2, 1>;
    extern template class tod_ewmult2<1, 2, 2>;
    extern template class tod_ewmult2<1, 2, 3>;
    extern template class tod_ewmult2<2, 1, 1>;
    extern template class tod_ewmult2<2, 1, 2>;
    extern template class tod_ewmult2<2, 1, 3>;
    extern template class tod_ewmult2<3, 0, 1>;
    extern template class tod_ewmult2<3, 0, 2>;
    extern template class tod_ewmult2<3, 0, 3>;

    extern template class tod_ewmult2<0, 4, 1>;
    extern template class tod_ewmult2<0, 4, 2>;
    extern template class tod_ewmult2<1, 3, 1>;
    extern template class tod_ewmult2<1, 3, 2>;
    extern template class tod_ewmult2<2, 2, 1>;
    extern template class tod_ewmult2<2, 2, 2>;
    extern template class tod_ewmult2<3, 1, 1>;
    extern template class tod_ewmult2<3, 1, 2>;
    extern template class tod_ewmult2<4, 0, 1>;
    extern template class tod_ewmult2<4, 0, 2>;

    extern template class tod_ewmult2<0, 5, 1>;
    extern template class tod_ewmult2<1, 4, 1>;
    extern template class tod_ewmult2<2, 3, 1>;
    extern template class tod_ewmult2<3, 2, 1>;
    extern template class tod_ewmult2<4, 1, 1>;
    extern template class tod_ewmult2<5, 0, 1>;

} // namespace libtensor

#else // LIBTENSOR_INSTANTIATE_TEMPLATES
#include "tod_ewmult2_impl.h"
#endif // LIBTENSOR_INSTANTIATE_TEMPLATES

#endif // LIBTENSOR_TOD_EWMULT2_H
