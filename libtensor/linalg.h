#ifndef LIBTENSOR_LINALG1_H
#define LIBTENSOR_LINALG1_H

/**	\defgroup libtensor_linalg Wrappers for linear algebra primitives
	\ingroup libtensor
 **/


#ifdef USE_MKL
#include "linalg/blas_mkl.h"
#else // USE_MKL
#ifdef USE_GSL
#include "linalg/blas_gsl.h"
#else // USE_GSL
#ifdef USE_CBLAS
#include "linalg/blas_cblas.h"
#else // USE_CBLAS
#ifdef USE_QCHEM
#include "linalg/blas_qchem.h"
#else // USE_QCHEM
#error "No BLAS implementation specified"
#endif // USE_QCHEM
#endif // USE_CBLAS
#endif // USE_GSL
#endif // USE_MKL

#ifdef USE_MKL
#include "linalg/lapack_mkl.h"
#else // USE_MKL
#include "linalg/lapack_generic.h"
#endif // USE_MKL

#endif // LIBTENSOR_LINALG1_H
