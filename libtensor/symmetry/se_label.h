#ifndef LIBTENSOR_SE_LABEL_H
#define LIBTENSOR_SE_LABEL_H

#include "../defs.h"
#include "../core/block_index_space.h"
#include "../core/mask.h"
#include "../core/symmetry_element_i.h"
#include "product_table_container.h"

namespace libtensor {

/**	\brief Symmetry element for point groups
	\tparam N Symmetry cardinality (%tensor order).
	\tparam T Tensor element type.

	\ingroup libtensor_symmetry
 **/
template<size_t N, typename T>
class se_label : public symmetry_element_i<N, T> {
public:
	static const char *k_clazz; //!< Class name
	static const char *k_sym_type; //!< Symmetry type

	typedef product_table_container::id_t table_id_t;
	typedef product_table::label_t label_t;
private:
	dimensions<N> m_bidims; //!< Block %index space dimensions
	sequence<N, size_t> m_type; //!< Label type
	sequence<N, label_points*> m_labels; //!< Block labels
	label_t m_label; //!< Target label

	table_id_t m_id; //!< Id of product table to be used
public:
	//!	\name Construction and destruction
	//@{

	/**	\brief Initializes the %symmetry element
		\param bis Block %index space.
		\param id Id of product table for label.
		\param target Target label.
	 **/
	se_label(const block_index_space<N> &bis,
			const table_id_t &id, const label_t &target);

	/**	\brief Copy constructor
	 **/
	se_label(const se_label<N, T> &elem);

	/**	\brief Virtual destructor
	 **/
	virtual ~se_label();

	//@}


	//!	\name Manipulations
	//@{

	/**	\brief Assign label to a subspace block given by a %mask and a position

		\param msk Dimension mask
		\param pos Block position (not to exceed the number of
			splits along the given dimension)
		\param label The label
		\throw bad_parameter If the mask is incorrect.
		\throw out_of_bounds If the position or the label is out of bounds.
	 **/
	void assign(const mask<N> &msk, size_t pos,
			label_t label) throw(bad_parameter, out_of_bounds);

	/**	\brief Remove label of a subspace block given by a %mask and a position

		\param msk Dimension mask
		\param pos Block position (not to exceed the number of
			splits along the given dimension)
		\throw bad_parameter If the mask is incorrect.
		\throw out_of_bounds If the position is out of bounds.
	 **/
	void remove(const mask<N> &msk, size_t pos) throw(bad_parameter,
			out_of_bounds);

	/**	\brief Remove all labels
	 **/
	void clear();

	//@}

	/**	\brief Returns the type (labeling pattern) of a dimension
		\param dim Dimension number.
		\throw out_of_bounds If the dimension number is out of bounds.
	 **/
	size_t get_type(size_t dim) const throw(out_of_bounds);

	/**	\brief Returns the block dimension of a dimension type
		\param type Dimension type.
		\throw out_of_bounds If the dimension type is out of bounds.
	 **/
	size_t get_dim(size_t type) const throw(out_of_bounds);

	/**	\brief Returns the block dimensions.
	 **/
	const dimensions<N> &get_dims() const;

	/**	\brief Returns the label of a block of a dimension type.
		\param type Dimension type.
		\param pos Block position.
		\throw out_of_bounds If the dimension type is out of bounds.
	 **/
	label_t get_label(size_t type, size_t pos) const throw(out_of_bounds);

	//!	\name Implementation of symmetry_element_i<N, T>
	//@{

	/**	\copydoc symmetry_element_i<N, T>::get_type()
	 **/
	virtual const char *get_type() const {
		return k_sym_type;
	}

	/**	\copydoc symmetry_element_i<N, T>::clone()
	 **/
	virtual symmetry_element_i<N, T> *clone() const {
		return new se_label<N, T>(*this);
	}

	/**	\copydoc symmetry_element_i<N, T>::get_mask
	 **/
	virtual const mask<N> &get_mask() const {
		throw 1;
	}

	/**	\copydoc symmetry_element_i<N, T>::permute
	 **/
	virtual void permute(const permutation<N> &perm) {
		throw 1;
	}

	/**	\copydoc symmetry_element_i<N, T>::is_valid_bis
	 **/
	virtual bool is_valid_bis(const block_index_space<N> &bis) const;

	/**	\copydoc symmetry_element_i<N, T>::is_allowed
	 **/
	virtual bool is_allowed(const index<N> &idx) const {

		return true;
	}

	/**	\copydoc symmetry_element_i<N, T>::apply(index<N>&)
	 **/
	virtual void apply(index<N> &idx) const;

	/**	\copydoc symmetry_element_i<N, T>::apply(
			index<N>&, transf<N, T>&)
	 **/
	virtual void apply(index<N> &idx, transf<N, T> &tr) const;

	//@}

};

template<size_t N, typename T>
const char se_label<N, T>::k_clazz = "se_label<N, T>";

template<size_t N, typename T>
const char se_label<N, T>::k_sym_type = "se_label";


} // namespace libtensor

#endif // LIBTENSOR_SE_LABEL_H

