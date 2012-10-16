#ifndef LIBTENSOR_LINALG_QCHEM_H
#define LIBTENSOR_LINALG_QCHEM_H

#include "linalg_qchem_level1.h"
#include "linalg_qchem_level2.h"
#include "linalg_qchem_level3.h"

namespace libtensor {


/** \brief Linear algebra implementation based on Q-Chem's imported BLAS

    \ingroup libtensor_linalg
 **/
class linalg_qchem :
    public linalg_qchem_level1,
    public linalg_qchem_level2,
    public linalg_qchem_level3 {

public:
    typedef double element_type; //!< Data type
    typedef void *device_context_type; //!< Device context
    typedef void *device_context_ref; //!< Reference type to device context

};


} // namespace libtensor

#endif // LIBTENSOR_LINALG_QCHEM_H
