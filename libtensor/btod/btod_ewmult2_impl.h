#ifndef LIBTENSOR_BTOD_EWMULT2_IMPL_H
#define LIBTENSOR_BTOD_EWMULT2_IMPL_H

#include "../core/orbit.h"
#include "../core/orbit_list.h"
#include "../core/permutation_builder.h"
#include <libtensor/dense_tensor/tod_ewmult2.h>
#include "../symmetry/so_dirprod.h"
#include "../symmetry/so_merge.h"
#include "bad_block_index_space.h"

namespace libtensor {


template<size_t N, size_t M, size_t K>
const char *btod_ewmult2<N, M, K>::k_clazz = "btod_ewmult2<N, M, K>";


template<size_t N, size_t M, size_t K>
btod_ewmult2<N, M, K>::btod_ewmult2(block_tensor_i<k_ordera, double> &bta,
    block_tensor_i<k_orderb, double> &btb, double d) :

    m_bta(bta), m_btb(btb), m_d(d),
    m_bisc(make_bisc(bta.get_bis(), permutation<k_ordera>(),
        btb.get_bis(), permutation<k_orderb>(),
        permutation<k_orderc>())),
    m_symc(m_bisc), m_sch(m_bisc.get_block_index_dims()) {

    make_symc();
    make_schedule();
}


template<size_t N, size_t M, size_t K>
btod_ewmult2<N, M, K>::btod_ewmult2(block_tensor_i<k_ordera, double> &bta,
    const permutation<k_ordera> &perma,
    block_tensor_i<k_orderb, double> &btb,
    const permutation<k_orderb> &permb, const permutation<k_orderc> &permc,
    double d) :

    m_bta(bta), m_perma(perma), m_btb(btb), m_permb(permb), m_permc(permc),
    m_d(d),
    m_bisc(make_bisc(bta.get_bis(), perma, btb.get_bis(), permb, permc)),
    m_symc(m_bisc), m_sch(m_bisc.get_block_index_dims()) {

    make_symc();
    make_schedule();
}


template<size_t N, size_t M, size_t K>
btod_ewmult2<N, M, K>::~btod_ewmult2() {

}


template<size_t N, size_t M, size_t K>
void btod_ewmult2<N, M, K>::sync_on() {

    block_tensor_ctrl<k_ordera, double>(m_bta).req_sync_on();
    block_tensor_ctrl<k_orderb, double>(m_btb).req_sync_on();
}


template<size_t N, size_t M, size_t K>
void btod_ewmult2<N, M, K>::sync_off() {

    block_tensor_ctrl<k_ordera, double>(m_bta).req_sync_off();
    block_tensor_ctrl<k_orderb, double>(m_btb).req_sync_off();
}

/*
template<size_t N, size_t M, size_t K>
void btod_ewmult2<N, M, K>::compute_block(dense_tensor_i<k_orderc, double> &blk,
    const index<k_orderc> &bidx) {

    tensor_transf<k_orderc, double> tr0;
    compute_block_impl(blk, bidx, tr0, true, 1.0);
}*/


template<size_t N, size_t M, size_t K>
void btod_ewmult2<N, M, K>::compute_block(bool zero,
    dense_tensor_i<k_orderc, double> &blk, const index<k_orderc> &bidx,
    const tensor_transf<k_orderc, double> &tr, const double &d) {

    compute_block_impl(blk, bidx, tr, zero, d);
}


template<size_t N, size_t M, size_t K>
block_index_space<N + M + K> btod_ewmult2<N, M, K>::make_bisc(
    const block_index_space<k_ordera> &bisa,
    const permutation<k_ordera> &perma,
    const block_index_space<k_orderb> &bisb,
    const permutation<k_orderb> &permb,
    const permutation<k_orderc> &permc) {

    static const char *method = "make_bisc()";

    //  Block index spaces and dimensions of A and B
    //  in the standard index ordering:
    //  A(ij..pq..) B(mn..pq..)

    block_index_space<k_ordera> bisa1(bisa);
    bisa1.permute(perma);
    block_index_space<k_orderb> bisb1(bisb);
    bisb1.permute(permb);
    dimensions<k_ordera> dimsa1(bisa1.get_dims());
    dimensions<k_orderb> dimsb1(bisb1.get_dims());

    //  Build the dimensions of the result

    index<k_orderc> i1, i2;
    for(size_t i = 0; i < N; i++) i2[i] = dimsa1[i] - 1;
    for(size_t i = 0; i < M; i++) i2[N + i] = dimsb1[i] - 1;
    for(size_t i = 0; i < K; i++) {
        if(dimsa1[N + i] != dimsb1[M + i]) {
            throw bad_block_index_space(g_ns, k_clazz, method,
                __FILE__, __LINE__, "bta,btb");
        }
        if(!bisa1.get_splits(bisa1.get_type(N + i)).equals(
            bisb1.get_splits(bisb1.get_type(M + i)))) {
            throw bad_block_index_space(g_ns, k_clazz, method,
                __FILE__, __LINE__, "bta,btb");
        }
        i2[N + M + i] = dimsa1[N + i] - 1;
    }
    dimensions<k_orderc> dimsc(index_range<k_orderc>(i1, i2));
    block_index_space<k_orderc> bisc(dimsc);

    //  Transfer block index space splits

    mask<k_orderc> mfin, mdone, mtodo;
    for(size_t i = 0; i < k_orderc; i++) mfin[i] = true;
    while(!mdone.equals(mfin)) {
        size_t i;
        for(i = 0; i < k_orderc; i++) mtodo[i] = false;
        for(i = 0; i < k_orderc; i++) if(!mdone[k_orderc - i - 1]) break;
        i = k_orderc - i - 1;
        const split_points *sp = 0;
        if(i < N) {
            size_t j = i;
            size_t typa = bisa1.get_type(j);
            for(size_t k = 0; k < N; k++) {
                mtodo[k] = (bisa1.get_type(k) == typa);
            }
            sp = &bisa1.get_splits(typa);
        } else if(i < N + M) {
            size_t j = i - N;
            size_t typb = bisb1.get_type(j);
            for(size_t k = 0; k < M; k++) {
                mtodo[N + k] = (bisb1.get_type(k) == typb);
            }
            sp = &bisb1.get_splits(typb);
        } else {
            size_t j = i - N - M;
            size_t typa = bisa1.get_type(N + j);
            size_t typb = bisb1.get_type(M + j);
            for(size_t k = 0; k < N; k++) {
                mtodo[k] = (bisa1.get_type(k) == typa);
            }
            for(size_t k = 0; k < M; k++) {
                mtodo[N + k] = (bisb1.get_type(k) == typb);
            }
            for(size_t k = 0; k < K; k++) {
                bool b1 = (bisa1.get_type(N + k) == typa);
                bool b2 = (bisb1.get_type(M + k) == typb);
                if(b1 != b2) {
                    throw bad_block_index_space(g_ns,
                        k_clazz, method,
                        __FILE__, __LINE__, "bta,btb");
                }
                mtodo[N + M + k] = b1;
            }
            sp = &bisa1.get_splits(typa);
        }
        for(size_t j = 0; j < sp->get_num_points(); j++) {
            bisc.split(mtodo, (*sp)[j]);
        }
        mdone |= mtodo;
    }

    bisc.permute(permc);
    return bisc;
}


template<size_t N, size_t M, size_t K>
void btod_ewmult2<N, M, K>::make_symc() {

    sequence<k_ordera, size_t> seq2a;
    sequence<k_orderb, size_t> seq2b;
    sequence<k_orderc, size_t> seq2c;
    for (register size_t i = 0; i < k_ordera; i++) seq2a[i] = i;
    m_perma.apply(seq2a);
    for (register size_t i = 0, j = k_ordera; i < k_orderb; i++, j++)
        seq2b[i] = j;
    m_permb.apply(seq2b);
    for (register size_t i = 0; i < k_orderc; i++) seq2c[i] = i;
    m_permc.apply(seq2c);

    sequence<k_orderc, size_t> seq2imx, seqx;
    sequence<k_ordera + k_orderb, size_t> seq1im, seq2im, seq;
    for (register size_t i = 0; i < N; i++) {
        seq1im[i] = i;
        seq2imx[i] = seq2a[i];
    }
    for (register size_t i = 0, j = N; i < M; i++, j++) {
        seq1im[j] = j;
        seq2imx[j] = seq2b[i];
    }

    mask<k_orderc> mskx;
    mask<k_ordera + k_orderb> msk;
    for (register size_t i = 0, j = N + M; i < K; i++, j++) {
        seq1im[j] = j;
        seq2imx[j] = seq2a[i + N];
        mskx[j] = true;
        seqx[j] = i;
    }

    for (register size_t i = 0, j = k_orderc; i < K; i++, j++) {
        seq1im[j] = j;
        seq2im[j] = seq2b[i + M];
        msk[j] = true;
        seq[j] = i;
    }

    for (register size_t i = 0; i < k_orderc; i++) {
        seq2im[i] = seq2imx[seq2c[i]];
        seq[i] = seqx[seq2c[i]];
        msk[i] = mskx[seq2c[i]];
    }

    permutation_builder<k_ordera + k_orderb> pb(seq2im, seq1im);

    block_index_space_product_builder<k_ordera, k_orderb> bbx(m_bta.get_bis(),
            m_btb.get_bis(), pb.get_perm());

    symmetry<k_ordera + k_orderb, double> symx(bbx.get_bis());

    block_tensor_ctrl<k_ordera, double> ca(m_bta);
    block_tensor_ctrl<k_orderb, double> cb(m_btb);
    so_dirprod<k_ordera, k_orderb, double>(ca.req_const_symmetry(),
            cb.req_const_symmetry(), pb.get_perm()).perform(symx);

    so_merge<k_ordera + k_orderb, K, double>(symx, msk, seq).perform(m_symc);
}


template<size_t N, size_t M, size_t K>
void btod_ewmult2<N, M, K>::make_schedule() {

    block_tensor_ctrl<k_ordera, double> ctrla(m_bta);
    block_tensor_ctrl<k_orderb, double> ctrlb(m_btb);

    btod_ewmult2<N, M, K>::start_timer("make_schedule");

    orbit_list<k_orderc, double> ol(m_symc);
    for(typename orbit_list<k_orderc, double>::iterator io = ol.begin();
        io != ol.end(); io++) {

        index<k_ordera> bidxa;
        index<k_orderb> bidxb;
        index<k_orderc> bidxstd(ol.get_index(io));
        bidxstd.permute(permutation<k_orderc>(m_permc, true));
        for(size_t i = 0; i < N; i++) bidxa[i] = bidxstd[i];
        for(size_t i = 0; i < M; i++) bidxb[i] = bidxstd[N + i];
        for(size_t i = 0; i < K; i++) {
            bidxa[N + i] = bidxb[M + i] = bidxstd[N + M +i];
        }
        bidxa.permute(permutation<k_ordera>(m_perma, true));
        bidxb.permute(permutation<k_orderb>(m_permb, true));

        orbit<k_ordera, double> oa(ctrla.req_const_symmetry(), bidxa);
        orbit<k_orderb, double> ob(ctrlb.req_const_symmetry(), bidxb);
        if(!oa.is_allowed() || !ob.is_allowed()) continue;

        abs_index<k_ordera> cidxa(oa.get_abs_canonical_index(),
            m_bta.get_bis().get_block_index_dims());
        abs_index<k_orderb> cidxb(ob.get_abs_canonical_index(),
            m_btb.get_bis().get_block_index_dims());
        bool zeroa = ctrla.req_is_zero_block(cidxa.get_index());
        bool zerob = ctrlb.req_is_zero_block(cidxb.get_index());
        if(zeroa || zerob) continue;

        m_sch.insert(ol.get_abs_index(io));
    }

    btod_ewmult2<N, M, K>::stop_timer("make_schedule");
}


template<size_t N, size_t M, size_t K>
void btod_ewmult2<N, M, K>::compute_block_impl(
    dense_tensor_i<k_orderc, double> &blk, const index<k_orderc> &bidx,
    const tensor_transf<k_orderc, double> &tr, bool zero, double d) {

    block_tensor_ctrl<k_ordera, double> ctrla(m_bta);
    block_tensor_ctrl<k_orderb, double> ctrlb(m_btb);

    btod_ewmult2<N, M, K>::start_timer();

    index<k_ordera> bidxa;
    index<k_orderb> bidxb;
    index<k_orderc> bidxstd(bidx);
    bidxstd.permute(permutation<k_orderc>(m_permc, true));
    for(size_t i = 0; i < N; i++) bidxa[i] = bidxstd[i];
    for(size_t i = 0; i < M; i++) bidxb[i] = bidxstd[N + i];
    for(size_t i = 0; i < K; i++) {
        bidxa[N + i] = bidxb[M + i] = bidxstd[N + M +i];
    }
    bidxa.permute(permutation<k_ordera>(m_perma, true));
    bidxb.permute(permutation<k_orderb>(m_permb, true));

    orbit<k_ordera, double> oa(ctrla.req_const_symmetry(), bidxa);
    orbit<k_orderb, double> ob(ctrlb.req_const_symmetry(), bidxb);

    abs_index<k_ordera> cidxa(oa.get_abs_canonical_index(),
        m_bta.get_bis().get_block_index_dims());
    const tensor_transf<k_ordera, double> &tra = oa.get_transf(bidxa);

    abs_index<k_orderb> cidxb(ob.get_abs_canonical_index(),
        m_btb.get_bis().get_block_index_dims());
    const tensor_transf<k_orderb, double> &trb = ob.get_transf(bidxb);

    permutation<k_ordera> perma(tra.get_perm());
    perma.permute(m_perma);
    permutation<k_orderb> permb(trb.get_perm());
    permb.permute(m_permb);
    permutation<k_orderc> permc(m_permc);

    bool zeroa = ctrla.req_is_zero_block(cidxa.get_index());
    bool zerob = ctrlb.req_is_zero_block(cidxb.get_index());

    if(zeroa || zerob) {
        btod_ewmult2<N, M, K>::start_timer("zero");
        if(zero) tod_set<k_orderc>().perform(blk);
        btod_ewmult2<N, M, K>::stop_timer("zero");
        btod_ewmult2<N, M, K>::stop_timer();
        return;
    }

    dense_tensor_i<k_ordera, double> &blka = ctrla.req_block(cidxa.get_index());
    dense_tensor_i<k_orderb, double> &blkb = ctrlb.req_block(cidxb.get_index());

    permc.permute(tr.get_perm());
    double k = m_d * tra.get_scalar_tr().get_coeff() *
            trb.get_scalar_tr().get_coeff() * tr.get_scalar_tr().get_coeff();
    tod_ewmult2<N, M, K>(blka, perma, blkb, permb, permc, k).
        perform(zero, d, blk);

    ctrla.ret_block(cidxa.get_index());
    ctrlb.ret_block(cidxb.get_index());

    btod_ewmult2<N, M, K>::stop_timer();
}


} // namespace libtensor

#endif // LIBTENSOR_BTOD_EWMULT2_IMPL_H
