#ifndef LIBTENSOR_EXPR_TENSOR_FROM_NODE_H
#define LIBTENSOR_EXPR_TENSOR_FROM_NODE_H

#include <libtensor/expr/iface/node_ident_any_tensor.h>
#include "node_interm.h"

namespace libtensor {
namespace expr {
namespace eval_btensor_double {


template<size_t N, typename T>
class btensor_from_node {
private:
    const expr_tree &m_tree; //!< Expression tree
    expr_tree::node_id_t m_head; //!< Head node ID
    tensor_transf<N, T> m_tr; //!< Transformation from leaf to head
    expr_tree::node_id_t m_leaf; //!< Leaf node ID

public:
    btensor_from_node(const expr_tree &tree, expr_tree::node_id_t head);

    const tensor_transf<N, T> &get_transf() const {
        return m_tr;
    }

    btensor_i<N, T> &get_btensor() const;
    btensor<N, T> &get_or_create_btensor(const block_index_space<N> &bis);

};


template<size_t N, typename T>
expr_tree::node_id_t transf_from_node(const expr_tree &tree,
    expr_tree::node_id_t head, tensor_transf<N, T> &tr);


template<size_t N, typename T>
btensor_from_node<N, T>::btensor_from_node(const expr_tree &tree,
    expr_tree::node_id_t head) :
    m_tree(tree), m_head(head), m_leaf(transf_from_node(tree, head, m_tr)) {

}


template<size_t N, typename T>
btensor_i<N, T> &btensor_from_node<N, T>::get_btensor() const {

    const node &n = m_tree.get_vertex(m_leaf);

    if(n.check_type<node_ident>()) {

        const node_ident_any_tensor<N, T> &ni =
            n.template recast_as< node_ident_any_tensor<N, T> >();
        any_tensor<N, T> &t = ni.get_tensor();
        return t.template get_tensor< btensor_i<N, T> >();

    } else if(n.check_type<node_interm_base>()) {

        const node_interm<N, T> &ni =
        		n.template recast_as< node_interm<N, T> >();
        btensor_placeholder<N, T> &ph =
            btensor_placeholder<N, T>::from_any_tensor(ni.get_tensor());
        if(ph.is_empty()) {
            throw eval_exception(__FILE__, __LINE__,
                "libtensor::expr::eval_btensor_double",
                "btensor_from_node<N, T>", "get_btensor()",
                "Intermediate does not exist.");
        }
        return ph.get_btensor();

    } else {

        throw eval_exception(__FILE__, __LINE__,
            "libtensor::expr::eval_btensor_double",
            "btensor_from_node<N, T>", "get_btensor()",
            "Given node is not a tensor.");

    }
}


template<size_t N, typename T>
btensor<N, T> &btensor_from_node<N, T>::get_or_create_btensor(
    const block_index_space<N> &bis) {

    const node &n = m_tree.get_vertex(m_leaf);

    if(n.check_type<node_ident>()) {

        const node_ident_any_tensor<N, T> &ni =
            n.recast_as< node_ident_any_tensor<N, T> >();
        return btensor<N, T>::from_any_tensor(ni.get_tensor());

    } else if(n.check_type<node_interm_base>()) {

        const node_interm<N, T> &ni =
        		n.template recast_as< node_interm<N, T> >();
        btensor_placeholder<N, T> &ph =
            btensor_placeholder<N, T>::from_any_tensor(ni.get_tensor());
        if(ph.is_empty()) ph.create_btensor(bis);
        return ph.get_btensor();

    } else {

        throw eval_exception(__FILE__, __LINE__,
            "libtensor::expr::eval_btensor_double",
            "btensor_from_node<N, T>", "get_btensor()",
            "Given node is not a tensor.");

    }
}


template<size_t N, typename T>
expr_tree::node_id_t transf_from_node(
    const expr_tree &tree, expr_tree::node_id_t head, tensor_transf<N, T> &tr) {

    const node &n = tree.get_vertex(head);

    if(n.check_type<node_ident>()) {
        return head;
    } else if(n.check_type<node_interm_base>()) {
        return head;
    } else if(n.check_type<node_transform_base>()) {

        const node_transform<T> &nt =
        		n.template recast_as< node_transform<T> >();
        if(N != nt.get_perm().size()) {
            throw eval_exception(__FILE__, __LINE__,
                "libtensor::expr::eval_btensor_double", 0, "transf_from_node()",
                "Malformed expression (bad tensor transformation).");
        }
        sequence<N, size_t> seq1(0), seq2(0);
        for(size_t i = 0; i < N; i++) {
            seq1[i] = i;
            seq2[i] = nt.get_perm().at(i);
        }
        permutation_builder<N> pb(seq2, seq1);
        tensor_transf<N, T> tr1(pb.get_perm(), nt.get_coeff());

        const expr_tree::edge_list_t &e = tree.get_edges_out(head);
        expr_tree::node_id_t leaf = transf_from_node(tree, e[0], tr);
        tr.transform(tr1);
        return leaf;

    } else {
        return head;
    }
}


} // namespace eval_btensor_double
} // namespace expr
} // namespace libtensor

#endif // LIBTENSOR_EXPR_TENSOR_FROM_NODE_H
