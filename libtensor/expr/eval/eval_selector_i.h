#ifndef LIBTENSOR_EXPR_EVAL_SELECTOR_I_H
#define LIBTENSOR_EXPR_EVAL_SELECTOR_I_H

#include "eval_i.h"

namespace libtensor {
namespace expr {


/** \brief Interface for evaluator selection strategies

    This interface is to be implemented by evaluator selection algorithms.
    The try_evaluator() method is to be called for each available evaluator,
    the strategy selects the most suitable one.

    \ingroup libtensor_expr_eval
 **/
class eval_selector_i {
public:
    /** \brief Virtual destructor
     **/
    virtual ~eval_selector_i() { }

    /** \brief Tests an evaluator for suitability
     **/
    virtual void try_evaluator(const eval_i &e) = 0;

    /** \brief Returns the selected evaluator or throws an exception
     **/
    virtual const eval_i &get_selected() const = 0;

};


} // namespace expr
} // namespace libtensor

#endif // LIBTENSOR_EXPR_EVAL_SELECTOR_I_H
