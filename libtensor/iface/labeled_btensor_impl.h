#ifndef LIBTENSOR_LABELED_BTENSOR_IMPL_H
#define LIBTENSOR_LABELED_BTENSOR_IMPL_H

#include "../defs.h"
#include "../exception.h"
#include "labeled_btensor.h"
#include "expr/expr.h"
#include "expr/eval.h"
#include "ident/core_ident.h"

namespace libtensor {

template<size_t N, typename T> template<typename Expr>
labeled_btensor<N, T, true> &labeled_btensor<N, T, true>::operator=(
    const labeled_btensor_expr::expr<N, T, Expr> rhs) throw(exception) {

    labeled_btensor_expr::eval<N, T, Expr> eval(rhs, *this);
    eval.evaluate();
    return *this;
}

template<size_t N, typename T>
template<bool AssignableR>
labeled_btensor<N, T, true> &labeled_btensor<N, T, true>::operator=(
    labeled_btensor<N, T, AssignableR> rhs) throw(exception) {

    typedef labeled_btensor_expr::core_ident<N, T, AssignableR> id_t;
    typedef labeled_btensor_expr::expr<N, T, id_t> expr_t;
    id_t id(rhs);
    expr_t op(id);
    labeled_btensor_expr::eval<N, T, id_t> eval(op, *this);
    eval.evaluate();
    return *this;
}

template<size_t N, typename T>
labeled_btensor<N, T, true> &labeled_btensor<N, T, true>::operator=(
    labeled_btensor<N, T, true> rhs) throw(exception) {

    typedef labeled_btensor_expr::core_ident<N, T, true> id_t;
    typedef labeled_btensor_expr::expr<N, T, id_t> expr_t;
    id_t id(rhs);
    expr_t op(id);
    labeled_btensor_expr::eval<N, T, id_t> eval(op, *this);
    eval.evaluate();
    return *this;
}

} // namespace libtensor

#endif // LIBTENSOR_LABELED_BTENSOR_IMPL_H
