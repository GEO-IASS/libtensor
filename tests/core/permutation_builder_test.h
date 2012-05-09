#ifndef LIBTENSOR_PERMUTATION_BUILDER_TEST_H
#define LIBTENSOR_PERMUTATION_BUILDER_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/** \brief Tests the libtensor::permutation_builder class

    \ingroup libtensor_tests_core
**/
class permutation_builder_test : public libtest::unit_test {
public:
    virtual void perform() throw(libtest::test_exception);

private:
    void test_1() throw(libtest::test_exception);
    void test_2() throw(libtest::test_exception);
    void test_3() throw(libtest::test_exception);
    void test_4() throw(libtest::test_exception);
    void test_5() throw(libtest::test_exception);
    void test_6() throw(libtest::test_exception);

};

}

#endif // LIBTENSOR_PERMUTATION_BUILDER_TEST_H
