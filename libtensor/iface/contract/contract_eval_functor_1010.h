#ifndef LIBTENSOR_LABELED_BTENSOR_EXPR_CONTRACT_EVAL_FUNCTOR_1010_H
#define LIBTENSOR_LABELED_BTENSOR_EXPR_CONTRACT_EVAL_FUNCTOR_1010_H

namespace libtensor {
namespace labeled_btensor_expr {


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT1, size_t NO1, size_t NT2, size_t NO2>
class contract_eval_functor;


/** \brief Functor for evaluating contractions (tensor + tensor)

    \ingroup libtensor_btensor_expr
 **/
template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2>
class contract_eval_functor<N, M, K, T, E1, E2, 1, 0, 1, 0> {
public:
    static const char *k_clazz; //!< Class name
    static const size_t k_ordera = N + K; //!< Order of the first %tensor
    static const size_t k_orderb = M + K; //!< Order of the second %tensor
    static const size_t k_orderc = N + M; //!< Order of the result

    //!    Contraction expression core type
    typedef core_contract<N, M, K, T, E1, E2> core_t;

    //!    Contraction expression type
    typedef expr<k_orderc, T, core_t> expression_t;

    //!    Evaluating container type of the first expression (A)
    typedef typename E1::eval_container_t eval_container_a_t;

    //!    Evaluating container type of the second expression (B)
    typedef typename E2::eval_container_t eval_container_b_t;

    //!    Sub-expressions labels
    typedef contract_subexpr_labels<N, M, K, T, E1, E2> subexpr_labels_t;

private:
    eval_container_a_t m_eval_a; //!< Container for tensor A
    arg<k_ordera, T, tensor_tag> m_arg_a; //!< Tensor argument for A
    permutation<k_ordera> m_invperm_a;
    eval_container_b_t m_eval_b; //!< Container for tensor B
    arg<k_orderb, T, tensor_tag> m_arg_b; //!< Tensor argument for B
    permutation<k_orderb> m_invperm_b;
    contract_contraction2_builder<N, M, K> m_contr_bld; //!< Contraction builder
    btod_contract2<N, M, K> m_op; //!< Contraction operation
    arg<k_orderc, T, oper_tag> m_arg; //!< Composed operation argument

public:
    contract_eval_functor(expression_t &expr,
        const subexpr_labels_t &labels_ab,
        const letter_expr<k_orderc> &label_c);

    void evaluate() { }

    void clean() { }

    arg<N + M, T, oper_tag> get_arg() const { return m_arg; }

};


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2>
const char *contract_eval_functor<N, M, K, T, E1, E2, 1, 0, 1, 0>::k_clazz =
    "contract_eval_functor<N, M, K, T, E1, E2, 1, 0, 1, 0>";


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2>
contract_eval_functor<N, M, K, T, E1, E2, 1, 0, 1, 0>::contract_eval_functor(
    expression_t &expr, const subexpr_labels_t &labels_ab,
    const letter_expr<k_orderc> &label_c) :

    m_eval_a(expr.get_core().get_expr_1(), labels_ab.get_label_a()),
    m_arg_a(m_eval_a.get_arg(tensor_tag(), 0)),
    m_invperm_a(m_arg_a.get_perm(), true),
    m_eval_b(expr.get_core().get_expr_2(), labels_ab.get_label_b()),
    m_arg_b(m_eval_b.get_arg(tensor_tag(), 0)),
    m_invperm_b(m_arg_b.get_perm(), true),
    m_contr_bld(labels_ab.get_label_a(), m_invperm_a,
        labels_ab.get_label_b(), m_invperm_b,
        label_c, expr.get_core().get_contr()),
    m_op(m_contr_bld.get_contr(), m_arg_a.get_btensor(), m_arg_b.get_btensor()),
    m_arg(m_op, m_arg_a.get_coeff() * m_arg_b.get_coeff()) {

}


} // namespace labeled_btensor_expr
} // namespace libtensor

#endif // LIBTENSOR_LABELED_BTENSOR_EXPR_CONTRACT_EVAL_FUNCTOR_1010_H
