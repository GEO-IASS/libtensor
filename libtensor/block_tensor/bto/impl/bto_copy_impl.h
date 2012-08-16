#ifndef LIBTENSOR_BTO_COPY_IMPL_H
#define LIBTENSOR_BTO_COPY_IMPL_H

#include <libtensor/core/orbit.h>
#include <libtensor/core/orbit_list.h>
#include <libtensor/symmetry/so_copy.h>
#include <libtensor/symmetry/so_permute.h>

namespace libtensor {


template<size_t N, typename Traits>
const char *bto_copy<N, Traits>::k_clazz = "bto_copy<N, Traits>";


template<size_t N, typename Traits>
bto_copy<N, Traits>::bto_copy(block_tensor_t &bta, const tensor_transf_t &tr) :

    m_bta(bta), m_tr(tr), m_bis(m_bta.get_bis()),
    m_bidims(m_bis.get_block_index_dims()), m_sym(m_bis), m_sch(m_bidims) {

    typedef typename Traits::template block_tensor_ctrl_type<N>::type
        block_tensor_ctrl_t;

    block_tensor_ctrl_t ctrla(m_bta);
    so_copy<N, element_t>(ctrla.req_const_symmetry()).perform(m_sym);
    make_schedule();
}


template<size_t N, typename Traits>
bto_copy<N, Traits>::bto_copy(block_tensor_t &bta, const scalar_transf_t &c) :

    m_bta(bta), m_tr(permutation<N>(), c), m_bis(m_bta.get_bis()),
    m_bidims(m_bis.get_block_index_dims()), m_sym(m_bis), m_sch(m_bidims) {

    typedef typename Traits::template block_tensor_ctrl_type<N>::type
        block_tensor_ctrl_t;

    block_tensor_ctrl_t ctrla(m_bta);
    so_copy<N, element_t>(ctrla.req_const_symmetry()).perform(m_sym);
    make_schedule();
}


template<size_t N, typename Traits>
bto_copy<N, Traits>::bto_copy(block_tensor_t &bta, const permutation<N> &p,
    const scalar_transf_t &c) :

    m_bta(bta), m_tr(p, c), m_bis(mk_bis(m_bta.get_bis(), p)),
    m_bidims(m_bis.get_block_index_dims()), m_sym(m_bis), m_sch(m_bidims) {

    typedef typename Traits::template block_tensor_ctrl_type<N>::type
        block_tensor_ctrl_t;

    block_tensor_ctrl_t ctrla(m_bta);
    so_permute<N, element_t>(ctrla.req_const_symmetry(),
            m_tr.get_perm()).perform(m_sym);
    make_schedule();
}


template<size_t N, typename Traits>
void bto_copy<N, Traits>::sync_on() {

    typedef typename Traits::template block_tensor_ctrl_type<N>::type
        block_tensor_ctrl_t;

    block_tensor_ctrl_t ctrla(m_bta);
    ctrla.req_sync_on();
}


template<size_t N, typename Traits>
void bto_copy<N, Traits>::sync_off() {

    typedef typename Traits::template block_tensor_ctrl_type<N>::type
        block_tensor_ctrl_t;

    block_tensor_ctrl_t ctrla(m_bta);
    ctrla.req_sync_off();
}


template<size_t N, typename Traits>
void bto_copy<N, Traits>::compute_block(bool zero, block_t &blk,
    const index<N> &ib, const tensor_transf_t &tr, const element_t &c) {

    typedef typename Traits::template block_tensor_ctrl_type<N>::type
        block_tensor_ctrl_t;
    typedef typename Traits::template to_set_type<N>::type to_set_t;
    typedef typename Traits::template to_copy_type<N>::type to_copy_t;

    bto_copy<N, Traits>::start_timer("compute_block");

    block_tensor_ctrl_t ctrla(m_bta);
    dimensions<N> bidimsa = m_bta.get_bis().get_block_index_dims();

    tensor_transf_t trinv(m_tr, true);

    //  Corresponding index in A
    index<N> ia(ib);
    ia.permute(trinv.get_perm());

    //  Find the canonical index in A
    orbit<N, double> oa(ctrla.req_const_symmetry(), ia);
    abs_index<N> acia(oa.get_abs_canonical_index(), bidimsa);


    //  Transformation for block from canonical A to B
    tensor_transf_t tra(oa.get_transf(ia));
    tra.transform(m_tr).transform(scalar_transf_t(c));
    tra.transform(tr);

    if(zero) to_set_t().perform(blk);
    if(!ctrla.req_is_zero_block(acia.get_index())) {
        block_t &blka = ctrla.req_block(acia.get_index());
        to_copy_t(blka, tra).perform(false, Traits::identity(), blk);
        ctrla.ret_block(acia.get_index());
    }

    bto_copy<N, Traits>::stop_timer("compute_block");
}


template<size_t N, typename Traits>
void bto_copy<N, Traits>::make_schedule() {

    typedef typename Traits::template block_tensor_ctrl_type<N>::type
        block_tensor_ctrl_t;

    bto_copy<N, Traits>::start_timer("make_schedule");

    block_tensor_ctrl_t ctrla(m_bta);
    dimensions<N> bidimsa = m_bta.get_bis().get_block_index_dims();

    bool identity = m_tr.get_perm().is_identity();

    orbit_list<N, element_t> ola(ctrla.req_const_symmetry());
    for(typename orbit_list<N, element_t>::iterator ioa = ola.begin();
        ioa != ola.end(); ioa++) {

        if(ctrla.req_is_zero_block(ola.get_index(ioa))) continue;

        if(!identity) {
            index<N> bib(ola.get_index(ioa)); bib.permute(m_tr.get_perm());
            orbit<N, element_t> ob(m_sym, bib);
            m_sch.insert(ob.get_abs_canonical_index());
        } else {
            m_sch.insert(ola.get_abs_index(ioa));
        }
    }

    bto_copy<N, Traits>::stop_timer("make_schedule");
}


template<size_t N, typename Traits>
block_index_space<N> bto_copy<N, Traits>::mk_bis(
        const block_index_space<N> &bis, const permutation<N> &perm) {

    block_index_space<N> bis1(bis);
    bis1.permute(perm);
    return bis1;
}


} // namespace libtensor

#endif // LIBTENSOR_BTOD_COPY_IMPL_H
