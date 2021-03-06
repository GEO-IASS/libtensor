#ifndef LIBTENSOR_LIBTENSOR_CTF_DENSE_TENSOR_SUITE_H
#define LIBTENSOR_LIBTENSOR_CTF_DENSE_TENSOR_SUITE_H

#include <libtest/test_suite.h>
#include "ctf_dense_tensor_test.h"
#include "ctf_symmetry_test.h"
#include "ctf_tod_contract2_test.h"
#include "ctf_tod_copy_test.h"
#include "ctf_tod_diag_test.h"
#include "ctf_tod_dirsum_test.h"
#include "ctf_tod_distribute_test.h"
#include "ctf_tod_dotprod_test.h"
#include "ctf_tod_ewmult2_test.h"
#include "ctf_tod_mult_test.h"
#include "ctf_tod_mult1_test.h"
#include "ctf_tod_random_test.h"
#include "ctf_tod_scale_test.h"
#include "ctf_tod_scatter_test.h"
#include "ctf_tod_set_test.h"
#include "ctf_tod_set_diag_test.h"
#include "ctf_tod_set_symmetry_test.h"
#include "ctf_tod_trace_test.h"

using libtest::unit_test_factory;

namespace libtensor {


/** \defgroup libtensor_ctf_dense_tensor_tests Tests for CTF tensors and
        operations
    \ingroup libtensor_tests
 **/


/** \brief Test suite for CTF tensors

    This suite runs the following tests:
     - libtensor::ctf_dense_tensor_test
     - libtensor::ctf_symmetry_test
     - libtensor::ctf_tod_contract2_test
     - libtensor::ctf_tod_copy_test
     - libtensor::ctf_tod_diag_test
     - libtensor::ctf_tod_dirsum_test
     - libtensor::ctf_tod_distribute_test
     - libtensor::ctf_tod_dotprod_test
     - libtensor::ctf_tod_ewmult2_test
     - libtensor::ctf_tod_mult_test
     - libtensor::ctf_tod_mult1_test
     - libtensor::ctf_tod_random_test
     - libtensor::ctf_tod_scale_test
     - libtensor::ctf_tod_scatter_test
     - libtensor::ctf_tod_set_test
     - libtensor::ctf_tod_set_diag_test
     - libtensor::ctf_tod_set_symmetry_test
     - libtensor::ctf_tod_trace_test

    \ingroup libtensor_ctf_dense_tensor_tests
 **/
class libtensor_ctf_dense_tensor_suite : public libtest::test_suite {
private:
    unit_test_factory<ctf_dense_tensor_test> m_utf_ctf_dense_tensor;
    unit_test_factory<ctf_symmetry_test> m_utf_ctf_symmetry;
    unit_test_factory<ctf_tod_contract2_test> m_utf_ctf_tod_contract2;
    unit_test_factory<ctf_tod_copy_test> m_utf_ctf_tod_copy;
    unit_test_factory<ctf_tod_diag_test> m_utf_ctf_tod_diag;
    unit_test_factory<ctf_tod_dirsum_test> m_utf_ctf_tod_dirsum;
    unit_test_factory<ctf_tod_distribute_test> m_utf_ctf_tod_distribute;
    unit_test_factory<ctf_tod_dotprod_test> m_utf_ctf_tod_dotprod;
    unit_test_factory<ctf_tod_ewmult2_test> m_utf_ctf_tod_ewmult2;
    unit_test_factory<ctf_tod_mult_test> m_utf_ctf_tod_mult;
    unit_test_factory<ctf_tod_mult1_test> m_utf_ctf_tod_mult1;
    unit_test_factory<ctf_tod_random_test> m_utf_ctf_tod_random;
    unit_test_factory<ctf_tod_scale_test> m_utf_ctf_tod_scale;
    unit_test_factory<ctf_tod_scatter_test> m_utf_ctf_tod_scatter;
    unit_test_factory<ctf_tod_set_test> m_utf_ctf_tod_set;
    unit_test_factory<ctf_tod_set_diag_test> m_utf_ctf_tod_set_diag;
    unit_test_factory<ctf_tod_set_symmetry_test> m_utf_ctf_tod_set_symmetry;
    unit_test_factory<ctf_tod_trace_test> m_utf_ctf_tod_trace;

public:
    //! Creates the suite
    libtensor_ctf_dense_tensor_suite();

};


} // namespace libtensor

#endif // LIBTENSOR_LIBTENSOR_CTF_DENSE_TENSOR_SUITE_H

