#ifndef LIBTENSOR_LINALG_MKL_H
#define LIBTENSOR_LINALG_MKL_H

#include "linalg_mkl_level1.h"
#include "linalg_mkl_level2.h"
#include "linalg_mkl_level3.h"

namespace libtensor {


/** \brief Linear algebra implementation based on
        Intel Math Kernel Library (MKL)

    \ingroup libtensor_linalg
 **/
class linalg_mkl :
    public linalg_mkl_level1,
    public linalg_mkl_level2,
    public linalg_mkl_level3 {

public:
    typedef double element_type; //!< Data type
    typedef void *device_context_type; //!< Device context
    typedef void *device_context_ref; //!< Reference type to device context

};


} // namespace libtensor

#endif // LIBTENSOR_LINALG_MKL_H
