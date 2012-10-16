#ifndef LIBTENSOR_TOD_DIRSUM_H
#define LIBTENSOR_TOD_DIRSUM_H

#include <list>
#include <libtensor/timings.h>
#include <libtensor/core/noncopyable.h>
#include <libtensor/core/scalar_transf_double.h>
#include <libtensor/core/tensor_transf.h>
#include "dense_tensor_i.h"

namespace libtensor {


/** \brief Computes the direct sum of two tensors
    \tparam N Order of the first %tensor.
    \tparam M Order of the second %tensor.

    Given two tensors \f$ a_{ij\cdots} \f$ and \f$ b_{mn\cdots} \f$,
    the operation computes
    \f$ c_{ij\cdots mn\cdots} = k_a a_{ij\cdots} + k_b b_{mn\cdots} \f$.

    The order of %tensor indexes in the result can be specified using
    a permutation.

    \ingroup libtensor_dense_tensor_tod
 **/
template<size_t N, size_t M>
class tod_dirsum : public timings< tod_dirsum<N, M> >, public noncopyable {
public:
    static const char *k_clazz; //!< Class name

public:
    enum {
        k_ordera = N, //!< Order of first argument (A)
        k_orderb = M, //!< Order of second argument (B)
        k_orderc = N + M //!< Order of result (C)
    };

    typedef tensor_transf<k_orderc, double> tensor_transf_type;

private:
    dense_tensor_rd_i<k_ordera, double> &m_ta; //!< First %tensor (A)
    dense_tensor_rd_i<k_orderb, double> &m_tb; //!< Second %tensor (B)
    double m_ka; //!< Scaling coefficient of A
    double m_kb; //!< Scaling coefficient of B
    double m_c; //!< Scaling coefficient of result (C)
    permutation<k_orderc> m_permc; //!< Permutation of result
    dimensions<k_orderc> m_dimsc; //!< Dimensions of the result

public:
    /** \brief Initializes the operation
        \param ta First input tensor
        \param ka Scalar transformation applied to ta
        \param tb Second input tensor
        \param kb Scalar transformation applied to tb
        \param trc Tensor transformation applied to result
     **/
    tod_dirsum(
            dense_tensor_rd_i<k_ordera, double> &ta,
            const scalar_transf<double> &ka,
            dense_tensor_rd_i<k_orderb, double> &tb,
            const scalar_transf<double> &kb,
            const tensor_transf_type &trc = tensor_transf_type());

    /** \brief Initializes the operation
     **/
    tod_dirsum(dense_tensor_rd_i<k_ordera, double> &ta, double ka,
        dense_tensor_rd_i<k_orderb, double> &tb, double kb);

    /** \brief Initializes the operation
     **/
    tod_dirsum(dense_tensor_rd_i<k_ordera, double> &ta, double ka,
        dense_tensor_rd_i<k_orderb, double> &tb, double kb,
        const permutation<k_orderc> &permc);

    /** \brief Performs the operation
        \param zero Zero the output array before running the operation.
        \param d Scaling coefficient for the result.
        \param tc Output tensor.
     **/
    void perform(bool zero, dense_tensor_wr_i<k_orderc, double> &tc);

private:
    static dimensions<N + M> mk_dimsc(dense_tensor_rd_i<k_ordera, double> &ta,
        dense_tensor_rd_i<k_orderb, double> &tb);
};


} // namespace libtensor

#endif // LIBTENOSR_TOD_DIRSUM_H

