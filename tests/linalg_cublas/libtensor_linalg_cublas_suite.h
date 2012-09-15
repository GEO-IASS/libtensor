#ifndef LIBTENSOR_LIBTENSOR_LINALG_CUBLAS_SUITE_H
#define LIBTENSOR_LIBTENSOR_LINALG_CUBLAS_SUITE_H

#include <libtest/test_suite.h>
//#include "linalg_add_i_i_x_x_test.h"
#include "linalg_cublas_x_p_p_test.h"
#include "linalg_cublas_i_x_test.h"
#include "linalg_cublas_i_i_x_test.h"

#include "linalg_cublas_i_ip_p_x_test.h"
/*
#include "linalg_i_i_i_x_test.h"
#include "linalg_x_pq_qp_test.h"

#include "linalg_i_pi_p_x_test.h"
#include "linalg_ij_i_j_x_test.h"
#include "linalg_ij_ji_test.h"
#include "linalg_i_ipq_qp_x_test.h"
#include "linalg_ij_ip_jp_x_test.h"
#include "linalg_ij_ip_pj_x_test.h"
#include "linalg_ij_pi_jp_x_test.h"
#include "linalg_ij_pi_pj_x_test.h"
#include "linalg_ij_pji_p_x_test.h"
#include "linalg_ij_ipq_jqp_x_test.h"
#include "linalg_ijk_ip_pkj_x_test.h"
#include "linalg_ijk_pi_pkj_x_test.h"
#include "linalg_ijk_ipkq_jpq_x_test.h"
#include "linalg_ijk_ipq_kjqp_x_test.h"
#include "linalg_ijk_pikq_jpq_x_test.h"
#include "linalg_ijk_piqk_jpq_x_test.h"
#include "linalg_ijk_pkiq_pjq_x_test.h"
#include "linalg_ijkl_ikp_jpl_x_test.h"
#include "linalg_ijkl_ipj_plk_x_test.h"
#include "linalg_ijkl_ipl_jpk_x_test.h"
#include "linalg_ijkl_ipl_kpj_x_test.h"
#include "linalg_ijkl_ipkq_pljq_x_test.h"
#include "linalg_ijkl_iplq_kpjq_x_test.h"
#include "linalg_ijkl_iplq_pkjq_x_test.h"
#include "linalg_ijkl_iplq_pkqj_x_test.h"
#include "linalg_ijkl_ipqk_pljq_x_test.h"
#include "linalg_ijkl_ipql_pkjq_x_test.h"
#include "linalg_ijkl_ipql_pkqj_x_test.h"
#include "linalg_ijkl_ipql_qkpj_x_test.h"
#include "linalg_ijkl_ipql_qpkj_x_test.h"
#include "linalg_ijkl_pikq_pljq_x_test.h"
#include "linalg_ijkl_pilq_kpjq_x_test.h"
#include "linalg_ijkl_pilq_pkjq_x_test.h"
#include "linalg_ijkl_piqk_pljq_x_test.h"
#include "linalg_ijkl_piql_kpqj_x_test.h"
#include "linalg_ijkl_piql_pkjq_x_test.h"
#include "linalg_ijkl_piql_pkqj_x_test.h"
#include "linalg_ijkl_piql_qkpj_x_test.h"
#include "linalg_ijkl_piql_qpkj_x_test.h"
#include "linalg_ijkl_pkiq_jplq_x_test.h"
#include "linalg_ijkl_pkiq_jpql_x_test.h"
#include "linalg_ijkl_pkiq_pjlq_x_test.h"
#include "linalg_ijkl_pkiq_pjql_x_test.h"
#include "linalg_ijkl_pliq_jpkq_x_test.h"
#include "linalg_ijkl_pliq_jpqk_x_test.h"
#include "linalg_ijkl_pliq_pjqk_x_test.h"
#include "linalg_ijklm_ipkm_jlp_x_test.h"
*/

using libtest::unit_test_factory;

namespace libtensor {

/** \defgroup libtensor_tests_linalg_cublas Tests of CUDA linear algebra
        components
    \brief Unit tests of the CUDA linear algebra components in libtensor
    \ingroup libtensor_tests
 **/


/** \brief Test suite for the CUDA linear algebra in the tensor library
    \ingroup libtensor_tests


    This suite runs the following tests:
     - libtensor::linalg_add_i_i_x_x_test
     - libtensor::linalg_cublas_x_p_p_test
     - libtensor::linalg_i_i_i_x_test
     - libtensor::linalg_cublas_i_i_x_test
     - libtensor::linalg_x_pq_qp_test
     - libtensor::linalg_i_ip_p_x_test
     - libtensor::linalg_i_pi_p_x_test
     - libtensor::linalg_ij_i_j_x_test
     - libtensor::linalg_ij_ji_test
     - libtensor::linalg_i_ipq_qp_x_test
     - libtensor::linalg_ij_ip_jp_x_test
     - libtensor::linalg_ij_ip_pj_x_test
     - libtensor::linalg_ij_pi_jp_x_test
     - libtensor::linalg_ij_pi_pj_x_test
     - libtensor::linalg_ij_pji_p_x_test
     - libtensor::linalg_ij_ipq_jqp_x_test
     - libtensor::linalg_ijk_ip_pkj_x_test
     - libtensor::linalg_ijk_pi_pkj_x_test
     - libtensor::linalg_ijk_ipkq_jpq_x_test
     - libtensor::linalg_ijk_ipq_kjqp_x_test
     - libtensor::linalg_ijk_pikq_jpq_x_test
     - libtensor::linalg_ijk_piqk_jpq_x_test
     - libtensor::linalg_ijk_pkiq_pjq_x_test
     - libtensor::linalg_ijkl_ikp_jpl_x_test
     - libtensor::linalg_ijkl_ipj_plk_x_test
     - libtensor::linalg_ijkl_ipl_jpk_x_test
     - libtensor::linalg_ijkl_ipl_kpj_x_test
     - libtensor::linalg_ijkl_ipkq_pljq_x_test
     - libtensor::linalg_ijkl_iplq_kpjq_x_test
     - libtensor::linalg_ijkl_iplq_pkjq_x_test
     - libtensor::linalg_ijkl_iplq_pkqj_x_test
     - libtensor::linalg_ijkl_ipqk_pljq_x_test
     - libtensor::linalg_ijkl_ipql_pkjq_x_test
     - libtensor::linalg_ijkl_ipql_pkqj_x_test
     - libtensor::linalg_ijkl_ipql_qkpj_x_test
     - libtensor::linalg_ijkl_ipql_qpkj_x_test
     - libtensor::linalg_ijkl_pikq_pljq_x_test
     - libtensor::linalg_ijkl_pilq_kpjq_x_test
     - libtensor::linalg_ijkl_pilq_pkjq_x_test
     - libtensor::linalg_ijkl_piqk_pljq_x_test
     - libtensor::linalg_ijkl_piql_kpqj_x_test
     - libtensor::linalg_ijkl_piql_pkjq_x_test
     - libtensor::linalg_ijkl_piql_pkqj_x_test
     - libtensor::linalg_ijkl_piql_qkpj_x_test
     - libtensor::linalg_ijkl_piql_qpkj_x_test
     - libtensor::linalg_ijkl_pkiq_jplq_x_test
     - libtensor::linalg_ijkl_pkiq_jpql_x_test
     - libtensor::linalg_ijkl_pkiq_pjlq_x_test
     - libtensor::linalg_ijkl_pkiq_pjql_x_test
     - libtensor::linalg_ijkl_pliq_jpkq_x_test
     - libtensor::linalg_ijkl_pliq_jpqk_x_test
     - libtensor::linalg_ijkl_pliq_pjqk_x_test
     - libtensor::linalg_ijklm_ipkm_jlp_x_test

 **/
class libtensor_linalg_cublas_suite : public libtest::test_suite {
private:
    //unit_test_factory<linalg_add_i_i_x_x_test> m_utf_linalg_add_i_i_x_x;
    unit_test_factory<linalg_cublas_x_p_p_test> m_utf_linalg_cublas_x_p_p;
    unit_test_factory<linalg_cublas_i_x_test> m_utf_linalg_cublas_i_x;
    unit_test_factory<linalg_cublas_i_i_x_test> m_utf_linalg_cublas_i_i_x;
/*
    unit_test_factory<linalg_i_i_i_x_test> m_utf_linalg_i_i_i_x;
    unit_test_factory<linalg_x_pq_qp_test> m_utf_linalg_x_pq_qp;*/
    unit_test_factory<linalg_cublas_i_ip_p_x_test> m_utf_linalg_cublas_i_ip_p_x;
/*    unit_test_factory<linalg_i_pi_p_x_test> m_utf_linalg_i_pi_p_x;
    unit_test_factory<linalg_ij_i_j_x_test> m_utf_linalg_ij_i_j_x;
    unit_test_factory<linalg_ij_ji_test> m_utf_linalg_ij_ji;
    unit_test_factory<linalg_i_ipq_qp_x_test> m_utf_linalg_i_ipq_qp_x;
    unit_test_factory<linalg_ij_ip_jp_x_test> m_utf_linalg_ij_ip_jp_x;
    unit_test_factory<linalg_ij_ip_pj_x_test> m_utf_linalg_ij_ip_pj_x;
    unit_test_factory<linalg_ij_pi_jp_x_test> m_utf_linalg_ij_pi_jp_x;
    unit_test_factory<linalg_ij_pi_pj_x_test> m_utf_linalg_ij_pi_pj_x;
    unit_test_factory<linalg_ij_pji_p_x_test> m_utf_linalg_ij_pji_p_x;
    unit_test_factory<linalg_ij_ipq_jqp_x_test> m_utf_linalg_ij_ipq_jqp_x;
    unit_test_factory<linalg_ijk_ip_pkj_x_test> m_utf_linalg_ijk_ip_pkj_x;
    unit_test_factory<linalg_ijk_pi_pkj_x_test> m_utf_linalg_ijk_pi_pkj_x;
    unit_test_factory<linalg_ijk_ipq_kjqp_x_test>
        m_utf_linalg_ijk_ipq_kjqp_x;
    unit_test_factory<linalg_ijk_ipkq_jpq_x_test>
        m_utf_linalg_ijk_ipkq_jpq_x;
    unit_test_factory<linalg_ijk_pikq_jpq_x_test>
        m_utf_linalg_ijk_pikq_jpq_x;
    unit_test_factory<linalg_ijk_piqk_jpq_x_test>
        m_utf_linalg_ijk_piqk_jpq_x;
    unit_test_factory<linalg_ijk_pkiq_pjq_x_test>
        m_utf_linalg_ijk_pkiq_pjq_x;
    unit_test_factory<linalg_ijkl_ikp_jpl_x_test>
        m_utf_linalg_ijkl_ikp_jpl_x;
    unit_test_factory<linalg_ijkl_ipj_plk_x_test>
        m_utf_linalg_ijkl_ipj_plk_x;
    unit_test_factory<linalg_ijkl_ipl_jpk_x_test>
        m_utf_linalg_ijkl_ipl_jpk_x;
    unit_test_factory<linalg_ijkl_ipl_kpj_x_test>
        m_utf_linalg_ijkl_ipl_kpj_x;
    unit_test_factory<linalg_ijkl_ipkq_pljq_x_test>
        m_utf_linalg_ijkl_ipkq_pljq_x;
    unit_test_factory<linalg_ijkl_iplq_kpjq_x_test>
        m_utf_linalg_ijkl_iplq_kpjq_x;
    unit_test_factory<linalg_ijkl_iplq_pkjq_x_test>
        m_utf_linalg_ijkl_iplq_pkjq_x;
    unit_test_factory<linalg_ijkl_iplq_pkqj_x_test>
        m_utf_linalg_ijkl_iplq_pkqj_x;
    unit_test_factory<linalg_ijkl_ipqk_pljq_x_test>
        m_utf_linalg_ijkl_ipqk_pljq_x;
    unit_test_factory<linalg_ijkl_ipql_pkjq_x_test>
        m_utf_linalg_ijkl_ipql_pkjq_x;
    unit_test_factory<linalg_ijkl_ipql_pkqj_x_test>
        m_utf_linalg_ijkl_ipql_pkqj_x;
    unit_test_factory<linalg_ijkl_ipql_qkpj_x_test>
        m_utf_linalg_ijkl_ipql_qkpj_x;
    unit_test_factory<linalg_ijkl_ipql_qpkj_x_test>
        m_utf_linalg_ijkl_ipql_qpkj_x;
    unit_test_factory<linalg_ijkl_pikq_pljq_x_test>
        m_utf_linalg_ijkl_pikq_pljq_x;
    unit_test_factory<linalg_ijkl_pilq_kpjq_x_test>
        m_utf_linalg_ijkl_pilq_kpjq_x;
    unit_test_factory<linalg_ijkl_piqk_pljq_x_test>
        m_utf_linalg_ijkl_piqk_pljq_x;
    unit_test_factory<linalg_ijkl_pilq_pkjq_x_test>
        m_utf_linalg_ijkl_pilq_pkjq_x;
    unit_test_factory<linalg_ijkl_piql_kpqj_x_test>
        m_utf_linalg_ijkl_piql_kpqj_x;
    unit_test_factory<linalg_ijkl_piql_pkjq_x_test>
        m_utf_linalg_ijkl_piql_pkjq_x;
    unit_test_factory<linalg_ijkl_piql_pkqj_x_test>
        m_utf_linalg_ijkl_piql_pkqj_x;
    unit_test_factory<linalg_ijkl_piql_qkpj_x_test>
        m_utf_linalg_ijkl_piql_qkpj_x;
    unit_test_factory<linalg_ijkl_piql_qpkj_x_test>
        m_utf_linalg_ijkl_piql_qpkj_x;
    unit_test_factory<linalg_ijkl_pkiq_jplq_x_test>
        m_utf_linalg_ijkl_pkiq_jplq_x;
    unit_test_factory<linalg_ijkl_pkiq_jpql_x_test>
        m_utf_linalg_ijkl_pkiq_jpql_x;
    unit_test_factory<linalg_ijkl_pkiq_pjlq_x_test>
        m_utf_linalg_ijkl_pkiq_pjlq_x;
    unit_test_factory<linalg_ijkl_pkiq_pjql_x_test>
        m_utf_linalg_ijkl_pkiq_pjql_x;
    unit_test_factory<linalg_ijkl_pliq_jpkq_x_test>
        m_utf_linalg_ijkl_pliq_jpkq_x;
    unit_test_factory<linalg_ijkl_pliq_jpqk_x_test>
        m_utf_linalg_ijkl_pliq_jpqk_x;
    unit_test_factory<linalg_ijkl_pliq_pjqk_x_test>
        m_utf_linalg_ijkl_pliq_pjqk_x;
    unit_test_factory<linalg_ijklm_ipkm_jlp_x_test>
        m_utf_linalg_ijklm_ipkm_jlp_x;
*/

public:
    //! Creates the suite
    libtensor_linalg_cublas_suite();

};


} // namespace libtensor

#endif // LIBTENSOR_LIBTENSOR_LINALG_CUBLAS_SUITE_H

