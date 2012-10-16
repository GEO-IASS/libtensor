#ifndef LIBTENSOR_GEN_BLOCK_TENSOR_H
#define LIBTENSOR_GEN_BLOCK_TENSOR_H

#include <libtensor/core/block_index_space.h>
#include <libtensor/core/immutable.h>
#include <libtensor/core/noncopyable.h>
#include <libtensor/core/orbit_list.h>
#include "auto_rwlock.h"
#include "block_map.h"
#include "gen_block_tensor_i.h"

namespace libtensor {


/** \brief Block tensor
    \tparam N Tensor order.
    \tparam BtTraits Block tensor traits.

    \ingroup libtensor_gen_block_tensor
 **/
template<size_t N, typename BtTraits>
class gen_block_tensor :
    public gen_block_tensor_i<N, typename BtTraits::bti_traits>,
    public immutable,
    public noncopyable {

public:
    static const char *k_clazz; //!< Class name

public:
    typedef typename BtTraits::element_type element_type;
    typedef typename BtTraits::bti_traits bti_traits;
    typedef typename bti_traits::template rd_block_type<N>::type rd_block_type;
    typedef typename bti_traits::template wr_block_type<N>::type wr_block_type;
    typedef symmetry<N, element_type> symmetry_type;

public:
    block_index_space<N> m_bis; //!< Block index space
    dimensions<N> m_bidims; //!< Block index dimensions
    symmetry<N, element_type> m_symmetry; //!< Block tensor symmetry
    orbit_list<N, element_type> *m_orblst; //!< Orbit list
    block_map<N, BtTraits> m_map; //!< Block map
    libutil::rwlock m_lock; //!< Read-write lock

public:
    //!    \name Construction and destruction
    //@{
    gen_block_tensor(const block_index_space<N> &bis);
    virtual ~gen_block_tensor();
    //@}

    //!    \name Implementation of libtensor::block_tensor_i<N, T>
    //@{
    virtual const block_index_space<N> &get_bis() const;
    //@}

protected:
    //!    \name Implementation of libtensor::block_tensor_i<N, T>
    //@{
    virtual const symmetry_type &on_req_const_symmetry();
    virtual symmetry_type &on_req_symmetry();
    virtual rd_block_type &on_req_const_block(const index<N> &idx);
    virtual void on_ret_const_block(const index<N> &idx);
    virtual wr_block_type &on_req_block(const index<N> &idx);
    virtual void on_ret_block(const index<N> &idx);
    virtual bool on_req_is_zero_block(const index<N> &idx);
    virtual void on_req_zero_block(const index<N> &idx);
    virtual void on_req_zero_all_blocks();
    //@}

    //!    \name Implementation of libtensor::immutable
    //@{
    virtual void on_set_immutable();
    //@}

private:
    void update_orblst(auto_rwlock &lock);

};


} // namespace libtensor

#endif // LIBTENSOR_GEN_BLOCK_TENSOR_H
