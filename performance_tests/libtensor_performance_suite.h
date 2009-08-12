#ifndef LIBTENSOR_LIBTENSOR_SUITE_H
#define LIBTENSOR_LIBTENSOR_SUITE_H

#include <libtest.h>
#include <libtensor.h>
#include "expression_p_test.h"

using libtest::unit_test_factory;

namespace libtensor {

/**
	\brief Test suite for the tensor library (libtensor)

	This suite runs the following tests:
	\li libtensor::tod_add_test
**/
class libtensor_performance_suite : public libtest::test_suite {
private:
	unit_test_factory<expression_p_test> m_utf_expression_p;

public:
	//!	Creates the suite
	libtensor_performance_suite();
};

} // namespace libtensor

#endif // LIBTENSOR_LIBTENSOR_SUITE_H
