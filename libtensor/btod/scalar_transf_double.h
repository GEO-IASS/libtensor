#ifndef LIBTENSOR_SCALAR_TRANSF_DOUBLE_H
#define LIBTENSOR_SCALAR_TRANSF_DOUBLE_H

#include "../defs.h"
#include "../exception.h"
#include "../core/scalar_transf.h"

namespace libtensor {

/** \brief Specialization of scalar_transf<T> for T == double

    TODO: Think about restricting m_coeff to 1.0 and -1.0
 **/
class scalar_transf<double> {
private:
	double m_coeff; //!< Coefficient

public:
	//! \name Constructors
	//@{
	scalar_transf() : m_coeff(1.0) { }
	scalar_transf(const scalar_transf<double> &tr) : m_coeff(tr.m_coeff) { }
	//@}

	//@ {
	void reset() { m_coeff = 1.0; }
	void transform(const scalar_transf<double> &tr) { m_coeff *= tr.m_coeff; }
    void apply(double &el) { el *= m_coeff; }
	void invert() { m_coeff = (m_coeff == 0.0 ? 0.0 : 1.0/m_coeff); }
	scalar_transf<double> inverse() const {
	    scalar_transf<double> st;
	    st.scale(m_coeff == 0.0 ? 0.0 : 1.0/m_coeff);
	    return st;
	}
	bool is_identity() const { return m_coeff == 1.0; }
    //@}

	/** \brief Scale coefficient by c
	 **/
	void scale(double c) { m_coeff *= c; }

	//! \name Member access functions
	//@{
	/** \brief Returns the coefficient
	 **/
	double& get_coeff() { return m_coeff; }

	/** \brief Returns the coefficient
	 **/
	const double& get_coeff() const { return m_coeff; }

	//@}

	//! Comparison operators
	//@{
	/** \brief equal comparison
	 **/
	bool operator==(const scalar_transf<N,double>& tr) const {
		return (m_coeff==tr.m_coeff);
	}

	/** \brief Unequal comparison
	 **/
	bool operator!=(const transf<N,double>& tr) const {
	    return (!operator==(tr));
	}
	//@}
};

} // namespace libtensor

#endif // LIBTENSOR_SCALAR_TRANSF_DOUBLE_H
