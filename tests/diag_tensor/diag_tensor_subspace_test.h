#ifndef LIBTENSOR_DIAG_TENSOR_SUBSPACE_TEST_H
#define LIBTENSOR_DIAG_TENSOR_SUBSPACE_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {


/** \brief Tests the libtensor::diag_tensor_subspace class

    \ingroup libtensor_diag_tensor_tests
 **/
class diag_tensor_subspace_test : public libtest::unit_test {
public:
    virtual void perform() throw(libtest::test_exception);

private:
    void test_1() throw(libtest::test_exception);
    void test_2() throw(libtest::test_exception);
    void test_3() throw(libtest::test_exception);

    void test_equals_1() throw(libtest::test_exception);
    void test_equals_2() throw(libtest::test_exception);
    void test_equals_3() throw(libtest::test_exception);

    void test_permute_1() throw(libtest::test_exception);
    void test_permute_2() throw(libtest::test_exception);
    void test_permute_3() throw(libtest::test_exception);

    void test_exc_1() throw(libtest::test_exception);
    void test_exc_2() throw(libtest::test_exception);
    void test_exc_3() throw(libtest::test_exception);

};


} // namespace libtensor

#endif // LIBTENSOR_DIAG_TENSOR_SUBSPACE_TEST_H

