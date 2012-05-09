#ifndef LIBTENSOR_BLOCK_TENSOR_I_H
#define LIBTENSOR_BLOCK_TENSOR_I_H

#include "../defs.h"
#include "../exception.h"
#include "block_index_space.h"
#include "index.h"
#include "symmetry.h"
#include "../dense_tensor/dense_tensor_i.h"

namespace libtensor {

template<size_t N, typename T> class block_tensor_ctrl;

/** \brief Block %tensor interface
    \tparam N Tensor order.
    \tparam T Tensor element type.

    Block tensors break down the whole %tensor into small blocks and
    implement %symmetry relations between them. Each individual block is
    a small %tensor itself and can be addressed using the dense_tensor_i<N, T>
    interface.

    The block %tensor interface does not impose any restrictions on how
    a particular implementation operates. However, it defines a set of
    events which have to reacted upon. The overall mechanism is the same
    as for regular tensors (see dense_tensor_i<N, T>): a control object (an
    instance of block_tensor_ctrl<N, T>) mediates requests to the block
    %tensor object and ensures the completeness of the interaction session.

    <b>Block %tensor events</b>

    <b>req_symmetry</b> The request for %symmetry is invoked when the client
    requires access to the %symmetry object. The handler returns a reference
    to %symmetry.

    <b>req_orbits</b> Invoked to obtain an iterator over all non-zero
    orbits (%symmetry-unique blocks) in the block %tensor. The handler
    returns an instance of orbit_iterator<N, T>.

    <b>req_block</b> Invoked to obtain a canonical block with a given
    %index.

    <b>ret_block</b> Invoked to indicate that a canonical block with a
    given %index is not required anymore.

    <b>req_zero_block</b> Invoked to inform that a canonical block has all
    its elements equal to zero.

    \ingroup libtensor_core
 **/
template<size_t N, typename T>
class block_tensor_i {
    friend class block_tensor_ctrl<N, T>;

public:
    /** \brief Virtual destructor
     **/
    virtual ~block_tensor_i() { }

    /** \brief Returns the block %index space of the block %tensor
     **/
    virtual const block_index_space<N> &get_bis() const = 0;

protected:
    //!    \name Symmetry event handlers
    //@{

    /** \brief Request to obtain the constant reference to the block
            %tensor's %symmetry
     **/
    virtual const symmetry<N, T> &on_req_const_symmetry()
        throw(exception) = 0;

    /** \brief Request to obtain the reference to the block %tensor's
            %symmetry
     **/
    virtual symmetry<N, T> &on_req_symmetry() throw(exception) = 0;

    //@}


    //!    \name Event handling
    //@{

    /** \brief Invoked when a canonical block is requested
        \param idx Block %index.
        \return Reference to the requested block.
     **/
    virtual dense_tensor_i<N, T> &on_req_block(const index<N> &idx)
        throw(exception) = 0;

    /** \brief Invoked to return a canonical block
        \param idx Block %index.
     **/
    virtual void on_ret_block(const index<N> &idx) throw(exception) = 0;

    /** \brief Invoked when an auxiliary canonical block is requested
        \param idx Block %index.
        \return Reference to the requested block.
     **/
    virtual dense_tensor_i<N, T> &on_req_aux_block(const index<N> &idx)
        throw(exception) = 0;

    /** \brief Invoked to return an auxiliary canonical block
        \param idx Block %index.
     **/
    virtual void on_ret_aux_block(const index<N> &idx) throw(exception) = 0;

    /** \brief Invoked to check whether a canonical block is zero
        \param idx Block %index.
     **/
    virtual bool on_req_is_zero_block(const index<N> &idx)
        throw(exception) = 0;

    /** \brief Invoked to make a canonical block zero
        \param idx Block %index.
     **/
    virtual void on_req_zero_block(const index<N> &idx)
        throw(exception) = 0;

    /** \brief Invoked to make all blocks zero
     **/
    virtual void on_req_zero_all_blocks() throw(exception) = 0;

    /** \brief Enables multi-processor synchronization
     **/
    virtual void on_req_sync_on() throw(exception) = 0;

    /** \brief Disables multi-processor synchronization
     **/
    virtual void on_req_sync_off() throw(exception) = 0;

    //@}
};

} // namespace libtensor

#endif // LIBTENSOR_BLOCK_TENSOR_I_H
