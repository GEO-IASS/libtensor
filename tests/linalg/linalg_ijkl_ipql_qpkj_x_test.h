#ifndef LIBTENSOR_LINALG_IJKL_IPQL_QPKJ_X_TEST_H
#define LIBTENSOR_LINALG_IJKL_IPQL_QPKJ_X_TEST_H

#include "linalg_test_base.h"

namespace libtensor {


/**	\brief Tests the libtensor::linalg class (ijkl_ipql_qpkj_x)

	\ingroup libtensor_tests_linalg
 **/
class linalg_ijkl_ipql_qpkj_x_test : public linalg_test_base {
public:
	virtual void perform() throw(libtest::test_exception);

private:
	void test_ijkl_ipql_qpkj_x(size_t ni, size_t nj, size_t nk, size_t nl,
		size_t np, size_t nq) throw(libtest::test_exception);

};


} // namespace libtensor

#endif // LIBTENSOR_LINALG_IJKL_IPQL_QPKJ_X_TEST_H
