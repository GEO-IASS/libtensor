#ifndef LIBTENSOR_SE_PART_TEST_H
#define LIBTENSOR_SE_PART_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/** \brief Tests the libtensor::se_part class

    \ingroup libtensor_tests_sym
 **/
class se_part_test : public libtest::unit_test {
public:
    virtual void perform() throw(libtest::test_exception);

private:
    void test_1() throw(libtest::test_exception);
    void test_2() throw(libtest::test_exception);
    void test_3a() throw(libtest::test_exception);
    void test_3b() throw(libtest::test_exception);
    void test_4() throw(libtest::test_exception);
    void test_5() throw(libtest::test_exception);
    void test_6() throw(libtest::test_exception);
    void test_perm_1() throw(libtest::test_exception);
    void test_perm_2() throw(libtest::test_exception);
    void test_perm_3() throw(libtest::test_exception);
    void test_perm_4() throw(libtest::test_exception);
    void test_perm_5() throw(libtest::test_exception);
    void test_exc() throw(libtest::test_exception);
};

} // namespace libtensor

#endif // LIBTENSOR_SE_PART_TEST_H

