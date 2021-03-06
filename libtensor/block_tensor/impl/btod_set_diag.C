#include <libtensor/gen_block_tensor/impl/gen_bto_set_diag_impl.h>
#include "btod_set_diag_impl.h"

namespace libtensor {


template class gen_bto_set_diag<1, btod_traits>;
template class gen_bto_set_diag<2, btod_traits>;
template class gen_bto_set_diag<3, btod_traits>;
template class gen_bto_set_diag<4, btod_traits>;
template class gen_bto_set_diag<5, btod_traits>;
template class gen_bto_set_diag<6, btod_traits>;
template class gen_bto_set_diag<7, btod_traits>;
template class gen_bto_set_diag<8, btod_traits>;

template class btod_set_diag<1>;
template class btod_set_diag<2>;
template class btod_set_diag<3>;
template class btod_set_diag<4>;
template class btod_set_diag<5>;
template class btod_set_diag<6>;
template class btod_set_diag<7>;
template class btod_set_diag<8>;


} // namespace libtensor
