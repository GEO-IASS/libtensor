#ifndef LIBTENSOR_CTF_DENSE_TENSOR_IMPL_H
#define LIBTENSOR_CTF_DENSE_TENSOR_IMPL_H

#include <algorithm>
#include <libtensor/exception.h>
#include "../ctf_error.h"
#include "../ctf_dense_tensor.h"
#include "ctf_world.h"

namespace libtensor {


template<size_t N, typename T>
const char ctf_dense_tensor<N, T>::k_clazz[] = "ctf_dense_tensor<N, T>";


template<size_t N, typename T>
ctf_dense_tensor<N, T>::ctf_dense_tensor(const dimensions<N> &dims) :

    m_dims(dims), m_tens(0) {

    static const char method[] = "ctf_dense_tensor(const dimensions<N>&)";

#ifdef LIBTENSOR_DEBUG
    if(m_dims.get_size() == 0) {
        throw bad_parameter(g_ns, k_clazz, method, __FILE__, __LINE__, "dims");
    }
#endif // LIBTENSOR_DEBUG

    ctf_symmetry<N, T> sym;
    on_reset_symmetry(sym);
}


template<size_t N, typename T>
ctf_dense_tensor<N, T>::ctf_dense_tensor(const dimensions<N> &dims,
    const ctf_symmetry<N, T> &sym) :

    m_dims(dims), m_tens(0) {

    static const char method[] =
        "ctf_dense_tensor(const dimensions<N>&, const ctf_symmetry<N, T>&)";

#ifdef LIBTENSOR_DEBUG
    if(m_dims.get_size() == 0) {
        throw bad_parameter(g_ns, k_clazz, method, __FILE__, __LINE__, "dims");
    }
#endif // LIBTENSOR_DEBUG

    on_reset_symmetry(sym);
}


template<size_t N, typename T>
ctf_dense_tensor<N, T>::~ctf_dense_tensor() {

    cleanup();
}


template<size_t N, typename T>
void ctf_dense_tensor<N, T>::cleanup() {

    for(size_t i = 0; i < m_tens.size(); i++) {
        CTF::Tensor<T> *t = reinterpret_cast<CTF::Tensor<T>*>(m_tens[i]);
        delete t;
    }
    m_tens.clear();
}


template<size_t N, typename T>
const dimensions<N> &ctf_dense_tensor<N, T>::get_dims() const {

    return m_dims;
}


template<size_t N, typename T>
const ctf_symmetry<N, T> &ctf_dense_tensor<N, T>::on_req_symmetry() {

    return m_sym;
}


template<size_t N, typename T>
typename ctf_dense_tensor<N, T>::ctf_tensor_adapter*
ctf_dense_tensor<N, T>::on_req_ctf_tensor(size_t icomp) {

    return m_tens[icomp];
}


template<size_t N, typename T>
void ctf_dense_tensor<N, T>::on_reset_symmetry(const ctf_symmetry<N, T> &sym) {

    cleanup();
    m_sym = sym;

    //  CTF stores tensors in the column-major format,
    //  need to use the reverse order of dimensions

    int edge_len[N], edge_sym[N];
    for(size_t i = 0; i < N; i++) {
        edge_len[i] = m_dims[N - i - 1];
        edge_sym[i] = NS;
    }

    size_t ncomp = m_sym.get_ncomp();
    m_tens.resize(ncomp, 0);
    for(size_t icomp = 0; icomp < ncomp; icomp++) {
        m_sym.write(icomp, edge_sym);
        CTF::Tensor<T> *t = new CTF::Tensor<T>(N, edge_len, edge_sym,
            ctf_world::get_world());
        m_tens[icomp] = reinterpret_cast<ctf_tensor_adapter*>(t);
    }
}


template<size_t N, typename T>
void ctf_dense_tensor<N, T>::on_adjust_symmetry(const ctf_symmetry<N, T> &sym) {

    static const char method[] = "on_adjust_symmetry()";

    //  If this operation becomes a bottleneck, use largest subgroup
    //  as symmetry of temporary tensor

    sequence<N, unsigned> symt_grp, symt_sym;
    for(size_t i = 0; i < N; i++) symt_grp[i] = i;
    ctf_symmetry<N, T> symt(symt_grp, symt_sym);
    ctf_dense_tensor<N, T> dtmp(get_dims(), symt);
    CTF::Tensor<T> &dtt = *reinterpret_cast<CTF::Tensor<T>*>(dtmp.m_tens[0]);

    char label[N + 1];
    for(size_t i = 0; i < N; i++) label[i] = char(i) + 1;
    label[N] = '\0';

    for(size_t icomp = 0; icomp < m_tens.size(); icomp++) {
        CTF::Tensor<T> &dta = *reinterpret_cast<CTF::Tensor<T>*>(m_tens[icomp]);
        if(icomp == 0) dtt[label] = dta[label];
        else dtt[label] += dta[label];
    }

    on_reset_symmetry(sym);

    for(size_t icomp = 0; icomp < m_tens.size(); icomp++) {
        CTF::Tensor<T> &dta = *reinterpret_cast<CTF::Tensor<T>*>(m_tens[icomp]);
        T z = ctf_symmetry<N, T>::symconv_factor(symt, 0, sym, icomp);
        if(z == T(0)) continue;
        dta[label] = z * dtt[label];
        dtt[label] -= dta[label];
    }
}


template<size_t N, typename T>
void ctf_dense_tensor<N, T>::on_set_immutable() {

}


} // namespace libtensor

#endif // LIBTENSOR_CTF_DENSE_TENSOR_IMPL_H
