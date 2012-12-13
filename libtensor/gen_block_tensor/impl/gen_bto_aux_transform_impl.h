#ifndef LIBTENSOR_GEN_BTO_AUX_TRANSFORM_IMPL_H
#define LIBTENSOR_GEN_BTO_AUX_TRANSFORM_IMPL_H

#include <libtensor/core/orbit.h>
#include <libtensor/symmetry/so_copy.h>
#include "../block_stream_exception.h"
#include "../gen_bto_aux_transform.h"

namespace libtensor {


template<size_t N, typename Traits>
const char *gen_bto_aux_transform<N, Traits>::k_clazz =
    "gen_bto_aux_transform<N, Traits>";


template<size_t N, typename Traits>
gen_bto_aux_transform<N, Traits>::gen_bto_aux_transform(
    const tensor_transf_type &tra,
    const symmetry_type &symb,
    gen_block_stream_i<N, bti_traits> &out) :

    m_tra(tra), m_symb(symb.get_bis()), m_out(out), m_open(false) {

    so_copy<N, element_type>(symb).perform(m_symb);
    m_noperm = m_tra.get_perm().is_identity();
}


template<size_t N, typename Traits>
gen_bto_aux_transform<N, Traits>::~gen_bto_aux_transform() {

    if(m_open) close();
}


template<size_t N, typename Traits>
void gen_bto_aux_transform<N, Traits>::open() {

    if(m_open) {
        throw block_stream_exception(g_ns, k_clazz, "open()",
            __FILE__, __LINE__, "Stream is already open.");
    }

    m_open = true;
}


template<size_t N, typename Traits>
void gen_bto_aux_transform<N, Traits>::close() {

    if(!m_open) {
        throw block_stream_exception(g_ns, k_clazz, "close()",
            __FILE__, __LINE__, "Stream is already closed.");
    }

    m_open = false;
}


template<size_t N, typename Traits>
void gen_bto_aux_transform<N, Traits>::put(
    const index<N> &idxa,
    rd_block_type &blk,
    const tensor_transf_type &tr) {

    if(!m_open) {
        throw block_stream_exception(g_ns, k_clazz, "put()",
            __FILE__, __LINE__, "Stream is not ready.");
    }

    tensor_transf_type tra1(tr);
    tra1.transform(m_tra);

    if(m_noperm) {
        m_out.put(idxa, blk, tra1);
    } else {
        index<N> idxb(idxa);
        idxb.permute(m_tra.get_perm());
        orbit<N, element_type> ob(m_symb, idxb, false);
        tra1.transform(tensor_transf_type(ob.get_transf(idxb), true));
        m_out.put(ob.get_cindex(), blk, tra1);
    }
}


} // namespace libtensor

#endif // LIBTENSOR_GEN_BTO_AUX_TRANSFORM_IMPL_H
