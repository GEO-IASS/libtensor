#ifndef LIBTENSOR_LINALG_GSL_H
#define LIBTENSOR_LINALG_GSL_H

#include "../cblas/linalg_cblas_level1.h"
#include "../cblas/linalg_cblas_level2.h"
#include "../cblas/linalg_cblas_level3.h"

namespace libtensor {


/** \brief Linear algebra implementation based on
        GNU Scientific Library (GSL)

    \ingroup libtensor_linalg
 **/
class linalg_gsl :
    public linalg_cblas_level1,
    public linalg_cblas_level2,
    public linalg_cblas_level3 {

public:
    typedef double element_type; //!< Data type
    typedef void *device_context_type; //!< Device context
    typedef void *device_context_ref; //!< Reference type to device context

};


} // namespace libtensor

#endif // LIBTENSOR_LINALG_GSL_H
