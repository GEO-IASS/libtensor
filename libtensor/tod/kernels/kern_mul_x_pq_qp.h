#ifndef LIBTENSOR_KERN_MUL_X_PQ_QP_H
#define LIBTENSOR_KERN_MUL_X_PQ_QP_H

#include "kern_mul_x_p_p.h"

namespace libtensor {


/**
    \ingroup libtensor_tod_kernel
 **/
class kern_mul_x_pq_qp : public kernel_base<2, 1> {
    friend class kern_mul_i_ipq_qp;

public:
    static const char *k_clazz; //!< Kernel name

private:
    double m_d;
    size_t m_np, m_nq;
    size_t m_spa, m_sqb;

public:
    virtual ~kern_mul_x_pq_qp() { }

    virtual const char *get_name() const {
        return k_clazz;
    }

    virtual void run(const loop_registers<2, 1> &r);

    static kernel_base<2, 1> *match(const kern_mul_x_p_p &z,
        list_t &in, list_t &out);

};


} // namespace libtensor

#endif // LIBTENSOR_KERN_MUL_X_PQ_QP_H
