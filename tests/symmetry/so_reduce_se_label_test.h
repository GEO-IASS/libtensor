#ifndef LIBTENSOR_SO_REDUCE_SE_LABEL_TEST_H
#define LIBTENSOR_SO_REDUCE_SE_LABEL_TEST_H

#include "se_label_test_base.h"

namespace libtensor {

/** \brief Tests the libtensor::so_reduce_se_label class

    \ingroup libtensor_tests_sym
 **/
class so_reduce_se_label_test : public se_label_test_base {
public:
    virtual void perform() throw(libtest::test_exception);

private:
    void test_empty_1(
            const std::string &table_id) throw(libtest::test_exception);
    void test_empty_2(
            const std::string &table_id) throw(libtest::test_exception);
    void test_nm1_1(
            const std::string &table_id) throw(libtest::test_exception);
    void test_nm1_2(const std::string &table_id,
            bool product) throw(libtest::test_exception);
    void test_nm1_3(const std::string &table_id,
            bool product) throw(libtest::test_exception);
    void test_nm1_4(
            const std::string &table_id) throw(libtest::test_exception);
    void test_nm1_5(
            const std::string &table_id) throw(libtest::test_exception);
    void test_nm1_6() throw(libtest::test_exception);
    void test_nm1_7() throw(libtest::test_exception);
    void test_nmk_1(
            const std::string &table_id) throw(libtest::test_exception);
    void test_nmk_2(const std::string &table_id,
            bool product) throw(libtest::test_exception);
    void test_nmk_3(
            const std::string &table_id) throw(libtest::test_exception);
    void test_nmk_4() throw(libtest::test_exception);

    using se_label_test_base::setup_pg_table;
    using se_label_test_base::check_allowed;
};


} // namespace libtensor

#endif // LIBTENSOR_SO_REDUCE_SE_LABEL_TEST_H

