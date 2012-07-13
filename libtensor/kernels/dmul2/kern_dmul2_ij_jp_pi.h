#ifndef LIBTENSOR_KERN_DMUL2_IJ_JP_PI_H
#define LIBTENSOR_KERN_DMUL2_IJ_JP_PI_H

#include "kern_dmul2_i_p_pi.h"

namespace libtensor {


/** \brief Specialized kernel for \f$ c_{ij} = c_{ij} + a_{jp} b_{pi} d \f$

     \ingroup libtensor_kernels
 **/
class kern_dmul2_ij_jp_pi : public kernel_base<2, 1> {
    friend class kern_mul_ijk_kp_ipj;
    friend class kern_mul_ijk_kp_jpi;

public:
    static const char *k_clazz; //!< Kernel name

private:
    double m_d;
    size_t m_ni, m_nj, m_np;
    size_t m_sja, m_spb, m_sic;

public:
    virtual ~kern_dmul2_ij_jp_pi() { }

    virtual const char *get_name() const {
        return k_clazz;
    }

    virtual void run(const loop_registers<2, 1> &r);

    static kernel_base<2, 1> *match(const kern_dmul2_i_p_pi &z,
        list_t &in, list_t &out);

};


} // namespace libtensor

#endif // LIBTENSOR_KERN_DMUL2_IJ_JP_PI_H