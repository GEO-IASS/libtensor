#ifndef LIBTENSOR_LIBTENSOR_TOD_SUITE_H
#define LIBTENSOR_LIBTENSOR_TOD_SUITE_H

#include <libtest/test_suite.h>
#include "contraction2_test.h"
#include "contraction2_list_builder_test.h"
#include "tod_add_test.h"
#include "tod_apply_test.h"
#include "tod_btconv_test.h"
#include "tod_compare_test.h"
#include "to_contract2_dims_test.h"
#include "to_contract2_perms_test.h"
#include "tod_contract2_test.h"
#include "tod_copy_test.h"
#include "tod_diag_test.h"
#include "tod_dirsum_test.h"
#include "tod_dotprod_test.h"
#include "tod_ewmult2_test.h"
#include "tod_extract_test.h"
#include "tod_import_raw_test.h"
#include "tod_import_raw_stream_test.h"
#include "tod_mult_test.h"
#include "tod_mult1_test.h"
#include "tod_random_test.h"
#include "tod_scale_test.h"
#include "tod_scatter_test.h"
#include "tod_select_test.h"
#include "tod_set_test.h"
#include "tod_set_diag_test.h"
#include "tod_set_elem_test.h"
#include "tod_trace_test.h"
#include "tod_vmpriority_test.h"

using libtest::unit_test_factory;

namespace libtensor {

/** \defgroup libtensor_tests_tod Tests of tensor operations
 	\brief Unit tests of the %tensor operations in libtensor
 	\ingroup libtensor_tests
 **/


/**
	\brief Test suite for the tensor operations in libtensor
	\ingroup libtensor_tests

	This suite runs the following tests:
	\li libtensor::contraction2_test
	\li libtensor::contraction2_list_builder_test
	\li libtensor::tod_add_test
	\li libtensor::tod_apply_test
	\li libtensor::tod_btconv_test
	\li libtensor::tod_compare_test
	\li libtensor::to_contract2_dims_test
	\li libtensor::to_contract2_perms_test
	\li libtensor::tod_contract2_test
	\li libtensor::tod_copy_test
	\li libtensor::tod_diag_test
	\li libtensor::tod_dirsum_test
	\li libtensor::tod_dotprod_test
	\li libtensor::tod_ewmult2_test
	\li libtensor::tod_extract_test
	\li libtensor::tod_import_raw_test
    \li libtensor::tod_import_raw_stream_test
	\li libtensor::tod_mult_test
	\li libtensor::tod_mult1_test
	\li libtensor::tod_random_test
	\li libtensor::tod_scale_test
	\li libtensor::tod_scatter_test
	\li libtensor::tod_select_test
	\li libtensor::tod_set_test
	\li libtensor::tod_set_diag_test
	\li libtensor::tod_set_elem_test
	\li libtensor::tod_trace_test
	\li libtensor::tod_vmpriority_test
**/
class libtensor_tod_suite : public libtest::test_suite {
private:
	unit_test_factory<contraction2_test> m_utf_contraction2;
	unit_test_factory<contraction2_list_builder_test>
		m_utf_contraction2_list_builder;
	unit_test_factory<tod_add_test> m_utf_tod_add;
	unit_test_factory<tod_apply_test> m_utf_tod_apply;
	unit_test_factory<tod_btconv_test> m_utf_tod_btconv;
	unit_test_factory<tod_compare_test> m_utf_tod_compare;
	unit_test_factory<to_contract2_dims_test> m_utf_to_contract2_dims;
	unit_test_factory<to_contract2_perms_test> m_utf_to_contract2_perms;
	unit_test_factory<tod_contract2_test> m_utf_tod_contract2;
	unit_test_factory<tod_copy_test> m_utf_tod_copy;
	unit_test_factory<tod_diag_test> m_utf_tod_diag;
	unit_test_factory<tod_dirsum_test> m_utf_tod_dirsum;
	unit_test_factory<tod_dotprod_test> m_utf_tod_dotprod;
	unit_test_factory<tod_ewmult2_test> m_utf_tod_ewmult2;
	unit_test_factory<tod_extract_test> m_utf_tod_extract;
	unit_test_factory<tod_import_raw_test> m_utf_tod_import_raw;
    unit_test_factory<tod_import_raw_stream_test> m_utf_tod_import_raw_stream;
	unit_test_factory<tod_mult_test> m_utf_tod_mult;
	unit_test_factory<tod_mult1_test> m_utf_tod_mult1;
	unit_test_factory<tod_random_test> m_utf_tod_random;
	unit_test_factory<tod_scale_test> m_utf_tod_scale;
	unit_test_factory<tod_scatter_test> m_utf_tod_scatter;
	unit_test_factory<tod_select_test> m_utf_tod_select;
	unit_test_factory<tod_set_test> m_utf_tod_set;
	unit_test_factory<tod_set_diag_test> m_utf_tod_set_diag;
	unit_test_factory<tod_set_elem_test> m_utf_tod_set_elem;
	unit_test_factory<tod_trace_test> m_utf_tod_trace;
	unit_test_factory<tod_vmpriority_test> m_utf_tod_vmpriority;

public:
	//!	Creates the suite
	libtensor_tod_suite();
};

} // namespace libtensor

#endif // LIBTENSOR_LIBTENSOR_SUITE_H

