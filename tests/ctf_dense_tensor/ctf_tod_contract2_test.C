#include <libtensor/dense_tensor/dense_tensor.h>
#include <libtensor/dense_tensor/tod_random.h>
#include <libtensor/ctf_dense_tensor/ctf.h>
#include <libtensor/ctf_dense_tensor/ctf_dense_tensor.h>
#include <libtensor/ctf_dense_tensor/ctf_tod_collect.h>
#include <libtensor/ctf_dense_tensor/ctf_tod_contract2.h>
#include <libtensor/ctf_dense_tensor/ctf_tod_distribute.h>
#include "../compare_ref.h"
#include "ctf_tod_contract2_test.h"

namespace libtensor {


void ctf_tod_contract2_test::perform() throw(libtest::test_exception) {

    ctf::init();

    try {

        test_1(0.0);
        test_1(-0.5);
        test_2(0.0);
        test_2(-0.1);
        test_3a();
        test_3b();
        test_4(0.0);
        test_4(-0.3);
        test_5(0.0);
        test_5(1.6);
        test_6(0.0);
        test_6(-1.6);
        test_7(0.0);
        test_7(0.23);

    } catch(...) {
        ctf::exit();
        throw;
    }

    ctf::exit();
}


void ctf_tod_contract2_test::test_1(double d) {

    std::ostringstream tnss;
    tnss << "ctf_tod_contract2_test::test_1(" << d << ")";
    std::string tn = tnss.str();
    const char *testname = tn.c_str();

    typedef allocator<double> allocator_t;

    try {

    index<2> i1, i2;
    i2[0] = 99; i2[1] = 99;
    dimensions<2> dimsa(index_range<2>(i1, i2)), dimsb(dimsa), dimsc(dimsa);
    dense_tensor<2, double, allocator_t> ta(dimsa), tb(dimsb), tc(dimsc),
        tc_ref(dimsc);
    ctf_dense_tensor<2, double> dta(dimsa), dtb(dimsb), dtc(dimsc);

    tod_random<2>().perform(ta);
    tod_random<2>().perform(tb);
    tod_random<2>().perform(tc);
    tod_copy<2>(tc).perform(true, tc_ref);

    ctf_tod_distribute<2>(ta).perform(dta);
    ctf_tod_distribute<2>(tb).perform(dtb);
    ctf_tod_distribute<2>(tc).perform(dtc);

    contraction2<1, 1, 1> contr;
    contr.contract(1, 0);

    if(d == 0.0) {
        tod_contract2<1, 1, 1>(contr, ta, tb).perform(true, tc_ref);
        ctf_tod_contract2<1, 1, 1>(contr, dta, dtb).perform(true, dtc);
    } else {
        tod_contract2<1, 1, 1>(contr, ta, tb, d).perform(false, tc_ref);
        ctf_tod_contract2<1, 1, 1>(contr, dta, dtb, d).perform(false, dtc);
    }

    ctf_tod_collect<2>(dtc).perform(tc);

    compare_ref<2>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_contract2_test::test_2(double d) {

    std::ostringstream tnss;
    tnss << "ctf_tod_contract2_test::test_2(" << d << ")";
    std::string tn = tnss.str();
    const char *testname = tn.c_str();

    typedef allocator<double> allocator_t;

    try {

    index<3> ia1, ia2;
    ia2[0] = 29; ia2[1] = 29; ia2[2] = 19;
    dimensions<3> dimsa(index_range<3>(ia1, ia2));
    index<3> ib1, ib2;
    ib2[0] = 19; ib2[1] = 29; ib2[2] = 29;
    dimensions<3> dimsb(index_range<3>(ib1, ib2));
    index<4> ic1, ic2;
    ic2[0] = 29; ic2[1] = 29; ic2[2] = 29; ic2[3] = 29;
    dimensions<4> dimsc(index_range<4>(ic1, ic2));
    dense_tensor<3, double, allocator_t> ta(dimsa);
    dense_tensor<3, double, allocator_t> tb(dimsb);
    dense_tensor<4, double, allocator_t> tc(dimsc), tc_ref(dimsc);
    ctf_dense_tensor<3, double> dta(dimsa);
    ctf_dense_tensor<3, double> dtb(dimsb);
    ctf_dense_tensor<4, double> dtc(dimsc);

    tod_random<3>().perform(ta);
    tod_random<3>().perform(tb);
    tod_random<4>().perform(tc);
    tod_copy<4>(tc).perform(true, tc_ref);

    ctf_tod_distribute<3>(ta).perform(dta);
    ctf_tod_distribute<3>(tb).perform(dtb);
    ctf_tod_distribute<4>(tc).perform(dtc);

    // c(ijkl) = a(jkp) b(pil)
    contraction2<2, 2, 1> contr(permutation<4>().permute(1, 2).permute(0, 1));
    contr.contract(2, 0);

    if(d == 0.0) {
        tod_contract2<2, 2, 1>(contr, ta, tb, 0.1).perform(true, tc_ref);
        ctf_tod_contract2<2, 2, 1>(contr, dta, dtb, 0.1).perform(true, dtc);
    } else {
        tod_contract2<2, 2, 1>(contr, ta, tb, d).perform(false, tc_ref);
        ctf_tod_contract2<2, 2, 1>(contr, dta, dtb, d).perform(false, dtc);
    }

    ctf_tod_collect<4>(dtc).perform(tc);

    compare_ref<4>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_contract2_test::test_3a() {

    static const char testname[] = "ctf_tod_contract2_test::test_3a()";

    typedef allocator<double> allocator_t;

    try {

    index<4> ia1, ia2;
    ia2[0] = 9; ia2[1] = 9; ia2[2] = 11; ia2[3] = 11;
    sequence<4, unsigned> syma_grp, syma_sym(0);
    syma_grp[0] = 0; syma_grp[1] = 0; syma_grp[2] = 1; syma_grp[3] = 1;
    dimensions<4> dimsa(index_range<4>(ia1, ia2));
    ctf_symmetry<4, double> syma(syma_grp, syma_sym);
    index<4> ib1, ib2;
    ib2[0] = 11; ib2[1] = 11; ib2[2] = 11; ib2[3] = 11;
    sequence<4, unsigned> symb_grp, symb_sym(0);
    symb_grp[0] = 0; symb_grp[1] = 0; symb_grp[2] = 1; symb_grp[3] = 1;
    dimensions<4> dimsb(index_range<4>(ib1, ib2));
    ctf_symmetry<4, double> symb(symb_grp, symb_sym);
    index<4> ic1, ic2;
    ic2[0] = 9; ic2[1] = 9; ic2[2] = 11; ic2[3] = 11;
    sequence<4, unsigned> symc_grp, symc_sym(0);
    symc_grp[0] = 0; symc_grp[1] = 1; symc_grp[2] = 2; symc_grp[3] = 3;
    dimensions<4> dimsc(index_range<4>(ic1, ic2));
    ctf_symmetry<4, double> symc(symc_grp, symc_sym);
    dense_tensor<4, double, allocator_t> ta0(dimsa), ta(dimsa);
    dense_tensor<4, double, allocator_t> tb0(dimsb), tb(dimsb);
    dense_tensor<4, double, allocator_t> tc(dimsc), tc_ref(dimsc);
    ctf_dense_tensor<4, double> dta(dimsa, syma);
    ctf_dense_tensor<4, double> dtb(dimsb, symb);
    ctf_dense_tensor<4, double> dtc(dimsc, symc);

    tod_random<4>().perform(ta0);
    tod_copy<4>(ta0).perform(true, ta);
    tod_copy<4>(ta0, permutation<4>().permute(0, 1), 1.0).perform(false, ta);
    tod_copy<4>(ta0, permutation<4>().permute(2, 3), 1.0).perform(false, ta);
    tod_copy<4>(ta0, permutation<4>().permute(0, 1).permute(2, 3), 1.0).
        perform(false, ta);
    tod_random<4>().perform(tb0);
    tod_copy<4>(tb0).perform(true, tb);
    tod_copy<4>(tb0, permutation<4>().permute(0, 1), 1.0).perform(false, tb);
    tod_copy<4>(tb0, permutation<4>().permute(2, 3), 1.0).perform(false, tb);
    tod_copy<4>(tb0, permutation<4>().permute(0, 1).permute(2, 3), 1.0).
        perform(false, tb);
    tod_random<4>().perform(tc);

    // c(ijkl) = a(ijab) b(klab)
    contraction2<2, 2, 2> contr;
    contr.contract(2, 2);
    contr.contract(3, 3);
    tod_contract2<2, 2, 2>(contr, ta, tb, -1.2).perform(true, tc_ref);

    ctf_tod_distribute<4>(ta).perform(dta);
    ctf_tod_distribute<4>(tb).perform(dtb);
    ctf_tod_distribute<4>(tc).perform(dtc);

    ctf_tod_contract2<2, 2, 2>(contr, dta, dtb, -1.2).perform(true, dtc);
    ctf_tod_collect<4>(dtc).perform(tc);

    compare_ref<4>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_contract2_test::test_3b() {

    static const char testname[] = "ctf_tod_contract2_test::test_3b()";

    typedef allocator<double> allocator_t;

    try {

    index<4> ia1, ia2;
    ia2[0] = 9; ia2[1] = 9; ia2[2] = 11; ia2[3] = 11;
    sequence<4, unsigned> syma_grp, syma_sym;
    syma_grp[0] = 0; syma_grp[1] = 0; syma_grp[2] = 1; syma_grp[3] = 1;
    syma_sym[0] = 1; syma_sym[1] = 1;
    dimensions<4> dimsa(index_range<4>(ia1, ia2));
    ctf_symmetry<4, double> syma(syma_grp, syma_sym);
    index<4> ib1, ib2;
    ib2[0] = 11; ib2[1] = 11; ib2[2] = 11; ib2[3] = 11;
    sequence<4, unsigned> symb_grp, symb_sym;
    symb_grp[0] = 0; symb_grp[1] = 0; symb_grp[2] = 1; symb_grp[3] = 1;
    symb_sym[0] = 1; symb_sym[1] = 1;
    dimensions<4> dimsb(index_range<4>(ib1, ib2));
    ctf_symmetry<4, double> symb(symb_grp, symb_sym);
    index<4> ic1, ic2;
    ic2[0] = 11; ic2[1] = 11; ic2[2] = 9; ic2[3] = 9;
    sequence<4, unsigned> symc_grp, symc_sym;
    symc_grp[0] = 0; symc_grp[1] = 1; symc_grp[2] = 2; symc_grp[3] = 3;
    symc_sym[0] = 0; symc_sym[1] = 0; symc_sym[2] = 0; symc_sym[3] = 0;
    dimensions<4> dimsc(index_range<4>(ic1, ic2));
    ctf_symmetry<4, double> symc(symc_grp, symc_sym);
    dense_tensor<4, double, allocator_t> ta0(dimsa), ta(dimsa);
    dense_tensor<4, double, allocator_t> tb0(dimsb), tb(dimsb);
    dense_tensor<4, double, allocator_t> tc(dimsc), tc_ref(dimsc);
    ctf_dense_tensor<4, double> dta(dimsa, syma);
    ctf_dense_tensor<4, double> dtb(dimsb, symb);
    ctf_dense_tensor<4, double> dtc(dimsc, symc);

    tod_random<4>().perform(ta0);
    tod_copy<4>(ta0).perform(true, ta);
    tod_copy<4>(ta0, permutation<4>().permute(0, 1), -1.0).perform(false, ta);
    tod_copy<4>(ta0, permutation<4>().permute(2, 3), -1.0).perform(false, ta);
    tod_copy<4>(ta0, permutation<4>().permute(0, 1).permute(2, 3), 1.0).
        perform(false, ta);
    tod_random<4>().perform(tb0);
    tod_copy<4>(tb0).perform(true, tb);
    tod_copy<4>(tb0, permutation<4>().permute(0, 1), -1.0).perform(false, tb);
    tod_copy<4>(tb0, permutation<4>().permute(2, 3), -1.0).perform(false, tb);
    tod_copy<4>(tb0, permutation<4>().permute(0, 1).permute(2, 3), 1.0).
        perform(false, tb);
    tod_random<4>().perform(tc);

    // c(klij) = a(ijab) b(klab)
    contraction2<2, 2, 2> contr(permutation<4>().permute(0, 2).permute(1, 3));
    contr.contract(2, 2);
    contr.contract(3, 3);
    tod_contract2<2, 2, 2>(contr, ta, tb, -1.2).perform(true, tc_ref);

    ctf_tod_distribute<4>(ta).perform(dta);
    ctf_tod_distribute<4>(tb).perform(dtb);
    ctf_tod_distribute<4>(tc).perform(dtc);

    ctf_tod_contract2<2, 2, 2>(contr, dta, dtb, -1.2).perform(true, dtc);
    ctf_tod_collect<4>(dtc).perform(tc);

    compare_ref<4>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_contract2_test::test_4(double d) {

    std::ostringstream tnss;
    tnss << "ctf_tod_contract2_test::test_4(" << d << ")";
    std::string tn = tnss.str();
    const char *testname = tn.c_str();

    typedef allocator<double> allocator_t;

    try {

    index<2> ia1, ia2;
    ia2[0] = 9; ia2[1] = 9;
    sequence<2, unsigned> syma_grp, syma_sym;
    syma_grp[0] = 0; syma_grp[1] = 0;
    syma_sym[0] = 0;
    dimensions<2> dimsa(index_range<2>(ia1, ia2));
    ctf_symmetry<2, double> syma(syma_grp, syma_sym);

    index<4> ib1, ib2;
    ib2[0] = 9; ib2[1] = 9; ib2[2] = 9; ib2[3] = 9;
    sequence<4, unsigned> symb_grp, symb_sym;
    symb_grp[0] = 0; symb_grp[1] = 1; symb_grp[2] = 2; symb_grp[3] = 3;
    dimensions<4> dimsb(index_range<4>(ib1, ib2));
    ctf_symmetry<4, double> symb(symb_grp, symb_sym);

    index<2> ic1, ic2;
    ic2[0] = 9; ic2[1] = 9;
    sequence<2, unsigned> symc_grp, symc_sym;
    symc_grp[0] = 0; symc_grp[1] = 0;
    symc_sym[0] = 0;
    dimensions<2> dimsc(index_range<2>(ic1, ic2));
    ctf_symmetry<2, double> symc(symc_grp, symc_sym);
    dense_tensor<2, double, allocator_t> ta0(dimsa), ta(dimsa);
    dense_tensor<4, double, allocator_t> tb0(dimsb), tb(dimsb);
    dense_tensor<2, double, allocator_t> tc0(dimsc), tc(dimsc), tc_ref(dimsc);
    ctf_dense_tensor<2, double> dta(dimsa, syma);
    ctf_dense_tensor<4, double> dtb(dimsb, symb);
    ctf_dense_tensor<2, double> dtc(dimsc, symc);

    tod_random<2>().perform(ta0);
    tod_copy<2>(ta0).perform(true, ta);
    tod_copy<2>(ta0, permutation<2>().permute(0, 1)).perform(false, ta);
    tod_random<4>().perform(tb0);
    tod_copy<4>(tb0).perform(true, tb);
    tod_copy<4>(tb0, permutation<4>().permute(0, 1).permute(2, 3)).
        perform(false, tb);
    tod_random<2>().perform(tc0);
    tod_copy<2>(tc0).perform(true, tc);
    tod_copy<2>(tc0, permutation<2>().permute(0, 1)).perform(false, tc);
    tod_copy<2>(tc).perform(true, tc_ref);

    ctf_tod_distribute<2>(ta).perform(dta);
    ctf_tod_distribute<4>(tb).perform(dtb);
    ctf_tod_distribute<2>(tc).perform(dtc);

    // c(ij) = a(kl) b(ijkl)
    contraction2<0, 2, 2> contr;
    contr.contract(0, 2);
    contr.contract(1, 3);
    if(d == 0.0) {
        tod_contract2<0, 2, 2>(contr, ta, tb).perform(true, tc_ref);
        ctf_tod_contract2<0, 2, 2>(contr, dta, dtb).perform(true, dtc);
    } else {
        tod_contract2<0, 2, 2>(contr, ta, tb, d).perform(false, tc_ref);
        ctf_tod_contract2<0, 2, 2>(contr, dta, dtb, d).perform(false, dtc);
    }

    ctf_tod_collect<2>(dtc).perform(tc);

    compare_ref<2>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_contract2_test::test_5(double d) {

    std::ostringstream tnss;
    tnss << "ctf_tod_contract2_test::test_5(" << d << ")";
    std::string tn = tnss.str();
    const char *testname = tn.c_str();

    typedef allocator<double> allocator_t;

    try {

    index<4> ia1, ia2;
    ia2[0] = 9; ia2[1] = 9; ia2[2] = 9; ia2[3] = 9;
    sequence<4, unsigned> syma_grp, syma_sym;
    syma_grp[0] = 0; syma_grp[1] = 1; syma_grp[2] = 2; syma_grp[3] = 3;
    dimensions<4> dimsa(index_range<4>(ia1, ia2));
    ctf_symmetry<4, double> syma(syma_grp, syma_sym, true);

    index<4> ib1, ib2;
    ib2[0] = 9; ib2[1] = 9; ib2[2] = 9; ib2[3] = 9;
    sequence<4, unsigned> symb_grp, symb_sym;
    symb_grp[0] = 0; symb_grp[1] = 1; symb_grp[2] = 2; symb_grp[3] = 3;
    dimensions<4> dimsb(index_range<4>(ib1, ib2));
    ctf_symmetry<4, double> symb(symb_grp, symb_sym, true);

    index<4> ic1, ic2;
    ic2[0] = 9; ic2[1] = 9; ic2[2] = 9; ic2[3] = 9;
    sequence<4, unsigned> symc_grp, symc_sym;
    symc_grp[0] = 0; symc_grp[1] = 1; symc_grp[2] = 2; symc_grp[3] = 3;
    dimensions<4> dimsc(index_range<4>(ic1, ic2));
    ctf_symmetry<4, double> symc(symc_grp, symc_sym, true);
    dense_tensor<4, double, allocator_t> ta0(dimsa), ta(dimsa);
    dense_tensor<4, double, allocator_t> tb0(dimsb), tb(dimsb);
    dense_tensor<4, double, allocator_t> tc0(dimsc), tc(dimsc), tc_ref(dimsc);
    ctf_dense_tensor<4, double> dta(dimsa, syma);
    ctf_dense_tensor<4, double> dtb(dimsb, symb);
    ctf_dense_tensor<4, double> dtc(dimsc, symc);

    tod_random<4>().perform(ta0);
    tod_copy<4>(ta0).perform(true, ta);
    tod_copy<4>(ta0, permutation<4>().permute(0, 1).permute(2, 3)).
        perform(false, ta);
    tod_random<4>().perform(tb0);
    tod_copy<4>(tb0).perform(true, tb);
    tod_copy<4>(tb0, permutation<4>().permute(0, 1).permute(2, 3)).
        perform(false, tb);
    tod_random<4>().perform(tc0);
    tod_copy<4>(tc0).perform(true, tc);
    tod_copy<4>(tc0, permutation<4>().permute(0, 1).permute(2, 3)).
        perform(false, tc);
    tod_copy<4>(tc).perform(true, tc_ref);

    ctf_tod_distribute<4>(ta).perform(dta);
    ctf_tod_distribute<4>(tb).perform(dtb);
    ctf_tod_distribute<4>(tc).perform(dtc);

    // c(ijkl) = a(pqkl) b(ijpq)
    contraction2<2, 2, 2> contr(permutation<4>().permute(0, 2).permute(1, 3));
    contr.contract(0, 2);
    contr.contract(1, 3);
    if(d == 0.0) {
        tod_contract2<2, 2, 2>(contr, ta, tb).perform(true, tc_ref);
        ctf_tod_contract2<2, 2, 2>(contr, dta, dtb).perform(true, dtc);
    } else {
        tod_contract2<2, 2, 2>(contr, ta, tb, d).perform(false, tc_ref);
        ctf_tod_contract2<2, 2, 2>(contr, dta, dtb, d).perform(false, dtc);
    }

    ctf_tod_collect<4>(dtc).perform(tc);

    compare_ref<4>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_contract2_test::test_6(double d) {

    std::ostringstream tnss;
    tnss << "ctf_tod_contract2_test::test_6(" << d << ")";
    std::string tn = tnss.str();
    const char *testname = tn.c_str();

    typedef allocator<double> allocator_t;

    try {

    index<4> ia1, ia2;
    ia2[0] = 9; ia2[1] = 9; ia2[2] = 9; ia2[3] = 9;
    sequence<4, unsigned> syma_grp, syma_sym;
    syma_grp[0] = 0; syma_grp[1] = 1; syma_grp[2] = 2; syma_grp[3] = 3;
    dimensions<4> dimsa(index_range<4>(ia1, ia2));
    ctf_symmetry<4, double> syma(syma_grp, syma_sym, true);

    index<4> ib1, ib2;
    ib2[0] = 9; ib2[1] = 9; ib2[2] = 9; ib2[3] = 9;
    sequence<4, unsigned> symb_grp, symb_sym;
    symb_grp[0] = 0; symb_grp[1] = 1; symb_grp[2] = 2; symb_grp[3] = 3;
    dimensions<4> dimsb(index_range<4>(ib1, ib2));
    ctf_symmetry<4, double> symb(symb_grp, symb_sym, true);

    index<4> ic1, ic2;
    ic2[0] = 9; ic2[1] = 9; ic2[2] = 9; ic2[3] = 9;
    sequence<4, unsigned> symc_grp, symc_sym;
    symc_grp[0] = 0; symc_grp[1] = 1; symc_grp[2] = 2; symc_grp[3] = 3;
    dimensions<4> dimsc(index_range<4>(ic1, ic2));
    ctf_symmetry<4, double> symc(symc_grp, symc_sym);
    dense_tensor<4, double, allocator_t> ta0(dimsa), ta(dimsa);
    dense_tensor<4, double, allocator_t> tb0(dimsb), tb(dimsb);
    dense_tensor<4, double, allocator_t> tc(dimsc), tc_ref(dimsc);
    ctf_dense_tensor<4, double> dta(dimsa, syma);
    ctf_dense_tensor<4, double> dtb(dimsb, symb);
    ctf_dense_tensor<4, double> dtc(dimsc, symc);

    tod_random<4>().perform(ta0);
    tod_copy<4>(ta0).perform(true, ta);
    tod_copy<4>(ta0, permutation<4>().permute(0, 1).permute(2, 3)).
        perform(false, ta);
    tod_random<4>().perform(tb0);
    tod_copy<4>(tb0).perform(true, tb);
    tod_copy<4>(tb0, permutation<4>().permute(0, 1).permute(2, 3)).
        perform(false, tb);
    tod_random<4>().perform(tc);
    tod_copy<4>(tc).perform(true, tc_ref);

    ctf_tod_distribute<4>(ta).perform(dta);
    ctf_tod_distribute<4>(tb).perform(dtb);
    ctf_tod_distribute<4>(tc).perform(dtc);

    // c(ijkl) = a(pqkl) b(ijpq)
    contraction2<2, 2, 2> contr(permutation<4>().permute(0, 2).permute(1, 3));
    contr.contract(0, 2);
    contr.contract(1, 3);
    if(d == 0.0) {
        tod_contract2<2, 2, 2>(contr, ta, tb).perform(true, tc_ref);
        ctf_tod_contract2<2, 2, 2>(contr, dta, dtb).perform(true, dtc);
    } else {
        tod_contract2<2, 2, 2>(contr, ta, tb, d).perform(false, tc_ref);
        ctf_tod_contract2<2, 2, 2>(contr, dta, dtb, d).perform(false, dtc);
    }

    ctf_tod_collect<4>(dtc).perform(tc);

    compare_ref<4>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_contract2_test::test_7(double d) {

    std::ostringstream tnss;
    tnss << "ctf_tod_contract2_test::test_7(" << d << ")";
    std::string tn = tnss.str();
    const char *testname = tn.c_str();

    typedef allocator<double> allocator_t;

    try {

    index<4> ia1, ia2;
    ia2[0] = 1; ia2[1] = 1; ia2[2] = 0; ia2[3] = 0;
    dimensions<4> dimsa(index_range<4>(ia1, ia2));

    index<4> ib1, ib2;
    ib2[0] = 1; ib2[1] = 1; ib2[2] = 0; ib2[3] = 0;
    dimensions<4> dimsb(index_range<4>(ib1, ib2));

    index<4> ic1, ic2;
    ic2[0] = 1; ic2[1] = 1; ic2[2] = 1; ic2[3] = 1;
    dimensions<4> dimsc(index_range<4>(ic1, ic2));
    dense_tensor<4, double, allocator_t> ta0(dimsa), ta(dimsa);
    dense_tensor<4, double, allocator_t> tb0(dimsb), tb(dimsb);
    dense_tensor<4, double, allocator_t> tc(dimsc), tc_ref(dimsc);
    ctf_dense_tensor<4, double> dta(dimsa);
    ctf_dense_tensor<4, double> dtb(dimsb);
    ctf_dense_tensor<4, double> dtc(dimsc);

    tod_random<4>().perform(ta);
    tod_random<4>().perform(tb);
    tod_random<4>().perform(tc);
    tod_copy<4>(tc).perform(true, tc_ref);

    ctf_tod_distribute<4>(ta).perform(dta);
    ctf_tod_distribute<4>(tb).perform(dtb);
    ctf_tod_distribute<4>(tc).perform(dtc);

    // c(ijkl) = a(klab) b(ijab)
    contraction2<2, 2, 2> contr(permutation<4>().permute(0, 2).permute(1, 3));
    contr.contract(2, 2);
    contr.contract(3, 3);
    if(d == 0.0) {
        tod_contract2<2, 2, 2>(contr, ta, tb).perform(true, tc_ref);
        ctf_tod_contract2<2, 2, 2>(contr, dta, dtb).perform(true, dtc);
    } else {
        tod_contract2<2, 2, 2>(contr, ta, tb, d).perform(false, tc_ref);
        ctf_tod_contract2<2, 2, 2>(contr, dta, dtb, d).perform(false, dtc);
    }

    ctf_tod_collect<4>(dtc).perform(tc);

    compare_ref<4>::compare(testname, tc, tc_ref, 5e-14);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


} // namespace libtensor

