#ifndef LIBTENSOR_DENSE_TENSOR_CTRL_H
#define LIBTENSOR_DENSE_TENSOR_CTRL_H

#include "dense_tensor_i.h"

namespace libtensor {


/**	\brief Tensor control

	Tensor control keeps track of pointers which have been checked out and
	returns all pointers as soon as it is destructed. Thus, pointers to
	tensor data are only valid as long as the dense_tensor_ctrl object exist by
	which they have been requested.

	\param N Tensor order.
	\param T Tensor element type.

	\ingroup libtensor_core
**/
template<size_t N, typename T>
class dense_tensor_ctrl {
private:
	typedef typename dense_tensor_i<N, T>::handle_t
		handle_t; //!< Session handle type

private:
	dense_tensor_i<N, T> &m_t; //!< Controlled %tensor object
	handle_t m_h; //!< Session handle

public:
	//!	\name Construction and destruction
	//@{

	/**	\brief Initializes the control object, initiates a session
		\param t Tensor instance.
	 **/
	dense_tensor_ctrl(dense_tensor_i<N, T> &t);

	/**	\brief Destroys the control object, closes the session
	 **/
	~dense_tensor_ctrl();

	//@}


	//!	\name Events
	//@{

	void req_prefetch();
	T *req_dataptr();
	void ret_dataptr(const T *p);
	const T *req_const_dataptr();
	void ret_const_dataptr(const T *p);

	//@}
};


template<size_t N, typename T>
inline dense_tensor_ctrl<N, T>::dense_tensor_ctrl(dense_tensor_i<N, T> &t) : m_t(t) {

	m_h = m_t.on_req_open_session();
}


template<size_t N, typename T>
inline dense_tensor_ctrl<N, T>::~dense_tensor_ctrl() {

	m_t.on_req_close_session(m_h);
}


template<size_t N, typename T>
inline void dense_tensor_ctrl<N, T>::req_prefetch() {

	m_t.on_req_prefetch(m_h);
}


template<size_t N, typename T>
inline T *dense_tensor_ctrl<N,T>::req_dataptr() {

	return m_t.on_req_dataptr(m_h);
}


template<size_t N, typename T>
inline void dense_tensor_ctrl<N, T>::ret_dataptr(const T *p) {

	m_t.on_ret_dataptr(m_h, p);
}


template<size_t N, typename T>
inline const T *dense_tensor_ctrl<N, T>::req_const_dataptr() {

	return m_t.on_req_const_dataptr(m_h);
}


template<size_t N, typename T>
inline void dense_tensor_ctrl<N, T>::ret_const_dataptr(const T *p) {

	m_t.on_ret_const_dataptr(m_h, p);
}


} // namespace libtensor

#endif // LIBTENSOR_DENSE_TENSOR_CTRL_H
