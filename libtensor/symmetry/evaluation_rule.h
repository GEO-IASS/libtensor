#ifndef LIBTENSOR_EVALUATION_RULE_H
#define LIBTENSOR_EVALUATION_RULE_H

#include <list>
#include <libtensor/exception.h>
#include <libtensor/timings.h>
#include <libtensor/core/mask.h>
#include "eval_sequence_list.h"
#include "product_rule.h"
#include "product_table_i.h"


namespace libtensor {


/** \brief Evaluation rule to determine allowed blocks of a block %tensor.

    The evaluation rule determines allowed blocks of a N-dim block %tensor
    from its block labels and the product table. It consists of a
    collection of N-dim sequences and a list of product rules
    (\sa product_rule).

    The function \c new_product() adds a new empty product rule to the
    evaluation rule. The product_rule object which is returned can be used to
    add terms to the new product. The list of product rules can be transversed
    using iterators and get_product() functions.

    The evaluation rule consists of a set of elementary rules each of which
    comprises a sequence of N integers and a set of intrinsic labels.
    Allowed blocks are determined from the evaluation rule as follows:
    - All blocks are forbidden, if the rule setup is empty.
    - A block is allowed, if it is allowed by any product in the rule setup.
    - A block is allowed by a product, if it is allowed by all elementary rules
      in this product.
    - If a product is empty, all blocks are forbidden by this product.
    - An elementary rule allows all blocks, if the intrinsic label
      consists only of the invalid label
    - An elementary rule forbids all blocks, if the sequence contains only
      zeroes
    - An elementary rule allows a block, if
        - one of the block labels for which the sequence is non-zero is the
          invalid label.
        - the product of labels specified by the sequence contains the
          intrinsic label.
    - The product of labels is a list of labels containing the i-th block label
      n times, if the i-th entry of the sequence is n.

    \ingroup libtensor_symmetry
 **/
template<size_t N>
class evaluation_rule : public timings< evaluation_rule<N> > {
public:
    static const char *k_clazz; //!< Class name

public:
    typedef typename product_table_i::label_t label_t;
    typedef typename product_table_i::label_group_t label_group_t;
    typedef typename product_table_i::label_set_t label_set_t;

    typedef product_rule<N> product_rule_t;
    typedef typename std::list<product_rule_t>::iterator iterator;
    typedef typename std::list<product_rule_t>::const_iterator const_iterator;

private:
    eval_sequence_list<N> *m_slist;
    std::list<product_rule_t> m_rules;

public:
    evaluation_rule() {
        m_slist = new eval_sequence_list<N>();
    }

    ~evaluation_rule() {
        delete m_slist;
    }

    evaluation_rule(const evaluation_rule<N> &other);

    const evaluation_rule<N> &operator=(const evaluation_rule<N> &other);

    /** \brief Create a new (empty) product in rule setup
     **/
    product_rule_t &new_product() {
        m_rules.push_back(product_rule_t(m_slist));
        return m_rules.back();
    }

    /** \brief Delete the list of lists
     **/
    void clear() { m_rules.clear(); m_slist->clear(); }

    /** \brief Checks if sequence of block labels is allowed by the rule
        \param blk_labels Block labels
        \param pt Product table
     **/
    bool is_allowed(const sequence<N, label_t> &blk_labels,
            const product_table_i &pt) const;

    /** \brief Obtain list of sequences
     **/
    eval_sequence_list<N> &get_sequences() { return *m_slist; }

    /** \brief Obtain constant list of sequences
     **/
    const eval_sequence_list<N> &get_sequences() const { return *m_slist; }

    /** \brief STL-style iterator to the 1st product in the setup
     **/
    iterator begin() { return m_rules.begin(); }

    /** \brief STL-style iterator to the 1st product in the setup (const)
     **/
    const_iterator begin() const { return m_rules.begin(); }

    /** \brief STL-style iterator to the end of the product list
     **/
    iterator end() { return m_rules.end(); }

    /** \brief STL-style iterator to the end of the product list (const)
     **/
    const_iterator end() const { return m_rules.end(); }

    /** \brief Return the product pointed to by iterator
     **/
    product_rule_t &get_product(iterator it) { return *it; }

    /** \brief Return the product pointed to by iterator (const)
     **/
    const product_rule_t &get_product(const_iterator it) const { return *it; }
};


} // namespace libtensor


#endif // LIBTENSOR_EVALUATION_RULE_H
