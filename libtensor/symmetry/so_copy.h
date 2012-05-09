#ifndef LIBTENSOR_SO_COPY_H
#define LIBTENSOR_SO_COPY_H

#include "../core/symmetry.h"

namespace libtensor {


/** \brief Produces a verbatim copy of a %symmetry group
    \tparam N Symmetry cardinality (%tensor order).
    \tparam T Tensor element type.

    The operation copies all elements one by one from one %symmetry
    container to another. If the destination %symmetry already contains
    elements, they are first erased.

    \ingroup libtensor_symmetry
 **/
template<size_t N, typename T>
class so_copy {
private:
    const symmetry<N, T> &m_sym1;

public:
    /** \brief Initializes the operation
        \param sym1 Source %symmetry container.
     **/
    so_copy(const symmetry<N, T> &sym1) : m_sym1(sym1) { }

    /** \brief Performs the operation
        \param sym2 Destination %symmetry container.
     **/
    void perform(symmetry<N, T> &sym2);

};

} // namespace libtensor

#endif // LIBTENSOR_SO_COPY_H
