#ifndef LIBTENSOR_GEN_BTO_CONTRACT2_BLOCK_IMPL_H
#define LIBTENSOR_GEN_BTO_CONTRACT2_BLOCK_IMPL_H

#include "gen_bto_contract2_clst.h"
#include "gen_bto_contract2_block.h"

namespace libtensor {


template<size_t N, size_t M, size_t K, typename Traits, typename Timed>
gen_bto_contract2_block<N, M, K, Traits, Timed>::gen_bto_contract2_block(
    const contraction2<N, M, K> &contr,
    gen_block_tensor_rd_i<NA, bti_traits> &bta,
    const symmetry<NA, element_type> &syma,
    const scalar_transf<element_type> &ka,
    gen_block_tensor_rd_i<NB, bti_traits> &btb,
    const symmetry<NB, element_type> &symb,
    const scalar_transf<element_type> &kb,
    const block_index_space<NC> &bisc,
    const scalar_transf<element_type> &kc) :

    m_contr(contr),
    m_bta(bta), m_bidimsa(m_bta.get_bis().get_block_index_dims()),
    m_ola(syma), m_ka(ka),
    m_btb(btb), m_bidimsb(m_btb.get_bis().get_block_index_dims()),
    m_olb(symb), m_kb(kb),
    m_bidimsc(bisc.get_block_index_dims()), m_kc(kc) {

}


template<size_t N, size_t M, size_t K, typename Traits, typename Timed>
void gen_bto_contract2_block<N, M, K, Traits, Timed>::compute_block(
    bool zero,
    const index<NC> &idxc,
    const tensor_transf<NC, element_type> &trc,
    wr_block_c_type &blkc) {

    typedef typename gen_bto_contract2_clst<N, M, K, Traits>::contr_list
        contr_list;
    typedef typename Traits::template to_contract2_type<N, M, K>::type
        to_contract2;
    typedef typename Traits::template to_set_type<NC>::type to_set;

    gen_block_tensor_rd_ctrl<NA, bti_traits> ca(m_bta);
    gen_block_tensor_rd_ctrl<NB, bti_traits> cb(m_btb);

    //  Prepare contraction list
    gen_bto_contract2_block::start_timer("contract_block::clst");
    gen_bto_contract2_clst<N, M, K, Traits> clstop(m_contr, m_bta, m_btb,
        m_ola, m_olb, m_bidimsa, m_bidimsb, m_bidimsc, idxc);
    clstop.build_list(false); // Build full contraction list
    const contr_list &clst = clstop.get_clst();
    gen_bto_contract2_block::stop_timer("contract_block::clst");

    //  Keep track of checked out blocks
    typedef std::map<size_t, rd_block_a_type*> coba_map;
    typedef std::map<size_t, rd_block_b_type*> cobb_map;
    coba_map coba;
    cobb_map cobb;

    //  Tensor contraction operation
    std::auto_ptr<to_contract2> op;

    //  Go through the contraction list and prepare the contraction
    for(typename contr_list::const_iterator i = clst.begin();
        i != clst.end(); ++i) {

        index<NA> ia;
        index<NB> ib;
        abs_index<NA>::get_index(i->aia, m_bidimsa, ia);
        abs_index<NB>::get_index(i->aib, m_bidimsb, ib);

        bool zeroa = ca.req_is_zero_block(ia);
        bool zerob = cb.req_is_zero_block(ib);
        if(zeroa || zerob) continue;

        if(coba.find(i->aia) == coba.end()) {
            rd_block_a_type &blka = ca.req_const_block(ia);
            coba[i->aia] = &blka;
        }
        if(cobb.find(i->aib) == cobb.end()) {
            rd_block_b_type &blkb = cb.req_const_block(ib);
            cobb[i->aib] = &blkb;
        }
        rd_block_a_type &blka = *coba[i->aia];
        rd_block_b_type &blkb = *cobb[i->aib];

        tensor_transf<NA, element_type> trainv(i->tra);
        trainv.invert();
        tensor_transf<NB, element_type> trbinv(i->trb);
        trbinv.invert();

        contraction2<N, M, K> contr(m_contr);
        contr.permute_a(trainv.get_perm());
        contr.permute_b(trbinv.get_perm());
        contr.permute_c(trc.get_perm());

        scalar_transf<element_type> ka(trainv.get_scalar_tr());
        scalar_transf<element_type> kb(trbinv.get_scalar_tr());
        scalar_transf<element_type> kc(m_kc);

        ka.transform(m_ka);
        kb.transform(m_kb);
        kc.transform(trc.get_scalar_tr());

        if(op.get() == 0) {
            op = std::auto_ptr<to_contract2>(
                new to_contract2(contr, blka, ka, blkb, kb, kc));
        } else {
            op->add_args(contr, blka, ka, blkb, kb, kc);
        }
    }

    //  Execute the contraction
    if(op.get() == 0) {
        if(zero) to_set().perform(blkc);
    } else {
        op->perform(zero, blkc);
    }

    //  Return input blocks
    for(typename coba_map::iterator i = coba.begin(); i != coba.end(); ++i) {
        index<NA> ia;
        abs_index<NA>::get_index(i->first, m_bidimsa, ia);
        ca.ret_const_block(ia);
    }
    for(typename cobb_map::iterator i = cobb.begin(); i != cobb.end(); ++i) {
        index<NB> ib;
        abs_index<NB>::get_index(i->first, m_bidimsb, ib);
        cb.ret_const_block(ib);
    }
}


} // namespace libtensor

#endif // LIBTENSOR_GEN_BTO_CONTRACT2_BLOCK_IMPL_H
