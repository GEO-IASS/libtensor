#ifndef LIBTENSOR_TOD_MULT_IMPL_H
#define LIBTENSOR_TOD_MULT_IMPL_H

#include <libtensor/dense_tensor/dense_tensor_ctrl.h>
#include <libtensor/tod/bad_dimensions.h>
#include "../tod_mult.h"

namespace libtensor {


template<size_t N>
const char *tod_mult<N>::k_clazz = "tod_mult<N>";


template<size_t N>
tod_mult<N>::tod_mult(dense_tensor_rd_i<N, double> &ta,
    dense_tensor_rd_i<N, double> &tb, bool recip, double c) :

    m_ta(ta), m_tb(tb), m_dimsc(ta.get_dims()), m_recip(recip), m_c(c) {

    static const char *method = "tod_mult(dense_tensor_rd_i<N, double>&, "
        "dense_tensor_rd_i<N, double>&, bool, double)";

    if(!ta.get_dims().equals(tb.get_dims())) {
        throw bad_dimensions(g_ns, k_clazz, method, __FILE__, __LINE__,
            "ta,tb");
    }
}


template<size_t N>
tod_mult<N>::tod_mult(dense_tensor_rd_i<N, double> &ta,
    const permutation<N> &pa, dense_tensor_rd_i<N, double> &tb,
    const permutation<N> &pb, bool recip, double c) :

    m_ta(ta), m_tb(tb), m_perma(pa), m_permb(pb),
    m_dimsc(ta.get_dims()), m_recip(recip), m_c(c) {

    static const char *method = "tod_mult(dense_tensor_rd_i<N, double>&,"
        " permutation<N>, dense_tensor_rd_i<N, double>&, permutation<N>, bool)";

    m_dimsc.permute(pa);
    dimensions<N> dimsb(tb.get_dims());
    dimsb.permute(pb);

    if(!m_dimsc.equals(dimsb)) {
        throw bad_dimensions(g_ns, k_clazz, method, __FILE__, __LINE__,
            "ta, tb");
    }
}


template<size_t N>
void tod_mult<N>::prefetch() {

    dense_tensor_rd_ctrl<N, double>(m_ta).req_prefetch();
    dense_tensor_rd_ctrl<N, double>(m_tb).req_prefetch();

}


template<size_t N>
void tod_mult<N>::perform(dense_tensor_wr_i<N, double> &tc) {

    perform(true, 1.0, tc);
}


template<size_t N>
void tod_mult<N>::perform(dense_tensor_wr_i<N, double> &tc, double c) {

    perform(false, c, tc);
}


template<size_t N>
void tod_mult<N>::perform(bool zero, double c,
    dense_tensor_wr_i<N, double> &tc) {

    static const char *method = "perform(bool, double, "
        "dense_tensor_wr_i<N, double>&)";

    if(!m_dimsc.equals(tc.get_dims())) {
        throw bad_dimensions(g_ns, k_clazz, method, __FILE__, __LINE__, "tc");
    }

    typedef typename loop_list_elem::list_t list_t;
    typedef typename loop_list_elem::registers registers_t;
    typedef typename loop_list_elem::node node_t;

    tod_mult<N>::start_timer();

    try {

    dense_tensor_rd_ctrl<N, double> ca(m_ta), cb(m_tb);
    dense_tensor_wr_ctrl<N, double> cc(tc);
    ca.req_prefetch();
    cb.req_prefetch();
    cc.req_prefetch();

    const dimensions<N> &dimsa = m_ta.get_dims();
    const dimensions<N> &dimsb = m_tb.get_dims();
    const dimensions<N> &dimsc = tc.get_dims();

    list_t loop;
    build_loop(loop, dimsa, m_perma, dimsb, m_permb, dimsc);

    const double *pa = ca.req_const_dataptr();
    const double *pb = cb.req_const_dataptr();
    double *pc = cc.req_dataptr();

    registers_t r;
    r.m_ptra[0] = pa;
    r.m_ptra[1] = pb;
    r.m_ptrb[0] = pc;
    r.m_ptra_end[0] = pa + dimsa.get_size();
    r.m_ptra_end[1] = pb + dimsb.get_size();
    r.m_ptrb_end[0] = pc + dimsc.get_size();

    loop_list_elem::run_loop(loop, r, m_c * c, !zero, m_recip);

    cc.ret_dataptr(pc); pc = 0;
    cb.ret_const_dataptr(pb); pb = 0;
    ca.ret_const_dataptr(pa); pa = 0;

    } catch (...) {
        tod_mult<N>::stop_timer();
        throw;
    }

    tod_mult<N>::stop_timer();
}


template<size_t N>
void tod_mult<N>::build_loop(typename loop_list_elem::list_t &loop,
    const dimensions<N> &dimsa, const permutation<N> &perma,
    const dimensions<N> &dimsb, const permutation<N> &permb,
    const dimensions<N> &dimsc) {

    typedef typename loop_list_elem::iterator_t iterator_t;
    typedef typename loop_list_elem::node node_t;

    sequence<N, size_t> mapa(0), mapb(0);
    for(size_t i = 0; i < N; i++) mapa[i] = mapb[i] = i;
    perma.apply(mapa);
    permb.apply(mapb);

    for (size_t idxc = 0; idxc < N; ) {
        size_t len = 1;
        size_t idxa = mapa[idxc], idxb = mapb[idxc];

        do {
            len *= dimsa.get_dim(idxa);
            idxa++; idxb++; idxc++;
        } while (idxc < N && mapa[idxc] == idxa && mapb[idxc] == idxb);

        iterator_t inode = loop.insert(loop.end(), node_t(len));
        inode->stepa(0) = dimsa.get_increment(idxa - 1);
        inode->stepa(1) = dimsb.get_increment(idxb - 1);
        inode->stepb(0) = dimsc.get_increment(idxc - 1);
    }

}


} // namespace libtensor

#endif // LIBTENSOR_TOD_MULT_IMPL_H
