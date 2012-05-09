#ifndef LIBTENSOR_IMMUTABLE_TEST_H
#define LIBTENSOR_IMMUTABLE_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/** \brief Tests the libtensor::immutable class

    \ingroup libtensor_tests_core
**/
class immutable_test : public libtest::unit_test {
public:
    virtual void perform() throw(libtest::test_exception);

};

} // namespace libtensor

#endif // LIBTENSOR_IMMUTABLE_TEST_H

