#include <libtensor/dense_tensor/dense_tensor.h>
#include <libtensor/dense_tensor/tod_copy.h>
#include <libtensor/dense_tensor/tod_random.h>
#include <libtensor/ctf_dense_tensor/ctf.h>
#include <libtensor/ctf_dense_tensor/ctf_dense_tensor.h>
#include <libtensor/ctf_dense_tensor/ctf_tod_collect.h>
#include <libtensor/ctf_dense_tensor/ctf_tod_distribute.h>
#include <libtensor/ctf_dense_tensor/ctf_tod_scatter.h>
#include "../compare_ref.h"
#include "ctf_tod_scatter_test.h"

namespace libtensor {


void ctf_tod_scatter_test::perform() throw(libtest::test_exception) {

    ctf::init();

    try {

        test_1a();
        test_1b();

    } catch(...) {
        ctf::exit();
        throw;
    }

    ctf::exit();
}


void ctf_tod_scatter_test::test_1a() {

    static const char testname[] = "ctf_tod_scatter_test::test_1a()";

    typedef allocator<double> allocator_t;

    try {

    index<1> i1a, i1b;
    i1b[0] = 99;
    index<2> i2a, i2b;
    i2b[0] = 99; i2b[1] = 99;

    dimensions<1> dimsa(index_range<1>(i1a, i1b));
    dimensions<2> dimsb(index_range<2>(i2a, i2b));

    dense_tensor<1, double, allocator_t> ta(dimsa);
    dense_tensor<2, double, allocator_t> tb(dimsb), tb_ref(dimsb);
    ctf_dense_tensor<1, double> dta(dimsa);
    ctf_dense_tensor<2, double> dtb(dimsb);

    tod_random<1>().perform(ta);
    tod_random<2>().perform(tb);
    tod_scatter<1, 1>(ta, 1.0).perform(true, tb_ref);

    ctf_tod_distribute<1>(ta).perform(dta);
    ctf_tod_distribute<2>(tb).perform(dtb);

    ctf_tod_scatter<1, 1>(dta, tensor_transf<2, double>()).perform(true, dtb);
    ctf_tod_collect<2>(dtb).perform(tb);

    compare_ref<2>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void ctf_tod_scatter_test::test_1b() {

    static const char testname[] = "ctf_tod_scatter_test::test_1b()";

    typedef allocator<double> allocator_t;

    try {

    index<1> i1a, i1b;
    i1b[0] = 99;
    index<2> i2a, i2b;
    i2b[0] = 99; i2b[1] = 99;

    dimensions<1> dimsa(index_range<1>(i1a, i1b));
    dimensions<2> dimsb(index_range<2>(i2a, i2b));

    dense_tensor<1, double, allocator_t> ta(dimsa);
    dense_tensor<2, double, allocator_t> tb(dimsb), tb_ref(dimsb);
    ctf_dense_tensor<1, double> dta(dimsa);
    ctf_dense_tensor<2, double> dtb(dimsb);

    tensor_transf<2, double> trb(permutation<2>(), scalar_transf<double>(-0.5));

    tod_random<1>().perform(ta);
    tod_random<2>().perform(tb);
    tod_copy<2>(tb).perform(true, tb_ref);
    tod_scatter<1, 1>(ta, trb).perform(false, tb_ref);

    ctf_tod_distribute<1>(ta).perform(dta);
    ctf_tod_distribute<2>(tb).perform(dtb);

    ctf_tod_scatter<1, 1>(dta, trb).perform(false, dtb);
    ctf_tod_collect<2>(dtb).perform(tb);

    compare_ref<2>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


} // namespace libtensor

