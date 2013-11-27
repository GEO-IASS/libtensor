#ifndef LIBTENSOR_ER_REDUCE_H
#define LIBTENSOR_ER_REDUCE_H

#include <libtensor/timings.h>
#include "adjacency_list.h"
#include "../evaluation_rule.h"
#include "../product_table_i.h"


namespace libtensor {


/** \brief Reduce dimension of evaluation rule by summation over
        certain dimensions.

    The reduction is performed according to \c m_rmap and \c m_rdim.
    \c m_rmap specifies which input dimensions end up at which output
    dimensions, as well as the input dimensions which are going to be
    reduced. The latter dimensions are given by values larger than N - M
    in \c m_rmap. Since the reduction can be performed in multiple steps
    the value also indicates the reduction step (i.e. value \f$ N - M \f$
    refers to the first reduction step, \f$ N - M + 1 \f$ to the second, ...).

    \ingroup libtensor_symmetry
 **/
template<size_t N, size_t M>
class er_reduce : public timings< er_reduce<N, M> > {
public:
    static const char *k_clazz; //!< Class name

public:
    typedef typename product_table_i::label_group_t label_group_t;
    typedef typename product_table_i::label_set_t label_set_t;

private:
    const evaluation_rule<N> &m_rule; //!< Input rule
    const product_table_i &m_pt; //!< Product table

    sequence<N, size_t> m_rmap; //!< Reduction map
    sequence<M, label_group_t> m_rdims; //!< Reduction dimension
    size_t m_nrsteps; //!< Number of reduction steps

public:
    /** \brief Constructor
        \param rule Input rule
        \param rmap Index map input->output
        \param rdims Labels of the reduction steps
        \param id Product table ID
     **/
    er_reduce(const evaluation_rule<N> &rule, const sequence<N, size_t> &rmap,
            const sequence<M, label_group_t> &rdims, const std::string &id);

    /** \brief Destructor
     **/
    ~er_reduce();

    /** \brief Perform reduction
        \param rule Output rule
     **/
    void perform(evaluation_rule<N - M> &to) const;

private:
    /** \brief Reduce the product rule
        \param pr Product rule to reduce (input)
        \param slist List of sequences (input)
        \param rsteps_in_seq Reduction steps in the sequences (input)
        \param to Result rule to add the product to
        \return True if a product rule was added, false
            if the product is always allowed
     **/
    bool reduce_product(const product_rule<N> &pr,
            const eval_sequence_list<N> &slist,
            const std::vector<size_t> &rsteps_in_seq,
            evaluation_rule<N - M> &to) const;

    /** \brief Combine the sequences given by slist and clist into a sequence
            of remaining indexes and a sequence of reduced indexes.
        \param slist List of sequences
        \param clist Numbers of sequences to combine
        \param seq_list List to append sequence of remaining indexes to.
        \param rseq_list List to append sequence of reduced indexes to.
        \return Number of remaining indexes in the sequence.
     **/
    size_t append_seq(const eval_sequence_list<N> &slist,
            const std::vector<size_t> &clist,
            std::vector< sequence<N - M, size_t> > &seq_list,
            std::vector< sequence<M, size_t> > &rseq_list) const;

    void append_intr(const std::vector<label_set_t> &cilist, size_t nmrsteps,
            std::list< std::vector<label_set_t> > &ilist) const;

    size_t get_rstep_multiplicity(const adjacency_list &alist,
            const std::vector<size_t> &clist) const;

    void create_list(const std::vector<label_set_t> &in,
            std::list<label_group_t> &out) const;

    void get_product_labels(size_t n, label_set_t &ls) const;
};


} // namespace libtensor


#endif // LIBTENSOR_ER_REDUCE_H
