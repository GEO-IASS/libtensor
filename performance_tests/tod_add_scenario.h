#ifndef LIBTENSOR_TOD_ADD_SCENARIO_H
#define LIBTENSOR_TOD_ADD_SCENARIO_H

#include <libtest/libtest.h>
#include "tod_add_performance.h"
#include "performance_test_scenario_i.h"

using libtest::unit_test_factory;

namespace libtensor {

/** \brief Performance test scenario for the libtensor::tod_add class

    \tparam Repeats Number of times each test is repeated
    \tparam N dimensions of the tensors to be added
    \tparam X size of the tensors

    All tests use function dimA() of the X object to determine the sizes of the
    tensors to add.

    \ingroup libtensor_performance_tests
**/
template<size_t Repeats, size_t N, typename DimData>
class tod_add_scenario : public performance_test_scenario_i {

private:
    unit_test_factory<tod_add_ref<Repeats,DimData> > m_ref;
    unit_test_factory<tod_add_p1<Repeats,N,DimData> > m_pt1;
    unit_test_factory<tod_add_p2<Repeats,N,DimData> > m_pt2;
    unit_test_factory<tod_add_p3<Repeats,N,DimData> > m_pt3;

public:
    tod_add_scenario();

    virtual ~tod_add_scenario() {}
};


template<size_t Repeats,size_t N, typename DimData>
tod_add_scenario<Repeats,N,DimData>::tod_add_scenario() {

    add_test("reference","A = A + 2B",m_ref);
    add_test("test 1","A = A + 2B",m_pt1);
    add_test("test 2","A = A + 2 P_I B",m_pt2);
    add_test("test 3","A = A + 2 B'",m_pt3);
}


} // namespace libtensor

#endif // LIBTENSOR_TOD_ADD_SCENARIO_H

