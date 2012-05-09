#ifndef LIBTENSOR_KERN_MUL_IJ_J_I_H
#define LIBTENSOR_KERN_MUL_IJ_J_I_H

#include "kern_mul_i_i_x.h"

namespace libtensor {


/** \brief Kernel for \f$ c_{ij} = c_{ij} + a_j b_i \f$

     \ingroup libtensor_tod_kernel
 **/
class kern_mul_ij_j_i : public kernel_base<2, 1> {
public:
    static const char *k_clazz; //!< Kernel name

private:
    double m_d;
    size_t m_ni, m_nj;
    size_t m_sja, m_sib, m_sic;

public:
    virtual ~kern_mul_ij_j_i() { }

    virtual const char *get_name() const {
        return k_clazz;
    }

    virtual void run(const loop_registers<2, 1> &r);

    static kernel_base<2, 1> *match(const kern_mul_i_i_x &z,
        list_t &in, list_t &out);

};


} // namespace libtensor

#endif // LIBTENSOR_KERN_MUL_IJ_J_I_H
