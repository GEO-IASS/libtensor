#ifndef LIBTENSOR_EXPR_BTENSOR_H
#define LIBTENSOR_EXPR_BTENSOR_H

#include <libtensor/core/allocator.h>
#include <libtensor/core/tensor_transf_double.h>
#include <libtensor/core/tensor_transf_complex_double.h>
#include <libtensor/block_tensor/block_tensor.h>
#include <libtensor/expr/dag/node_assign.h>
#include <libtensor/expr/dag/expr_tree.h>
#include <libtensor/expr/dag/node_transform.h>
#include <libtensor/expr/iface/node_ident_any_tensor.h>
#include <libtensor/expr/iface/expr_lhs.h>
#include <libtensor/expr/iface/labeled_lhs_rhs.h>
#include <libtensor/expr/bispace/bispace.h>
#include "btensor_i.h"
#include "eval_btensor.h"

namespace libtensor {
namespace expr {


/** \brief Block tensor

    \ingroup libtensor_expr_btensor
 **/
template<size_t N, typename T = double>
class btensor :
    public btensor_i<N, T>,
    public expr_lhs<N, T>,
    virtual public block_tensor< N, T, allocator<T> > {

public:
    btensor(const bispace<N> &bi) :
        block_tensor< N, T, allocator<T> >(bi.get_bis())
    { }

    btensor(const block_index_space<N> &bis) :
        block_tensor< N, T, allocator<T> >(bis)
    { }

    virtual ~btensor() { }

    /** \brief Attaches a letter label to btensor
     **/
    labeled_lhs_rhs<N, T> operator()(const label<N> &label) {
        return labeled_lhs_rhs<N, T>(*this, label,
            any_tensor<N, T>::make_rhs(label));
    }

    /** \brief Computes an expression and assigns it to this tensor
     **/
    virtual void assign(const expr_rhs<N, T> &rhs, const label<N> &label);

    /** \brief Computes an expression and adds it to this tensor
     **/
    virtual void assign_add(const expr_rhs<N, T> &rhs, const label<N> &label);

    /** \brief Converts any_tensor to btensor
     **/
    static btensor<N, T> &from_any_tensor(any_tensor<N, T> &t);

};


/** \brief Complex block tensor

    \ingroup libtensor_expr_btensor
 **/
template<size_t N, typename T>
class btensor< N, std::complex<T> > :
    public btensor_i< N, std::complex<T> >,
    public expr_lhs< N, std::complex<T> > {

private:
    btensor<N, T> m_re; //!< Real part
    btensor<N, T> m_im; //!< Imaginary part

public:
    btensor(const bispace<N> &bi) :
        m_re(bi.get_bis()), m_im(bi.get_bis())
    { }

    btensor(const block_index_space<N> &bis) :
        m_re(bis), m_im(bis)
    { }

    virtual ~btensor() { }

    /** \brief Attaches a letter label to btensor
     **/
    labeled_lhs_rhs< N, std::complex<T> > operator()(const label<N> &label) {
        return labeled_lhs_rhs< N, std::complex<T> >(*this, label,
            any_tensor< N, std::complex<T> >::make_rhs(label));
    }

    /** \brief Computes an expression and assigns it to this tensor
     **/
    virtual void assign(
        const expr_rhs< N, std::complex<T> > &rhs, const label<N> &label);

    /** \brief Computes an expression and adds it to this tensor
     **/
    virtual void assign_add(
        const expr_rhs< N, std::complex<T> > &rhs, const label<N> &label);

    /** \brief Converts any_tensor to btensor
     **/
    static btensor< N, std::complex<T> > &from_any_tensor(
        any_tensor< N, std::complex<T> > &t);

};


template<size_t N, typename T>
void btensor<N, T>::assign(const expr_rhs<N, T> &rhs,
    const label<N> &label) {

    node_assign n1(N, false);
    expr_tree e(n1);
    expr_tree::node_id_t id = e.get_root();
    node_ident_any_tensor<N, T> n2(*this);
    e.add(id, n2);

    permutation<N> px = label.permutation_of(rhs.get_label());
    if (! px.is_identity()) {
        std::vector<size_t> perm(N);
        for(size_t i = 0; i < N; i++) perm[i] = px[i];

        node_transform<T> n3(perm, scalar_transf<T>());
        id = e.add(id, n3);
    }
    e.add(id, rhs.get_expr());

    eval_btensor<T>().evaluate(e);
}


template<size_t N, typename T>
void btensor<N, T>::assign_add(const expr_rhs<N, T> &rhs,
    const label<N> &label) {

    node_assign n1(N, true);
    expr_tree e(n1);
    expr_tree::node_id_t id = e.get_root();
    node_ident_any_tensor<N, T> n2(*this);
    e.add(id, n2);

    permutation<N> px = label.permutation_of(rhs.get_label());
    if (! px.is_identity()) {
        std::vector<size_t> perm(N);
        for(size_t i = 0; i < N; i++) perm[i] = px[i];

        node_transform<T> n3(perm, scalar_transf<T>());
        id = e.add(id, n3);
    }
    e.add(id, rhs.get_expr());

    eval_btensor<T>().evaluate(e);
}


template<size_t N, typename T>
btensor<N, T> &btensor<N, T>::from_any_tensor(any_tensor<N, T> &t) {

    return dynamic_cast< btensor<N, T>& >(
        t.template get_tensor< btensor_i<N, T> >());
}


template<size_t N, typename T>
void btensor< N, std::complex<T> >::assign(
    const expr_rhs< N, std::complex<T> > &rhs, const label<N> &label) {

    node_assign n1(N, false);
    expr_tree e(n1);
    expr_tree::node_id_t id = e.get_root();
    node_ident_any_tensor< N, std::complex<T> > n2(*this);
    e.add(id, n2);

    permutation<N> px = label.permutation_of(rhs.get_label());
    if (! px.is_identity()) {
        std::vector<size_t> perm(N);
        for(size_t i = 0; i < N; i++) perm[i] = px[i];

        node_transform< std::complex<T> > n3(perm,
            scalar_transf< std::complex<T> >());
        id = e.add(id, n3);
    }
    e.add(id, rhs.get_expr());

    eval_btensor< std::complex<T> >().evaluate(e);
}


template<size_t N, typename T>
void btensor< N, std::complex<T> >::assign_add(
    const expr_rhs< N, std::complex<T> > &rhs,
    const label<N> &label) {

    node_assign n1(N, true);
    expr_tree e(n1);
    expr_tree::node_id_t id = e.get_root();
    node_ident_any_tensor< N, std::complex<T> > n2(*this);
    e.add(id, n2);

    permutation<N> px = label.permutation_of(rhs.get_label());
    if (! px.is_identity()) {
        std::vector<size_t> perm(N);
        for(size_t i = 0; i < N; i++) perm[i] = px[i];

        node_transform< std::complex<T> > n3(perm,
            scalar_transf< std::complex<T> >());
        id = e.add(id, n3);
    }
    e.add(id, rhs.get_expr());

    eval_btensor< std::complex<T> >().evaluate(e);
}


template<size_t N, typename T>
btensor< N, std::complex<T> > &btensor< N, std::complex<T> >::from_any_tensor(
    any_tensor< N, std::complex<T> > &t) {

    return dynamic_cast< btensor< N, std::complex<T> >& >(
        t.template get_tensor< btensor_i< N, std::complex<T> > >());
}


} // namespace expr
} // namespace libtensor


namespace libtensor {

using expr::btensor;

} // namespace libtensor

#endif // LIBTENSOR_EXPR_BTENSOR_H
