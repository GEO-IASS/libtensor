#ifndef LIBTENSOR_LABELED_BTENSOR_EXPR_DIAG_EVAL_FUNCTOR_H
#define LIBTENSOR_LABELED_BTENSOR_EXPR_DIAG_EVAL_FUNCTOR_H

#include <libtensor/block_tensor/btod/btod_diag.h>
#include "../expr/direct_eval.h"
#include "diag_core.h"
#include "diag_subexpr_label_builder.h"
#include "diag_params_builder.h"

namespace libtensor {
namespace labeled_btensor_expr {


/** \brief Functor for evaluating the diagonal

    \ingroup libtensor_btensor_expr
 **/
template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
class diag_eval_functor {
public:
    static const char *k_clazz; //!< Class name
    static const size_t k_ordera = N; //!< Order of RHS
    static const size_t k_orderb = N - M + 1; //!< Order of LHS

    //!    Expression core type
    typedef diag_core<N, M, T, E1> core_t;

    //!    Expression type
    typedef expr<k_orderb, T, core_t> expression_t;

    //!    Expression core type of A
    typedef E1 core_a_t;

    //!    Direct evaluator type of A
    typedef direct_eval<k_ordera, T, core_a_t> eval_a_t;

    //!    Sub-expression labels
    typedef diag_subexpr_label_builder<N, M> subexpr_label_t;

private:
    eval_a_t m_eval_a; //!< Direct evaluator for the sub-expression
    permutation<k_ordera> m_invperm_a;
    diag_params_builder<N, M> m_params_bld; //!< Parameters builder
    btod_diag<N, M> *m_op; //!< Diagonal extraction operation
    arg<k_orderb, T, oper_tag> *m_arg; //!< Composed operation argument

public:
    diag_eval_functor(expression_t &expr,
        const subexpr_label_t &labels_a,
        const letter_expr<k_orderb> &label_b);

    ~diag_eval_functor();

    void evaluate();

    void clean();

    arg<N - M + 1, T, oper_tag> get_arg() const { return *m_arg; }

private:
    void create_arg();
    void destroy_arg();

};


template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
const char *diag_eval_functor<N, M, T, E1, NT1, NO1>::k_clazz =
    "diag_eval_functor<N, M, T, E1, NT1, NO1>";


template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
diag_eval_functor<N, M, T, E1, NT1, NO1>::diag_eval_functor(
    expression_t &expr, const subexpr_label_t &label_a,
    const letter_expr<k_orderb> &label_b) :

    m_eval_a(expr.get_core().get_sub_expr(), label_a.get_label()),
    m_params_bld(label_a.get_label(), m_invperm_a, label_b,
        expr.get_core().get_diag_letter(),
        expr.get_core().get_diag_label()),
    m_op(0), m_arg(0) {

}


template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
diag_eval_functor<N, M, T, E1, NT1, NO1>::~diag_eval_functor() {

    destroy_arg();
}


template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
void diag_eval_functor<N, M, T, E1, NT1, NO1>::evaluate() {

    m_eval_a.evaluate();
    create_arg();
}


template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
void diag_eval_functor<N, M, T, E1, NT1, NO1>::clean() {

    destroy_arg();
    m_eval_a.clean();
}


template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
void diag_eval_functor<N, M, T, E1, NT1, NO1>::create_arg() {

    destroy_arg();
    m_op = new btod_diag<N, M>(m_eval_a.get_btensor(),
        m_params_bld.get_mask(), m_params_bld.get_perm());
    m_arg = new arg<k_orderb, T, oper_tag>(*m_op, 1.0);
}


template<size_t N, size_t M, typename T, typename E1, size_t NT1, size_t NO1>
void diag_eval_functor<N, M, T, E1, NT1, NO1>::destroy_arg() {

    delete m_arg; m_arg = 0;
    delete m_op; m_op = 0;
}


} // namespace labeled_btensor_expr
} // namespace libtensor

// Template specializations
#include "diag_eval_functor_10.h"

#endif // LIBTENSOR_LABELED_BTENSOR_EXPR_DIAG_EVAL_FUNCTOR_H
