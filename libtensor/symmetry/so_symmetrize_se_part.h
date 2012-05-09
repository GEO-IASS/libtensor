#ifndef LIBTENSOR_SO_SYMMETRIZE_SE_PART_H
#define LIBTENSOR_SO_SYMMETRIZE_SE_PART_H


#include "se_part.h"
#include "so_symmetrize.h"
#include "symmetry_element_set_adapter.h"
#include "symmetry_operation_impl_base.h"


namespace libtensor {


/** \brief Implementation of so_symmetrize<N, T> for se_part<N, T>
    \tparam N Tensor order.
    \tparam T Tensor element type.

    \ingroup libtensor_symmetry
 **/
template<size_t N, typename T>
class symmetry_operation_impl< so_symmetrize<N, T>, se_part<N, T> > :
public symmetry_operation_impl_base< so_symmetrize<N, T>, se_part<N, T> > {

public:
    static const char *k_clazz; //!< Class name

public:
    typedef so_symmetrize<N, T> operation_t;
    typedef se_part<N, T> element_t;
    typedef symmetry_operation_params<operation_t>
        symmetry_operation_params_t;

protected:
    virtual void do_perform(symmetry_operation_params_t &params) const;

private:
    static bool is_forbidden(const se_part<N, T> &sp, const index<N> &i1,
            const mask<N> &msk, const sequence<N, size_t> &map);

    static void mark_forbidden(se_part<N, T> &sp, const index<N> &i1,
            const mask<N> &msk, const sequence<N, size_t> &map);

    static bool map_exists(const se_part<N, T> &sp,
            const index<N> &i1, const index<N> &i2,
            const mask<N> &msk, const sequence<N, size_t> &map);

    static void add_map(se_part<N, T> &sp,
            const index<N> &i1, const index<N> &i2,
            const scalar_transf<T>& tr, const mask<N> &msk,
            const sequence<N, size_t> &map);
};


} // namespace libtensor


#endif // LIBTENSOR_SO_SYMMETRIZE_SE_PART_H
