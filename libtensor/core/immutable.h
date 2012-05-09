#ifndef LIBTENSOR_IMMUTABLE_H
#define LIBTENSOR_IMMUTABLE_H

#include "../defs.h"
#include "../exception.h"

namespace libtensor {

/** \brief Enables %immutability

    \ingroup libtensor_core
**/
class immutable {
private:
    bool m_immutable; //!< Indicates whether the object is immutable

public:
    //!    \name Construction and destruction
    //@{

    /** \brief Initializes a mutable object
    **/
    immutable();

    //@}

    //!    \name Immutability
    //@{

    /** \brief Checks if the object is %immutable

        Returns true if the object is %immutable, false otherwise.
    **/
    bool is_immutable() const;

    /** \brief Sets the object status as %immutable.

        Sets the object status as %immutable. If the object has already
        been set %immutable, it stays %immutable.
    **/
    void set_immutable();

    //@}

protected:
    //!    \name Immutability
    //@{

    /** \brief Invoked when the object is set immutable
     **/
    virtual void on_set_immutable() = 0;

    //@}
};

inline immutable::immutable() {
    m_immutable = false;
}

inline bool immutable::is_immutable() const {
    return m_immutable;
}

inline void immutable::set_immutable() {
    m_immutable = true;
    on_set_immutable();
}

} // namespace libtensor

#endif // LIBTENSOR_IMMUTABLE_H

