#ifndef LIBTENSOR_LINALG_ESSL_LEVEL3_H
#define LIBTENSOR_LINALG_ESSL_LEVEL3_H

#include "../generic/linalg_generic_level3.h"

namespace libtensor {


/** \brief Level-3 linear algebra operations (ESSL)

    \ingroup libtensor_linalg
 **/
class linalg_essl_level3 : public linalg_generic_level3 {
public:
    static const char *k_clazz; //!< Class name

public:
    static void mul2_ij_ip_jp_x(
        void*,
        size_t ni, size_t nj, size_t np,
        const double *a, size_t sia,
        const double *b, size_t sjb,
        double *c, size_t sic,
        double d);

    static void mul2_ij_ip_pj_x(
        void*,
        size_t ni, size_t nj, size_t np,
        const double *a, size_t sia,
        const double *b, size_t spb,
        double *c, size_t sic,
        double d);

    static void mul2_ij_pi_jp_x(
        void*,
        size_t ni, size_t nj, size_t np,
        const double *a, size_t spa,
        const double *b, size_t sjb,
        double *c, size_t sic,
        double d);

    static void mul2_ij_pi_pj_x(
        void*,
        size_t ni, size_t nj, size_t np,
        const double *a, size_t spa,
        const double *b, size_t spb,
        double *c, size_t sic,
        double d);

};


} // namespace libtensor

#endif // LIBTENSOR_LINALG_ESSL_LEVEL3_H
