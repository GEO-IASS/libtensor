#ifndef LIBTENSOR_LINALG_BASE_GSL_H
#define LIBTENSOR_LINALG_BASE_GSL_H

#include <gsl/gsl_cblas.h>
#include "../generic/linalg_base_lowlevel.h"
#include "../adaptive/linalg_base_highlevel.h"
#include "../generic/linalg_base_memory_generic.h"
#include "../cblas/linalg_base_level1_cblas.h"
#include "../cblas/linalg_base_level2_cblas.h"
#include "../cblas/linalg_base_level3_cblas.h"

namespace libtensor {


/** \brief Linear algebra implementation based on
        GNU Scientific Library (GSL)

    \ingroup libtensor_linalg
 **/
struct linalg_base_gsl :
    public linalg_base_lowlevel<
        linalg_base_memory_generic,
        linalg_base_level1_cblas,
        linalg_base_level2_cblas,
        linalg_base_level3_cblas>,
    public linalg_base_highlevel<
        linalg_base_memory_generic,
        linalg_base_level1_cblas,
        linalg_base_level2_cblas,
        linalg_base_level3_cblas>
{ };


} // namespace libtensor

#endif // LIBTENSOR_LINALG_BASE_GSL_H
