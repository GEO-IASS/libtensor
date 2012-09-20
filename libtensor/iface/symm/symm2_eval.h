#ifndef LIBTENSOR_LABELED_BTENSOR_EXPR_SYMM2_EVAL_H
#define LIBTENSOR_LABELED_BTENSOR_EXPR_SYMM2_EVAL_H

#include <libtensor/block_tensor/btod/btod_symmetrize.h>
#include "../expr/eval_i.h"
#include "../expr/evalfunctor.h"

namespace libtensor {
namespace labeled_btensor_expr {


/** \brief Evaluating container for the symmetrization over two sets of
        indexes
    \tparam N Tensor order.
    \tparam M Number of indexes in the set.
    \tparam Sym Symmetrization/antisymmetrization.
    \tparam SubCore Sub-expression core type.

    \ingroup libtensor_btensor_expr
 **/
template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
class symm2_eval : public eval_i<N, T> {
public:
    static const char *k_clazz; //!< Class name

    //!    Expression core type
    typedef symm2_core<N, M, Sym, T, SubCore> core_t;

    //!    Expression type
    typedef expr<N, T, core_t> expression_t;

    //!    Sub-expression core type
    typedef SubCore sub_core_t;

    //!    Sub-expression type
    typedef expr<N, T, sub_core_t> sub_expr_t;

    //!    Evaluating container type
    typedef typename sub_expr_t::eval_container_t sub_eval_container_t;

    //!    Number of tensor arguments
    static const size_t k_sub_narg_tensor =
        sub_eval_container_t::template narg<tensor_tag>::k_narg;

    //!    Number of operation arguments
    static const size_t k_sub_narg_oper =
        sub_eval_container_t::template narg<oper_tag>::k_narg;

    //!    Evaluation functor type
    typedef evalfunctor<N, T, sub_core_t, k_sub_narg_tensor,
        k_sub_narg_oper> sub_evalfunctor_t;

    //!    Number of arguments in the expression
    template<typename Tag, int Dummy = 0>
    struct narg {
        static const size_t k_narg = 0;
    };

private:
    sub_expr_t m_sub_expr; //!< Sub-expression
    sub_eval_container_t m_sub_eval_cont; //!< Evaluation of the sub-expression
    sub_evalfunctor_t m_sub_eval; //!< Evaluation functor
    permutation<N> m_perm; //!< Permutation for symmetrization
    btod_symmetrize<N> *m_op; //!< Symmetrization operation
    arg<N, T, oper_tag> *m_arg; //!< Argument

public:
    /** \brief Initializes the container with given expression and
            result recipient
     **/
    symm2_eval(expression_t &expr, const letter_expr<N> &label);

    /** \brief Virtual destructor
     **/
    virtual ~symm2_eval();

    /** \brief Evaluates sub-expressions into temporary tensors
     **/
    void prepare();

    /** \brief Cleans up temporary tensors
     **/
    void clean();

    template<typename Tag>
    arg<N, T, Tag> get_arg(const Tag &tag, size_t i) const;

    /** \brief Returns the operation argument
     **/
    arg<N, T, oper_tag> get_arg(const oper_tag &tag, size_t i) const;

private:
    void create_arg();
    void destroy_arg();

};


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
const char *symm2_eval<N, M, Sym, T, SubCore>::k_clazz =
    "symm2_eval<N, M, Sym, T, SubCore>";


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
template<int Dummy>
struct symm2_eval<N, M, Sym, T, SubCore>::narg<oper_tag, Dummy> {
    static const size_t k_narg = 1;
};


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
symm2_eval<N, M, Sym, T, SubCore>::symm2_eval(expression_t &expr,
    const letter_expr<N> &label) :

    m_sub_expr(expr.get_core().get_sub_expr()),
    m_sub_eval_cont(m_sub_expr, label),
    m_sub_eval(m_sub_expr, m_sub_eval_cont),
    m_op(0), m_arg(0) {

    for(size_t i = 0; i < M; i++) {
        size_t i1 = label.index_of(
            expr.get_core().get_sym1().letter_at(i));
        size_t i2 = label.index_of(
            expr.get_core().get_sym2().letter_at(i));
        m_perm.permute(i1, i2);
    }
}


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
symm2_eval<N, M, Sym, T, SubCore>::~symm2_eval() {

    destroy_arg();
}


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
void symm2_eval<N, M, Sym, T, SubCore>::prepare() {

    m_sub_eval_cont.prepare();
    create_arg();
}


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
void symm2_eval<N, M, Sym, T, SubCore>::clean() {

    destroy_arg();
    m_sub_eval_cont.clean();
}


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
void symm2_eval<N, M, Sym, T, SubCore>::create_arg() {

    destroy_arg();
    m_op = new btod_symmetrize<N>(m_sub_eval.get_bto(), m_perm, Sym);
    m_arg = new arg<N, T, oper_tag>(*m_op, 1.0);
}


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
void symm2_eval<N, M, Sym, T, SubCore>::destroy_arg() {

    delete m_arg; m_arg = 0;
    delete m_op; m_op = 0;
}


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
template<typename Tag>
arg<N, T, Tag> symm2_eval<N, M, Sym, T, SubCore>::get_arg(const Tag &tag,
    size_t i) const {

    static const char *method = "get_arg(const Tag&, size_t)";

    throw expr_exception(g_ns, k_clazz, method, __FILE__, __LINE__,
        "Invalid method.");
}


template<size_t N, size_t M, bool Sym, typename T, typename SubCore>
arg<N, T, oper_tag> symm2_eval<N, M, Sym, T, SubCore>::get_arg(
    const oper_tag &tag, size_t i) const {

    static const char *method = "get_arg(const oper_tag&, size_t)";
    if(i == 0) {
        return *m_arg;
    } else {
        throw out_of_bounds(g_ns, k_clazz, method, __FILE__, __LINE__,
            "Argument index is out of bounds.");
    }
}


} // namespace labeled_btensor_expr
} // namespace libtensor

#endif // LIBTENSOR_LABELED_BTENSOR_EXPR_SYMM2_EVAL_H
