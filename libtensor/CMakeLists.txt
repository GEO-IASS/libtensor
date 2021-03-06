set(SRC_CORE
    defs.C
    exception.C
    version.C
    core/impl/batching_policy_base.C
    core/impl/abs_index.C
    core/impl/allocator.C
    core/impl/combined_orbits.C
    core/impl/dimensions.C
    core/impl/magic_dimensions.C
    core/impl/orbit.C
    core/impl/orbit_list.C
    core/impl/short_orbit.C
    core/impl/subgroup_orbits.C
)

set(SRC_LINALG_ACML
    linalg/acml/linalg_acml_level1.C
    linalg/acml/linalg_acml_level2.C
    linalg/acml/linalg_acml_level3.C
    linalg/acml/lapack_acml.C
)

set(SRC_LINALG_CBLAS
    linalg/cblas/linalg_cblas_level1.C
    linalg/cblas/linalg_cblas_level2.C
    linalg/cblas/linalg_cblas_level3.C
)

set(SRC_LINALG_ESSL
    linalg/essl/linalg_essl_level1.C
    linalg/essl/linalg_essl_level2.C
    linalg/essl/linalg_essl_level3.C
)

set(SRC_LINALG_MKL
    linalg/mkl/linalg_mkl_level1.C
    linalg/mkl/linalg_mkl_level2.C
    linalg/mkl/linalg_mkl_level3.C
    linalg/mkl/lapack_mkl.C
)

set(SRC_LINALG_QCHEM
    linalg/qchem/linalg_qchem_level1.C
    linalg/qchem/linalg_qchem_level2.C
    linalg/qchem/linalg_qchem_level3.C
)

set(SRC_LINALG_GENERIC
    linalg/generic/linalg_generic_level1.C
    linalg/generic/linalg_generic_level2.C
    linalg/generic/linalg_generic_level3.C
)

set(SRC_KERNELS
    kernels/dadd1/kern_dadd1.C
    kernels/dadd2/kern_dadd2.C
    kernels/dcopy/kern_dcopy.C
    kernels/ddiv1/kern_ddiv1.C
    kernels/ddiv2/kern_ddiv2.C
    kernels/ddivadd1/kern_ddivadd1.C
    kernels/dmul1/kern_dmul1.C
    kernels/dmul2/kern_dmul2.C
    kernels/dmuladd1/kern_dmuladd1.C
)

set(SRC_INST
    dense_tensor/impl/dense_tensor.C
    dense_tensor/impl/to_contract2_dims.C
    dense_tensor/impl/to_diag_dims.C
    dense_tensor/impl/to_dirsum_dims.C
    dense_tensor/impl/to_ewmult2_dims.C
    dense_tensor/impl/tod_add.C
    dense_tensor/impl/tod_btconv.C
    dense_tensor/impl/tod_compare.C
    dense_tensor/impl/tod_contract2_1.C
    dense_tensor/impl/tod_contract2_2.C
    dense_tensor/impl/tod_contract2_3.C
    dense_tensor/impl/tod_contract2_4.C
    dense_tensor/impl/tod_contract2_5.C
    dense_tensor/impl/tod_contract2_6.C
    dense_tensor/impl/tod_contract2_7.C
    dense_tensor/impl/tod_contract2_8.C
    dense_tensor/impl/tod_copy.C
    dense_tensor/impl/tod_copy_wnd.C
    dense_tensor/impl/tod_diag.C
    dense_tensor/impl/tod_dirsum.C
    dense_tensor/impl/tod_dotprod.C
    dense_tensor/impl/tod_ewmult2.C
    dense_tensor/impl/tod_extract.C
    dense_tensor/impl/tod_import_raw.C
    dense_tensor/impl/tod_import_raw_stream.C
    dense_tensor/impl/tod_mult.C
    dense_tensor/impl/tod_mult1.C
    dense_tensor/impl/tod_random.C
    dense_tensor/impl/tod_scale.C
    dense_tensor/impl/tod_scatter.C
    dense_tensor/impl/tod_screen.C
    dense_tensor/impl/tod_set.C
    dense_tensor/impl/tod_set_diag.C
    dense_tensor/impl/tod_set_elem.C
    dense_tensor/impl/tod_size.C
    dense_tensor/impl/tod_trace.C
    dense_tensor/impl/tod_vmpriority.C
    symmetry/point_group_table.C
    symmetry/product_table_container.C
    symmetry/product_table_i.C
    symmetry/inst/adjacency_list.C
    symmetry/inst/block_labeling_inst.C
    symmetry/inst/combine_part_inst.C
    symmetry/inst/combine_label_inst.C
    symmetry/inst/er_merge_inst.C
    symmetry/inst/er_optimize_inst.C
    symmetry/inst/er_reduce_inst.C
    symmetry/inst/evaluation_rule_inst.C
    symmetry/inst/permutation_group_inst.C
    symmetry/inst/print_symmetry_inst.C
    symmetry/inst/se_label_inst.C
    symmetry/inst/se_part_inst.C
    symmetry/inst/se_perm_inst.C
    symmetry/inst/so_apply_inst.C
    symmetry/inst/so_apply_se_label_inst.C
    symmetry/inst/so_apply_se_part_inst.C
    symmetry/inst/so_apply_se_perm_inst.C
    symmetry/inst/so_copy_inst.C
    symmetry/inst/so_dirprod_inst.C
    symmetry/inst/so_dirprod_se_label_inst.C
    symmetry/inst/so_dirprod_se_part_inst.C
    symmetry/inst/so_dirprod_se_perm_inst.C
    symmetry/inst/so_dirsum_inst.C
    symmetry/inst/so_dirsum_se_label_inst.C
    symmetry/inst/so_dirsum_se_part_inst.C
    symmetry/inst/so_dirsum_se_perm_inst.C
    symmetry/inst/so_merge_inst.C
    symmetry/inst/so_merge_se_label_inst.C
    symmetry/inst/so_merge_se_part_inst.C
    symmetry/inst/so_merge_se_perm_inst.C
    symmetry/inst/so_permute_inst.C
    symmetry/inst/so_permute_se_label_inst.C
    symmetry/inst/so_permute_se_part_inst.C
    symmetry/inst/so_permute_se_perm_inst.C
    symmetry/inst/so_reduce_inst.C
    symmetry/inst/so_reduce_se_label_inst.C
    symmetry/inst/so_reduce_se_part_inst.C
    symmetry/inst/so_reduce_se_perm_inst.C
    symmetry/inst/so_symmetrize_inst.C
    symmetry/inst/so_symmetrize_se_label_inst.C
    symmetry/inst/so_symmetrize_se_part_inst.C
    symmetry/inst/so_symmetrize_se_perm_inst.C
    btod/btod_diagonalize.C
    btod/btod_tridiagonalize.C
)

set(SRC_GEN_BTOD
    gen_block_tensor/impl/auto_rwlock.C
    gen_block_tensor/impl/gen_bto_contract2_bis.C
)

set(SRC_BTOD
    block_tensor/impl/block_tensor.C
    block_tensor/impl/btod_addition_schedule.C
    block_tensor/impl/btod_add.C
    block_tensor/impl/btod_aux_add.C
    block_tensor/impl/btod_aux_chsym.C
    block_tensor/impl/btod_aux_copy.C
    block_tensor/impl/btod_aux_symmetrize.C
    block_tensor/impl/btod_aux_transform.C
    block_tensor/impl/btod_compare.C
    block_tensor/impl/btod_contract2_1.C
    block_tensor/impl/btod_contract2_2.C
    block_tensor/impl/btod_contract2_3.C
    block_tensor/impl/btod_contract2_4.C
    block_tensor/impl/btod_contract2_5.C
    block_tensor/impl/btod_contract2_6.C
    block_tensor/impl/btod_contract2_7.C
    block_tensor/impl/btod_contract2_8.C
    block_tensor/impl/btod_contract2_clst_builder.C
    block_tensor/impl/btod_contract2_clst_optimize.C
    block_tensor/impl/btod_contract2_nzorb.C
    block_tensor/impl/btod_contract3.C
    block_tensor/impl/btod_copy.C
    block_tensor/impl/btod_diag.C
    block_tensor/impl/btod_dirsum.C
    block_tensor/impl/btod_dotprod.C
    block_tensor/impl/btod_ewmult2.C
    block_tensor/impl/btod_export.C
    block_tensor/impl/btod_extract.C
    block_tensor/impl/btod_mult.C
    block_tensor/impl/btod_mult1.C
    block_tensor/impl/btod_random.C
    block_tensor/impl/btod_scale.C
    block_tensor/impl/btod_set_diag.C
    block_tensor/impl/btod_set_elem.C
    block_tensor/impl/btod_set.C
    block_tensor/impl/btod_shift_diag.C
    block_tensor/impl/btod_size.C
    block_tensor/impl/btod_sum.C
    block_tensor/impl/btod_symcontract3.C
    block_tensor/impl/btod_symmetrize2.C
    block_tensor/impl/btod_symmetrize3.C
    block_tensor/impl/btod_symmetrize4.C
    block_tensor/impl/btod_trace.C
    block_tensor/impl/btod_unfold_block_list.C
    block_tensor/impl/btod_unfold_symmetry.C
    block_tensor/impl/btod_vmpriority.C
)

set(SRC_BLOCK_SPARSE
    block_sparse/sparsity_data.C
    block_sparse/subspace.C
    block_sparse/sparse_bispace_impl.C
    block_sparse/block_loop.C
    block_sparse/sparse_loop_list.C
    block_sparse/sparsity_fuser.C
    block_sparse/sparse_loop_grouper.C
    block_sparse/range.C
    block_sparse/batch_list_builder.C
    block_sparse/subspace_iterator.C
    block_sparse/connectivity.C
    block_sparse/memory_reserve.C
)

set(SRC_DIAG_TENSOR
    diag_block_tensor/impl/diag_block_tensor.C
    diag_block_tensor/impl/diag_btod_addition_schedule.C
    diag_block_tensor/impl/diag_btod_aux_add.C
)

set(SRC_DIAG_TENSOR
    diag_block_tensor/impl/diag_block_tensor.C
    diag_block_tensor/impl/diag_btod_addition_schedule.C
    diag_block_tensor/impl/diag_btod_aux_add.C
    diag_block_tensor/impl/diag_btod_aux_copy.C
    diag_block_tensor/impl/diag_btod_contract2.C
    diag_block_tensor/impl/diag_btod_contract2_clst_builder.C
    diag_block_tensor/impl/diag_btod_copy.C
    diag_block_tensor/impl/diag_btod_dotprod.C
    diag_block_tensor/impl/diag_btod_random.C
    diag_block_tensor/impl/diag_btod_unfold_block_list.C
    diag_block_tensor/impl/tod_conv_diag_block_tensor.C
    diag_tensor/impl/diag_tensor_space.C
    diag_tensor/impl/diag_tensor.C
    diag_tensor/impl/tod_conv_diag_tensor.C
    diag_tensor/impl/diag_to_add_space.C
    diag_tensor/impl/diag_to_contract2_space.C
    diag_tensor/impl/diag_tod_adjust_space.C
    diag_tensor/impl/diag_tod_aux_constr_add.C
    diag_tensor/impl/diag_tod_aux_constr_base.C
    diag_tensor/impl/diag_tod_aux_dotprod.C
    diag_tensor/impl/diag_tod_contract2.C
    diag_tensor/impl/diag_tod_contract2s.C
    diag_tensor/impl/diag_tod_copy.C
    diag_tensor/impl/diag_tod_dotprod.C
    diag_tensor/impl/diag_tod_mult1.C
    diag_tensor/impl/diag_tod_random.C
    diag_tensor/impl/diag_tod_set.C
)

set(SRC_EXPR
    expr/btensor/impl/eval_btensor_double.C
    expr/btensor/impl/eval_btensor_double_add.C
    expr/btensor/impl/eval_btensor_double_autoselect.C
    expr/btensor/impl/eval_btensor_double_contract.C
    expr/btensor/impl/eval_btensor_double_copy.C
    expr/btensor/impl/eval_btensor_double_diag.C
    expr/btensor/impl/eval_btensor_double_dirsum.C
    expr/btensor/impl/eval_btensor_double_div.C
    expr/btensor/impl/eval_btensor_double_dot_product.C
    expr/btensor/impl/eval_btensor_double_scale.C
    expr/btensor/impl/eval_btensor_double_set.C
    expr/btensor/impl/eval_btensor_double_symm.C
    expr/btensor/impl/eval_btensor_double_trace.C
    expr/btensor/impl/eval_tree_builder_btensor.C
    expr/btensor/impl/node_interm.C
    expr/dag/expr_tree.C
    expr/dag/graph.C
    expr/dag/node_add.C
    expr/dag/node_assign.C
    expr/dag/node_const_scalar.C
    expr/dag/node_contract.C
    expr/dag/node_diag.C
    expr/dag/node_dirsum.C
    expr/dag/node_div.C
    expr/dag/node_dot_product.C
    expr/dag/node_ident.C
    expr/dag/node_null.C
    expr/dag/node_product.C
    expr/dag/node_scalar.C
    expr/dag/node_scale.C
    expr/dag/node_set.C
    expr/dag/node_symm.C
    expr/dag/node_trace.C
    expr/dag/node_transform.C
    expr/dag/node_unblock.C
    expr/dag/node_reblock.C
    expr/dag/print_node.C
    expr/dag/print_tree.C
    expr/eval/default_eval_selector.C
    expr/eval/eval.C
    expr/eval/eval_register.C
    expr/opt/opt_add_before_transf.C
    expr/opt/opt_merge_adjacent_add.C
    expr/opt/opt_merge_adjacent_transf.C
    expr/opt/opt_merge_equiv_ident.C
)

set(SRC_CTF
    ctf_dense_tensor/impl/ctf.C
    ctf_dense_tensor/impl/ctf_dense_tensor.C
    ctf_dense_tensor/impl/ctf_fctr.C
    ctf_dense_tensor/impl/ctf_symmetry.C
    ctf_dense_tensor/impl/ctf_tod_collect.C
    ctf_dense_tensor/impl/ctf_tod_contract2_1.C
    ctf_dense_tensor/impl/ctf_tod_contract2_2.C
    ctf_dense_tensor/impl/ctf_tod_contract2_3.C
    ctf_dense_tensor/impl/ctf_tod_contract2_4.C
    ctf_dense_tensor/impl/ctf_tod_contract2_5.C
    ctf_dense_tensor/impl/ctf_tod_contract2_6.C
    ctf_dense_tensor/impl/ctf_tod_contract2_7.C
    ctf_dense_tensor/impl/ctf_tod_contract2_8.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_1.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_2.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_3.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_4.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_5.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_6.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_7.C
    ctf_dense_tensor/impl/ctf_tod_contract2_streamed_8.C
    ctf_dense_tensor/impl/ctf_tod_copy.C
    ctf_dense_tensor/impl/ctf_tod_diag.C
    ctf_dense_tensor/impl/ctf_tod_dirsum.C
    ctf_dense_tensor/impl/ctf_tod_dotprod.C
    ctf_dense_tensor/impl/ctf_tod_distribute.C
    ctf_dense_tensor/impl/ctf_tod_ewmult2.C
    ctf_dense_tensor/impl/ctf_tod_mult.C
    ctf_dense_tensor/impl/ctf_tod_mult1.C
    ctf_dense_tensor/impl/ctf_tod_random.C
    ctf_dense_tensor/impl/ctf_tod_scale.C
    ctf_dense_tensor/impl/ctf_tod_scatter.C
    ctf_dense_tensor/impl/ctf_tod_set.C
    ctf_dense_tensor/impl/ctf_tod_set_diag.C
    ctf_dense_tensor/impl/ctf_tod_set_symmetry.C
    ctf_dense_tensor/impl/ctf_tod_trace.C
    ctf_block_tensor/impl/ctf_block_tensor.C
    ctf_block_tensor/impl/ctf_btod_addition_schedule.C
    ctf_block_tensor/impl/ctf_btod_aux_add.C
    ctf_block_tensor/impl/ctf_btod_aux_chsym.C
    ctf_block_tensor/impl/ctf_btod_aux_copy.C
    ctf_block_tensor/impl/ctf_btod_aux_symmetrize.C
    ctf_block_tensor/impl/ctf_btod_aux_transform.C
    ctf_block_tensor/impl/ctf_btod_collect.C
    ctf_block_tensor/impl/ctf_btod_contract2_1.C
    ctf_block_tensor/impl/ctf_btod_contract2_2.C
    ctf_block_tensor/impl/ctf_btod_contract2_3.C
    ctf_block_tensor/impl/ctf_btod_contract2_4.C
    ctf_block_tensor/impl/ctf_btod_contract2_5.C
    ctf_block_tensor/impl/ctf_btod_contract2_6.C
    ctf_block_tensor/impl/ctf_btod_contract2_7.C
    ctf_block_tensor/impl/ctf_btod_contract2_8.C
    ctf_block_tensor/impl/ctf_btod_contract2_clst_builder.C
    ctf_block_tensor/impl/ctf_btod_contract2_nzorb.C
    ctf_block_tensor/impl/ctf_btod_copy.C
    ctf_block_tensor/impl/ctf_btod_diag.C
    ctf_block_tensor/impl/ctf_btod_dirsum.C
    ctf_block_tensor/impl/ctf_btod_distribute.C
    ctf_block_tensor/impl/ctf_btod_dotprod.C
    ctf_block_tensor/impl/ctf_btod_ewmult2.C
    ctf_block_tensor/impl/ctf_btod_mult.C
    ctf_block_tensor/impl/ctf_btod_mult1.C
    ctf_block_tensor/impl/ctf_btod_random.C
    ctf_block_tensor/impl/ctf_btod_scale.C
    ctf_block_tensor/impl/ctf_btod_set.C
    ctf_block_tensor/impl/ctf_btod_set_diag.C
    ctf_block_tensor/impl/ctf_btod_set_symmetry.C
    ctf_block_tensor/impl/ctf_btod_shift_diag.C
    ctf_block_tensor/impl/ctf_btod_sum.C
    ctf_block_tensor/impl/ctf_btod_symmetrize2.C
    ctf_block_tensor/impl/ctf_btod_symmetrize3.C
    ctf_block_tensor/impl/ctf_btod_trace.C
    ctf_block_tensor/impl/ctf_btod_unfold_block_list.C
    ctf_block_tensor/impl/ctf_symmetry_builder.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_add.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_autoselect.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_contract.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_convert.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_copy.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_diag.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_dirsum.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_div.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_dot_product.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_scale.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_set.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_symm.C
    expr/ctf_btensor/impl/eval_ctf_btensor_double_trace.C
    expr/ctf_btensor/impl/eval_tree_builder_ctf_btensor.C
    expr/ctf_btensor/impl/node_ctf_btensor_interm.C
)

set(SRC_ARMA
    arma/impl/btod_export_arma.C
)

set(SRC_XM
    libxm/xm.c
    libxm/alloc.c
    block_tensor/impl/btod_contract2_1_xm.C
    block_tensor/impl/btod_contract2_2_xm.C
    block_tensor/impl/btod_contract2_3_xm.C
    block_tensor/impl/btod_contract2_4_xm.C
    block_tensor/impl/btod_contract2_5_xm.C
    block_tensor/impl/btod_contract2_6_xm.C
    block_tensor/impl/btod_contract2_7_xm.C
    block_tensor/impl/btod_contract2_8_xm.C
)

if(USE_ACML)
    set(SRC_LINALG ${SRC_LINALG_GENERIC} ${SRC_LINALG_ACML})
elseif(USE_CBLAS OR USE_GSL)
    set(SRC_LINALG ${SRC_LINALG_GENERIC} ${SRC_LINALG_CBLAS})
elseif(USE_ESSL)
    set(SRC_LINALG ${SRC_LINALG_GENERIC} ${SRC_LINALG_ESSL})
elseif(USE_MKL)
    set(SRC_LINALG ${SRC_LINALG_GENERIC} ${SRC_LINALG_MKL})
else(USE_ACML)
    set(SRC_LINALG ${SRC_LINALG_GENERIC})
endif(USE_ACML)

set(TARGETS tensor_core tensor tensor_block_sparse)

set(SRC ${SRC_LINALG} ${SRC_KERNELS} ${SRC_GEN_BTOD} ${SRC_BTOD}
    ${SRC_DIAG_TENSOR} ${SRC_INST} ${SRC_EXPR})
if(WITH_ARMADILLO)
    set(SRC ${SRC} ${SRC_ARMA})
endif(WITH_ARMADILLO)
if(WITH_XM)
    set(SRC ${SRC} ${SRC_XM})
    add_definitions(-DWITH_LIBXM)
endif(WITH_XM)
if(WITH_CTF)
    set(SRC ${SRC} ${SRC_CTF})
    set_property(SOURCE ${SRC_CTF} APPEND PROPERTY COMPILE_FLAGS "-std=c++0x")
endif(WITH_CTF)

add_library(tensor_core ${SRC_CORE})
target_link_libraries(tensor_core util)
add_library(tensor ${SRC})
target_link_libraries(tensor tensor_core)
add_library(tensor_block_sparse ${SRC_BLOCK_SPARSE})
target_link_libraries(tensor_block_sparse tensor_core)

if(QCHEM_SOURCE_DIR)
    set(TARGETS ${TARGETS} tensor_qchem)
    add_library(tensor_qchem ${SRC_LINALG_GENERIC} ${SRC_LINALG_QCHEM})
    target_link_libraries(tensor_qchem tensor_core)
endif(QCHEM_SOURCE_DIR)

set_property(TARGET ${TARGETS} APPEND PROPERTY
    COMPILE_DEFINITIONS $<$<CONFIG:Debug>:LIBTENSOR_DEBUG>)
set_property(TARGET ${TARGETS} APPEND PROPERTY
    COMPILE_DEFINITIONS LIBTENSOR_TIMINGS)
if(HAVE_LIBVMM)
    set_property(TARGET ${TARGETS} APPEND PROPERTY
        COMPILE_DEFINITIONS $<$<CONFIG:Debug>:LIBVMM_DEBUG>)
else(HAVE_LIBVMM)
    set_property(TARGET ${TARGETS} APPEND PROPERTY
        COMPILE_DEFINITIONS WITHOUT_LIBVMM)
endif(HAVE_LIBVMM)
