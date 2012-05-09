#ifndef LIBTENSOR_LIBTENSOR_DIAG_TENSOR_SUITE_H
#define LIBTENSOR_LIBTENSOR_DIAG_TENSOR_SUITE_H

#include <libtest/test_suite.h>
#include "diag_tensor_test.h"
#include "diag_tensor_space_test.h"
#include "diag_tensor_subspace_test.h"
#include "diag_to_add_space_test.h"
#include "diag_to_contract2_space_test.h"
#include "diag_tod_adjust_space_test.h"
#include "diag_tod_set_test.h"
#include "tod_conv_diag_tensor_test.h"

using libtest::unit_test_factory;

namespace libtensor {

/** \defgroup libtensor_diag_tensor_tests Tests of diagonal tensor routines
    \brief Unit tests for diagonal tensor classes in libtensor
    \ingroup libtensor_tests
 **/


/** \brief Test suite for diagonal tensor classes and operations in libtensor

    This suite runs the following tests:
     - libtensor::diag_tensor_test
     - libtensor::diag_tensor_space_test
     - libtensor::diag_tensor_subspace_test
     - libtensor::diag_to_add_space_test
     - libtensor::diag_to_contract2_space_test
     - libtensor::diag_tod_adjust_space_test
     - libtensor::diag_tod_set_test
     - libtensor::tod_conv_diag_tensor_test

    \ingroup libtensor_diag_tensor_tests
 **/
class libtensor_diag_tensor_suite : public libtest::test_suite {
private:
    unit_test_factory<diag_tensor_test> m_utf_diag_tensor;
    unit_test_factory<diag_tensor_space_test> m_utf_diag_tensor_space;
    unit_test_factory<diag_tensor_subspace_test> m_utf_diag_tensor_subspace;
    unit_test_factory<diag_to_add_space_test> m_utf_diag_to_add_space;
    unit_test_factory<diag_to_contract2_space_test>
        m_utf_diag_to_contract2_space;
    unit_test_factory<diag_tod_adjust_space_test> m_utf_diag_tod_adjust_space;
    unit_test_factory<diag_tod_set_test> m_utf_diag_tod_set;
    unit_test_factory<tod_conv_diag_tensor_test> m_utf_tod_conv_diag_tensor;

public:
    //! Creates the suite
    libtensor_diag_tensor_suite();

};


} // namespace libtensor

#endif // LIBTENSOR_LIBTENSOR_DIAG_TENSOR_SUITE_H

