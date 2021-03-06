#include <sstream>
#include <libtensor/core/allocator.h>
#include <libtensor/dense_tensor/dense_tensor.h>
#include <libtensor/dense_tensor/dense_tensor_ctrl.h>
#include <libtensor/dense_tensor/tod_scale.h>
#include "../compare_ref.h"
#include "../test_utils.h"

using namespace libtensor;


template<size_t N>
int test_generic(const char *testname, const dimensions<N> &d, double c) {

    typedef allocator<double> allocator_t;

    try {

    dense_tensor<N, double, allocator_t> t(d), t_ref(d);

    {
    dense_tensor_ctrl<N, double> tc(t), tc_ref(t_ref);
    double *p = tc.req_dataptr(), *p_ref = tc_ref.req_dataptr();
    size_t sz = d.get_size();

    for(size_t i = 0; i < sz; i++) {
        double a = drand48();
        p[i] = a;
        p_ref[i] = c * a;
    }

    tc.ret_dataptr(p); p = 0;
    tc_ref.ret_dataptr(p_ref); p_ref = 0;
    }

    tod_scale<N>(c).perform(t);

    compare_ref<N>::compare(testname, t, t_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


int test_0() {

    static const char testname[] = "tod_scale_test::test_0()";

    try {

//    index<0> i1, i2;
//    dimensions<0> dims(index_range<0>(i1, i2));
//    test_generic(testname, dims, 1.0);
//    test_generic(testname, dims, 0.0);
//    test_generic(testname, dims, -0.5);
//    test_generic(testname, dims, 2.3);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


int test_i(size_t i) {

    std::ostringstream ss;
    ss << "tod_scale_test::test_i(" << i << ")";
    std::string tn = ss.str();

    try {

    index<1> i1, i2;
    i2[0] = i - 1;
    dimensions<1> dims(index_range<1>(i1, i2));
    test_generic(tn.c_str(), dims, 1.0);
    test_generic(tn.c_str(), dims, 0.0);
    test_generic(tn.c_str(), dims, -0.5);
    test_generic(tn.c_str(), dims, 2.3);

    } catch(exception &e) {
        return fail_test(tn.c_str(), __FILE__, __LINE__, e.what());
    }

    return 0;
}


int test_ij(size_t i, size_t j) {

    std::ostringstream ss;
    ss << "tod_scale_test::test_ij(" << i << ", " << j << ")";
    std::string tn = ss.str();

    try {

    index<2> i1, i2;
    i2[0] = i - 1; i2[1] = j - 1;
    dimensions<2> dims(index_range<2>(i1, i2));
    test_generic(tn.c_str(), dims, 1.0);
    test_generic(tn.c_str(), dims, 0.0);
    test_generic(tn.c_str(), dims, -0.5);
    test_generic(tn.c_str(), dims, 2.3);

    } catch(exception &e) {
        return fail_test(tn.c_str(), __FILE__, __LINE__, e.what());
    }

    return 0;
}


int test_ijkl(size_t i, size_t j, size_t k, size_t l) {

    std::ostringstream ss;
    ss << "tod_scale_test::test_ijkl(" << i << ", " << j << ", "
        << k << ", " << l << ")";
    std::string tn = ss.str();

    try {

    index<4> i1, i2;
    i2[0] = i - 1; i2[1] = j - 1; i2[2] = k - 1; i2[3] = l - 1;
    dimensions<4> dims(index_range<4>(i1, i2));
    test_generic(tn.c_str(), dims, 1.0);
    test_generic(tn.c_str(), dims, 0.0);
    test_generic(tn.c_str(), dims, -0.5);
    test_generic(tn.c_str(), dims, 2.3);

    } catch(exception &e) {
        return fail_test(tn.c_str(), __FILE__, __LINE__, e.what());
    }

    return 0;
}


int main() {

    return

    test_0() |
    test_i(1) |
    test_i(3) |
    test_i(16) |
    test_ij(1, 1) |
    test_ij(1, 3) |
    test_ij(3, 1) |
    test_ij(3, 7) |
    test_ij(16, 16) |
    test_ijkl(1, 1, 1, 1) |
    test_ijkl(1, 1, 1, 3) |
    test_ijkl(1, 3, 1, 3) |
    test_ijkl(3, 5, 7, 11) |
    test_ijkl(16, 16, 16, 16) |

    0;
}


