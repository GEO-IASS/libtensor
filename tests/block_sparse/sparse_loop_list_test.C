/*
 * sparse_loop_list_test.C
 *
 *  Created on: Nov 13, 2013
 *      Author: smanzer
 */

#include <libtensor/block_sparse/sparse_loop_list.h>
#include <libtensor/block_sparse/block_permute_kernel.h>
#include <libtensor/block_sparse/block_contract2_kernel.h>
#include "sparse_loop_list_test.h"

using namespace std;

namespace libtensor
{

void sparse_loop_list_test::perform() throw(libtest::test_exception) {
	test_construct_invalid_loop_bispaces();
    test_construct_all_ignored();
    test_construct_duplicate_subspaces_looped();

    test_run_block_permute_kernel_2d();
    test_run_block_permute_kernel_2d_sparse();
    test_run_block_permute_kernel_3d_120();
    test_run_block_permute_kernel_3d_120_sparse();

    test_run_block_contract2_kernel_2d_2d();
    test_run_block_contract2_kernel_3d_2d();

#if 0
    test_run_fixed_blocks_invalid_bispace_idx();
    test_run_fixed_blocks_not_enough_block_indices();
    test_run_fixed_blocks_bpk_2d();
#endif
}

void sparse_loop_list_test::test_construct_invalid_loop_bispaces() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_construct_invalid_loop_bispaces()";

	//bispaces
    sparse_bispace<1> spb_1(4);
    vector<size_t> split_points_1;
    split_points_1.push_back(2);
    spb_1.split(split_points_1);

    sparse_bispace<1> spb_2(5);
    vector<size_t> split_points_2;
    split_points_2.push_back(2);
    spb_2.split(split_points_2);

    sparse_bispace<1> spb_3(6);
    vector<size_t> split_points_3;
    split_points_3.push_back(2);
    split_points_3.push_back(4);
    spb_3.split(split_points_3);

    vector<sparse_bispace_any_order> bispaces_1;
    bispaces_1.push_back(spb_1|spb_2|spb_3);
    bispaces_1.push_back(spb_2|spb_3);

    //We alter middle subspace of first bispace to make them not match
    vector<sparse_bispace_any_order> bispaces_2;
    bispaces_2.push_back(spb_1|spb_3|spb_3);
    bispaces_2.push_back(spb_2|spb_3);

    vector<block_loop> loops(1,block_loop(bispaces_1));
    loops[0].set_subspace_looped(0,1);
    loops.push_back(block_loop(bispaces_2));
    loops[1].set_subspace_looped(0,2);

    //Should fail due to incompatible bispaces
    bool threw_exception = false;
    try
    {
        sparse_loop_list sll(loops);
    }
    catch(bad_parameter&)
    {
    	threw_exception = true;
    }

    if(!threw_exception)
    {
        fail_test(test_name,__FILE__,__LINE__,
                "sparse_loop_list::sparse_loop_list(...) did not throw exception when adding loop with invalid bispaces");
    }
}

void sparse_loop_list_test::test_construct_all_ignored() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_construct_all_ignore()";

	//bispaces
    sparse_bispace<1> spb_1(4);
    vector<size_t> split_points_1;
    split_points_1.push_back(2);
    spb_1.split(split_points_1);

    sparse_bispace<1> spb_2(5);
    vector<size_t> split_points_2;
    split_points_2.push_back(2);
    spb_2.split(split_points_2);

    sparse_bispace<1> spb_3(6);
    vector<size_t> split_points_3;
    split_points_3.push_back(2);
    split_points_3.push_back(4);
    spb_3.split(split_points_3);

    vector< sparse_bispace_any_order > bispaces_1;
    bispaces_1.push_back(spb_1|spb_2|spb_3);
    bispaces_1.push_back(spb_2|spb_3);

    //Should fail due to loop not touching any subspaces
    bool threw_exception = false;
    try
    {
        sparse_loop_list sll(vector<block_loop>(1,block_loop(bispaces_1)));
    }
    catch(bad_parameter&)
    {
    	threw_exception = true;
    }

    if(!threw_exception)
    {
        fail_test(test_name,__FILE__,__LINE__,
                "sparse_loop_list::sparse_loop_list(...) did not throw exception when adding loop that does not touch any subspaces");
    }
}

void sparse_loop_list_test::test_construct_duplicate_subspaces_looped() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_construct_duplicate_subspaces_looped()";

	//bispaces
    sparse_bispace<1> spb_1(4);
    vector<size_t> split_points_1;
    split_points_1.push_back(2);
    spb_1.split(split_points_1);

    sparse_bispace<1> spb_2(5);
    vector<size_t> split_points_2;
    split_points_2.push_back(2);
    spb_2.split(split_points_2);

    sparse_bispace<1> spb_3(6);
    vector<size_t> split_points_3;
    split_points_3.push_back(2);
    split_points_3.push_back(4);
    spb_3.split(split_points_3);

    vector< sparse_bispace_any_order > bispaces_1;
    bispaces_1.push_back(spb_1|spb_2|spb_3);
    bispaces_1.push_back(spb_2|spb_3);

    vector<block_loop> loops(4,block_loop(bispaces_1));
    loops[0].set_subspace_looped(0,1);
    loops[1].set_subspace_looped(0,2);
    loops[2].set_subspace_looped(1,1);
    loops[3].set_subspace_looped(0,1); //Intentional duplicate

    //Should fail due to two loops touching the same subspace of the same bispace
    bool threw_exception = false;
    try
    {
        sparse_loop_list sll(loops);
    }
    catch(bad_parameter&)
    {
    	threw_exception = true;
    }

    if(!threw_exception)
    {
        fail_test(test_name,__FILE__,__LINE__,
                "sparse_loop_list::sparse_loop_list(...) did not throw exception when adding duplicate loops over the same bispaces");
    }
}

//Permutation 01
//Permuted nested loops
void sparse_loop_list_test::test_run_block_permute_kernel_2d() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_block_permute_kernel_2d()";

	//Indices in comments are block indices
    double test_input_arr[20] = { //i = 0, j = 0
                                  1,2,
                                  6,7,

                                 //i = 0, j = 1
                                 3,4,5,
                                 8,9,10,

                                 //i = 1, j = 0
                                 11,12,
                                 16,17,

                                 //i = 0, j = 1
                                 13,14,15,
                                 18,19,20 };

    double correct_output_arr[20] = { //j = 0, i = 0
                                 	  1,6,
                                      2,7,

									  //j = 0, i = 1
									  11,16,
									  12,17,

									  //j = 1, i = 0
									  3,8,
									  4,9,
									  5,10,

									  //j = 1, i = 1
									  13,18,
									  14,19,
									  15,20 };

    double test_output_arr[20];

    //First bispace (slow index) and splitting
    sparse_bispace<1> spb_1(4);
    vector<size_t> split_points_1;
    split_points_1.push_back(2);
    spb_1.split(split_points_1);

    //Second bispace (fast index) and splitting
    sparse_bispace<1> spb_2(5);
    vector<size_t> split_points_2;
    split_points_2.push_back(2);
    spb_2.split(split_points_2);

    vector< sparse_bispace_any_order > bispaces;
    bispaces.push_back(spb_2 | spb_1);
    bispaces.push_back(spb_1 | spb_2);

    runtime_permutation perm(2);
    perm.permute(0,1);
    block_permute_kernel<double> bpk(perm);


    //We stride the input, not the output
    vector<block_loop> loops(2,block_loop(bispaces));
    loops[0].set_subspace_looped(0,0);
    loops[0].set_subspace_looped(1,1);
    loops[1].set_subspace_looped(0,1);
    loops[1].set_subspace_looped(1,0);

    sparse_loop_list sll(loops);
    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr);
    sll.run(bpk,ptrs);

    for(int i = 0; i < 20; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "sparse_loop_list::run(...) produced incorrect output");
        }
    }
}

void sparse_loop_list_test::test_run_block_permute_kernel_2d_sparse() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_block_permute_kernel_2d_sparse()";

	//Indices in comments are block indices
    double test_input_arr[14] = { //i = 0, j = 0
                                  1,2,
                                  3,4,

                                  //i = 0, j = 2
                                  5,6,7,
                                  8,9,10,

                                  //i = 1, j = 1
                                  11,12,
                                  13,14};

    double correct_output_arr[14] = { //j = 0, i = 0
                                      1,3,
                                      2,4,

									  //j = 1, i = 1
                                      11,13,
                                      12,14,

									  //j = 2, i = 0
                                      5,8,
                                      6,9,
                                      7,10};

    double test_output_arr[14];

    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr);

    //First bispace (slow index) and splitting
    sparse_bispace<1> spb_1(4);
    vector<size_t> split_points_1;
    split_points_1.push_back(2);
    spb_1.split(split_points_1);

    //Second bispace (fast index) and splitting
    sparse_bispace<1> spb_2(7);
    vector<size_t> split_points_2;
    split_points_2.push_back(2);
    split_points_2.push_back(4);
    spb_2.split(split_points_2);

    //Sparsity information
    vector< sequence<2,size_t> > sig_blocks(3);
    sig_blocks[0][0] = 0;
    sig_blocks[0][1] = 0;
    sig_blocks[1][0] = 0;
    sig_blocks[1][1] = 2;
    sig_blocks[2][0] = 1;
    sig_blocks[2][1] = 1;

    permutation<2> perm;
    perm.permute(0,1);
    sparse_bispace<2> two_d_input = spb_1 % spb_2 << sig_blocks;
    sparse_bispace<2> two_d_output = two_d_input.permute(perm);
    vector< sparse_bispace_any_order > bispaces(1,two_d_output);
    bispaces.push_back(two_d_input);

    runtime_permutation rperm(2);
    rperm.permute(0,1);
    block_permute_kernel<double> bpk(rperm);


    vector<block_loop> loops(2,block_loop(bispaces));
    loops[0].set_subspace_looped(0,0);
    loops[0].set_subspace_looped(1,1);
    loops[1].set_subspace_looped(0,1);
    loops[1].set_subspace_looped(1,0);

    sparse_loop_list sll(loops);
    sll.run(bpk,ptrs);

    for(int i = 0; i < 14; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "block_loop<M,N,T>::run(...) produced incorrect output");
        }
    }
}

void sparse_loop_list_test::test_run_block_permute_kernel_3d_120() throw(libtest::test_exception)
{
    static const char *test_name = "block_loop_test::test_run_block_permute_kernel_3d_120()";

    //3x4x5
    //Permutation is kij -> ijk
	//Indices in comments are block indices
    double test_input_arr[60] = { // k = 0, i = 0; j = 0
                                  1,2,
                                  3,4,
                                  5,6,

                                  // k = 0, i = 0, j = 1
                                  7,8,9,
                                  10,11,12,
                                  13,14,15,

                                  // k = 0, i = 1, j = 0
                                  16,17,

                                  // k = 0, i = 1, j = 1
                                  18,19,20,

                                  //k = 1, i = 0, j = 0
                                  21,22,
                                  23,24,
                                  25,26,
                                  27,28,
                                  29,30,
                                  31,32,

                                  //k = 1, i = 0, j = 1
                                  33,34,35,
                                  36,37,38,
                                  39,40,41,
                                  42,43,44,
                                  45,46,47,
                                  48,49,50,

                                  //k = 1, i = 1, j = 0
                                  51,52,
                                  53,54,

                                  //k = 1, i = 1, j = 1
                                  55,56,57,
                                  58,59,60};

    double correct_output_arr[60] = { //i = 0, j = 0, k = 0
                                      1,
                                      2,
                                      3,
                                      4,
                                      5,
                                      6,

                                      //i = 0, j = 0, k = 1
                                      21,27,
                                      22,28,
                                      23,29,
                                      24,30,
                                      25,31,
                                      26,32,

                                      //i = 0, j = 1, k = 0
                                      7,8,9,
                                      10,11,12,
                                      13,14,15,

                                      //i = 0, j = 1, k = 1
                                      33,42,
                                      34,43,
                                      35,44,
                                      36,45,
                                      37,46,
                                      38,47,
                                      39,48,
                                      40,49,
                                      41,50,

                                      //i = 1, j = 0, k = 0
                                      16,17,

                                      //i = 1, j = 0, k = 1
                                      51,53,
                                      52,54,

                                      //i = 1, j = 1, k = 0
                                      18,19,20,

                                      //i = 1, j = 1, k = 1
                                      55,58,
                                      56,59,
                                      57,60};

    double test_output_arr[60];

    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr);

    //First bispace (slow index in input) and splitting
    sparse_bispace<1> spb_1(3);
    vector<size_t> split_points_1;
    split_points_1.push_back(1);
    spb_1.split(split_points_1);

    //Second bispace (mid index in input) and splitting
    sparse_bispace<1> spb_2(4);
    vector<size_t> split_points_2;
    split_points_2.push_back(3);
    spb_2.split(split_points_2);

    //Third bispace (fast index in input) and splitting
    sparse_bispace<1> spb_3(5);
    vector<size_t> split_points_3;
    split_points_3.push_back(2);
    spb_3.split(split_points_3);

    vector<sparse_bispace_any_order> bispaces;
    bispaces.push_back(spb_2 | spb_3 | spb_1);
    bispaces.push_back(spb_1 | spb_2 | spb_3);

    runtime_permutation perm(3);
    perm.permute(0,2);
    perm.permute(0,1);
    block_permute_kernel<double> bpk(perm);

    vector<block_loop> loops(3,block_loop(bispaces));
    loops[0].set_subspace_looped(0,0);
    loops[0].set_subspace_looped(1,1);
    loops[1].set_subspace_looped(0,1);
    loops[1].set_subspace_looped(1,2);
    loops[2].set_subspace_looped(0,2);
    loops[2].set_subspace_looped(1,0);
    sparse_loop_list sll(loops);
    sll.run(bpk,ptrs);

    for(int i = 0; i < 60; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "sparse_loop_list::run(...) produced incorrect output");
        }
    }

}

void sparse_loop_list_test::test_run_block_permute_kernel_3d_120_sparse() throw(libtest::test_exception)
{
    static const char *test_name = "block_loop_test::test_run_block_permute_kernel_3d_120_sparse()";

    //3x4x5
    //Permutation is kij -> ijk
	//Indices in comments are block indices
    double test_input_arr[35] = { //k = 0, i = 0; j = 0
                                  1,2,
                                  3,4,
                                  5,6,

                                  //k = 0, i = 0, j = 1
                                  7,8,9,
                                  10,11,12,
                                  13,14,15,

                                  //k = 0, i = 1, j = 0
                                  16,17,

                                  //k = 1, i = 0, j = 0
                                  21,22,
                                  23,24,
                                  25,26,
                                  27,28,
                                  29,30,
                                  31,32,

                                  //k = 1, i = 1, j = 1
                                  55,56,57,
                                  58,59,60};

    double correct_output_arr[35] = { //i = 0 j = 0 k = 0
                                      1,
                                      2,
                                      3,
                                      4,
                                      5,
                                      6,


                                      //i = 0 j = 0 k = 1
                                      21,27,
                                      22,28,
                                      23,29,
                                      24,30,
                                      25,31,
                                      26,32,

                                      //i = 0 j = 1 k = 0
                                      7,
                                      8,
                                      9,
                                      10,
                                      11,
                                      12,
                                      13,
                                      14,
                                      15,

                                      //i = 1 j = 0 k = 0
                                      16,
                                      17,

                                      // i = 1, j = 1 k = 1
                                      55,58,
                                      56,59,
                                      57,60};

    double test_output_arr[35];

    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr);

    //First bispace (slow index in input) and splitting
    sparse_bispace<1> spb_1(3);
    vector<size_t> split_points_1;
    split_points_1.push_back(1);
    spb_1.split(split_points_1);

    //Second bispace (mid index in input) and splitting
    sparse_bispace<1> spb_2(4);
    vector<size_t> split_points_2;
    split_points_2.push_back(3);
    spb_2.split(split_points_2);

    //Third bispace (fast index in input) and splitting
    sparse_bispace<1> spb_3(5);
    vector<size_t> split_points_3;
    split_points_3.push_back(2);
    spb_3.split(split_points_3);

    //Sparsity data
    vector< sequence<3,size_t> > sig_blocks(5);
    sig_blocks[0][0] = 0;
    sig_blocks[0][1] = 0;
    sig_blocks[0][2] = 0;
    sig_blocks[1][0] = 0;
    sig_blocks[1][1] = 0;
    sig_blocks[1][2] = 1;
    sig_blocks[2][0] = 0;
    sig_blocks[2][1] = 1;
    sig_blocks[2][2] = 0;
    sig_blocks[3][0] = 1;
    sig_blocks[3][1] = 0;
    sig_blocks[3][2] = 0;
    sig_blocks[4][0] = 1;
    sig_blocks[4][1] = 1;
    sig_blocks[4][2] = 1;

    sparse_bispace<3> three_d_input = spb_1 % spb_2 % spb_3 << sig_blocks;
    permutation<3> perm;
    perm.permute(0,2).permute(0,1);
    sparse_bispace<3> three_d_output = three_d_input.permute(perm);
    vector< sparse_bispace_any_order > bispaces(1,three_d_output);
    bispaces.push_back(three_d_input);

    runtime_permutation rperm(3);
    rperm.permute(0,2);
    rperm.permute(0,1);
    block_permute_kernel<double> bpk(rperm);

    vector<block_loop> loops(3,block_loop(bispaces));
    loops[0].set_subspace_looped(0,0);
    loops[0].set_subspace_looped(1,1);
    loops[1].set_subspace_looped(0,1);
    loops[1].set_subspace_looped(1,2);
    loops[2].set_subspace_looped(0,2);
    loops[2].set_subspace_looped(1,0);

    sparse_loop_list sll(loops);
    sll.run(bpk,ptrs);

    for(int i = 0; i < 35; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "block_loop<M,N,T>::run(...) produced incorrect output");
        }
    }
}

void sparse_loop_list_test::test_run_block_contract2_kernel_2d_2d() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_block_contract2_kernel_2d_2d()";

	//Indices in comments are block indices
    //dimensions: i = 4,k = 5,j = 6
    //Contraction takes the form of A * B^t
    double test_input_arr_1[20] = { //i = 0, k = 0
                                  1,2,
                                  6,7,

                                 //i = 0, k = 1
                                 3,4,5,
                                 8,9,10,

                                 //i = 1, k = 0
                                 11,12,
                                 16,17,

                                 //i = 1, k = 1
                                 13,14,15,
                                 18,19,20 };

    double test_input_arr_2[30] = { //j = 0, k = 0
                                    1,2,
                                    3,4,

                                    //j = 0, k = 1
                                    5,6,7,
                                    8,9,10,

                                    //j = 1, k = 0
                                    11,12,
                                    13,14,
                                    15,16,
                                    17,18,

                                    //j = 1, k = 1
                                    19,20,21,
                                    22,23,24,
                                    25,26,27,
                                    28,29,30};

    double test_output_arr[24] = {0};

    double correct_output_arr[24] = { //i = 0, j = 0
                                      79,121,
                                      184,291,

                                      //i = 0, j = 1
                                      277,319,361,403,
                                      692,799,906,1013,


									  //i = 1, j = 0
                                      289,461,
                                      394,631,

									  //i = 1, j = 1
                                      1107,1279,1451,1623,
                                      1522,1759,1996,2233};

    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr_1);
    ptrs.push_back(test_input_arr_2);

    //Bispace for i
    sparse_bispace<1> spb_i(4);
    vector<size_t> split_points_i;
    split_points_i.push_back(2);
    spb_i.split(split_points_i);

    //Bispace for j
    sparse_bispace<1> spb_j(6);
    vector<size_t> split_points_j;
    split_points_j.push_back(2);
    spb_j.split(split_points_j);

    //Bispace for k
    sparse_bispace<1> spb_k(5);
    vector<size_t> split_points_k;
    split_points_k.push_back(2);
    spb_k.split(split_points_k);

    vector< sparse_bispace_any_order > bispaces(1,spb_i | spb_j);
    bispaces.push_back(spb_i | spb_k);
    bispaces.push_back(spb_j | spb_k);

    vector<block_loop> loops(3,block_loop(bispaces));
    //i loop
    loops[0].set_subspace_looped(0,0);
    loops[0].set_subspace_looped(1,0);
    //j loop
    loops[1].set_subspace_looped(0,1);
    loops[1].set_subspace_looped(2,0);
    //k loop
    loops[2].set_subspace_looped(1,1);
    loops[2].set_subspace_looped(2,1);

    sparse_loop_list sll(loops);
    block_contract2_kernel<double> bc2k(sll);
    sll.run(bc2k,ptrs);

    for(int i = 0; i < 24; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "block_loop<M,N,T>::run(...) produced incorrect output");
        }
    }
}

void sparse_loop_list_test::test_run_block_contract2_kernel_3d_2d() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_block_contract2_kernel_3d_2d()";

	//Indices in comments are block indices
    //dimensions: i = 3,j = 4, k = 5,l = 6
    //Contraction takes the form of A*B
    double test_input_arr_1[60] = {//i = 0 j = 0 k = 0 (1,2,2)
                                   1,2,
                                   3,4,

                                   //i = 0 j = 0 k = 1 (1,2,3)
                                   5,6,7,
                                   8,9,10,

                                   //i = 0 j = 1 k = 0 (1,2,2)
                                   11,12,
                                   13,14,

                                   //i = 0 j = 1 k = 1 (1,2,3)
                                   15,16,17,
                                   18,19,20,

                                   //i = 1 j = 0 k = 0 (2,2,2)
                                   21,22,
                                   23,24,
                                   25,26,
                                   27,28,

                                   //i = 1 j = 0 k = 1 (2,2,3)
                                   29,30,31,
                                   32,33,34,
                                   35,36,37,
                                   38,39,40,

                                   //i = 1 j = 1 k = 0 (2,2,2)
                                   41,42,
                                   43,44,
                                   45,46,
                                   47,48,


                                   //i = 1 j = 1 k = 1 (2,2,3)
                                   49,50,51,
                                   52,53,54,
                                   55,56,57,
                                   58,59,60};


    double test_input_arr_2[30] = {//k = 0  l = 0
                                   1,2,3,
                                   4,5,6,

                                   //k = 0 l = 1
                                   7,8,9,
                                   10,11,12,

                                   //k = 1 l = 0
                                   13,14,15,
                                   16,17,18,
                                   19,20,21,

                                   //k = 1 l = 1
                                   22,23,24,
                                   25,26,27,
                                   28,29,30};

    double correct_output_arr[72] = {//i = 0 j = 0 l = 0
                                     303,324,345,
                                     457,491,525,

                                     //i = 0 j = 0 l = 1
                                     483,504,525,
                                     742,776,810,

                                     //i = 0 j = 1 l = 0
                                     833,904,975,
                                     987,1071,1155,

                                     //i = 0 j = 1 l = 1
                                     1403,1474,1545,
                                     1662,1746,1830,

                                     //i = 1 j = 0 l = 0
                                     1555,1688,1821,
                                     1709,1855,2001,
                                     1863,2022,2181,
                                     2017,2189,2361,

                                     //i = 1 j = 0 l = 1
                                     2623,2756,2889,
                                     2882,3028,3174,
                                     3141,3300,3459,
                                     3400,3572,3744,

                                     //i = 1 j = 1 l = 0
                                     2615,2848,3081,
                                     2769,3015,3261,
                                     2923,3182,3441,
                                     3077,3349,3621,

                                     //i = 1 j = 1 l = 1
                                     4463,4696,4929,
                                     4722,4968,5214,
                                     4981,5240,5499,
                                     5240,5512,5784};


    double test_output_arr[72] = {0};

    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr_1);
    ptrs.push_back(test_input_arr_2);

    //Bispace for i
    sparse_bispace<1> spb_i(3);
    vector<size_t> split_points_i;
    split_points_i.push_back(1);
    spb_i.split(split_points_i);

    //Bispace for j
    sparse_bispace<1> spb_j(4);
    vector<size_t> split_points_j;
    split_points_j.push_back(2);
    spb_j.split(split_points_j);

    //Bispace for k
    sparse_bispace<1> spb_k(5);
    vector<size_t> split_points_k;
    split_points_k.push_back(2);
    spb_k.split(split_points_k);

    //Bispace for l
    sparse_bispace<1> spb_l(6);
    vector<size_t> split_points_l;
    split_points_l.push_back(3);
    spb_l.split(split_points_l);

    vector< sparse_bispace_any_order > bispaces(1,spb_i|spb_j|spb_l);
    bispaces.push_back(spb_i|spb_j|spb_k);
    bispaces.push_back(spb_k|spb_l);

    vector<block_loop> loops(4,block_loop(bispaces));
    //i loop
    loops[0].set_subspace_looped(0,0);
    loops[0].set_subspace_looped(1,0);
    //j loop
    loops[1].set_subspace_looped(0,1);
    loops[1].set_subspace_looped(1,1);
    //l loop
    loops[2].set_subspace_looped(0,2);
    loops[2].set_subspace_looped(2,1);
    //k loop
    loops[3].set_subspace_looped(1,2);
    loops[3].set_subspace_looped(2,0);

    sparse_loop_list sll(loops);
    block_contract2_kernel<double> bc2k(sll);
    sll.run(bc2k,ptrs);

    for(int i = 0; i < 72; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "block_loop<M,N,T>::run(...) produced incorrect output");
        }
    }
}

#if 0
//Passing a bispace idx > # of bispaces in the loop list in fixed_blocks_map should throw exception
void sparse_loop_list_test::test_run_fixed_blocks_invalid_bispace_idx() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_fixed_blocks_invalid_bispace_idx()";

    //Only need dummy bispace data for this
    sparse_bispace<1> spb(5);
    vector<sparse_bispace_any_order> bispaces(2,spb|spb);
    sparse_loop_list sll(bispaces);
    for(size_t i = 0; i < 2; ++i)
    {
    	block_loop bl(bispaces);
    	bl.set_subspace_looped(i,0);
    	sll.add_loop(bl);
    }

    //Dummy pointer data
    vector<double*> ptrs(2,NULL);

    //token kernel - identity permutation
    runtime_permutation perm(2);
    block_permute_kernel<double> bpk(perm);

    //Fixed blocks data with invalid bispace index
    fixed_block_map fbm;
    fbm.insert(make_pair(3,vector<size_t>(2,0)));

    bool threw_exception = false;
    try
    {
    	sll.run(bpk,ptrs,fbm);
    }
    catch(out_of_bounds&)
    {
    	threw_exception = true;
    }

    if(!threw_exception)
    {
        fail_test(test_name,__FILE__,__LINE__,
                "sparse_loop_list::run(...) did not throw exception when invalid bispace index specified in fixed_blocks");
    }
}

//Passing wrong number of indices for fixed block of a given bispace should throw exception
void sparse_loop_list_test::test_run_fixed_blocks_not_enough_block_indices() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_fixed_blocks_not_enough_block_indices()";

    //Only need dummy bispace data for this
    sparse_bispace<1> spb(5);
    vector<sparse_bispace_any_order> bispaces(2,spb|spb);
    sparse_loop_list sll(bispaces);
    for(size_t i = 0; i < 2; ++i)
    {
    	block_loop bl(bispaces);
    	bl.set_subspace_looped(i,0);
    	sll.add_loop(bl);
    }

    //Dummy pointer data
    vector<double*> ptrs(2,NULL);

    //token kernel - identity permutation
    runtime_permutation perm(2);
    block_permute_kernel<double> bpk(perm);

    //Fixed blocks data with only one block index specified for a 2d bispace
    fixed_block_map fbm;
    fbm.insert(make_pair(1,vector<size_t>(1,0)));

    bool threw_exception = false;
    try
    {
    	sll.run(bpk,ptrs,fbm);
    }
    catch(bad_parameter&)
    {
    	threw_exception = true;
    }

    if(!threw_exception)
    {
        fail_test(test_name,__FILE__,__LINE__,
                "sparse_loop_list::run(...) did not throw exception when invalid block indices specified in fixed_blocks");
    }
}

//Should throw exception if we fix the blocks of two coupled bispaces to incompatible values
void sparse_loop_list_test::test_run_fixed_blocks_incompatible_indices() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_fixed_blocks_incompatible_indices()";

    //Just need dummy pointers for this test
    double test_input_arr[20] = { //i = 0, j = 0
                                  1,2,
                                  6,7,

                                 //i = 0, j = 1
                                 3,4,5,
                                 8,9,10,

                                 //i = 1, j = 0
                                 11,12,
                                 16,17,

                                 //i = 0, j = 1
                                 13,14,15,
                                 18,19,20 };

    //We only need an array of size 6 to hold our block
    double correct_output_arr[6] = { //j = 1, i = 0
									 3,8,
									 4,9,
									 5,10 };

    double test_output_arr[6];

    //First bispace (slow index) and splitting
    sparse_bispace<1> spb_1(4);
    vector<size_t> split_points_1;
    split_points_1.push_back(2);
    spb_1.split(split_points_1);

    //Second bispace (fast index) and splitting
    sparse_bispace<1> spb_2(5);
    vector<size_t> split_points_2;
    split_points_2.push_back(2);
    spb_2.split(split_points_2);

    vector< sparse_bispace_any_order > bispaces;
    bispaces.push_back(spb_2 | spb_1);
    bispaces.push_back(spb_1 | spb_2);

    runtime_permutation perm(2);
    perm.permute(0,1);
    block_permute_kernel<double> bpk(perm);


    //We stride the input, not the output
    block_loop bl_1(bispaces);
    bl_1.set_subspace_looped(0,0);
    bl_1.set_subspace_looped(1,1);
    block_loop bl_2(bispaces);
    bl_2.set_subspace_looped(0,1);
    bl_2.set_subspace_looped(1,0);

    sparse_loop_list sll(bispaces);
    sll.add_loop(bl_1);
    sll.add_loop(bl_2);

    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr);

    fixed_block_map fbm;
    vector<size_t> fixed_blocks_output(1,1);
    fixed_blocks_output.push_back(0);
    fbm.insert(make_pair(0,fixed_blocks_output));

    sll.run(bpk,ptrs,fbm);

    for(int i = 0; i < 6; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "sparse_loop_list::run(...) produced incorrect output");
        }
    }
}

//Form a single block of the output tensor by fixing the desired blocks for a subset of the loops
//We will form the block j = 1, i = 0
void sparse_loop_list_test::test_run_fixed_blocks_bpk_2d() throw(libtest::test_exception)
{
    static const char *test_name = "sparse_loop_list_test::test_run_fixed_blocks_bpk_2d()";

	//Indices in comments are block indices
    double test_input_arr[20] = { //i = 0, j = 0
                                  1,2,
                                  6,7,

                                 //i = 0, j = 1
                                 3,4,5,
                                 8,9,10,

                                 //i = 1, j = 0
                                 11,12,
                                 16,17,

                                 //i = 0, j = 1
                                 13,14,15,
                                 18,19,20 };

    //We only need an array of size 6 to hold our block
    double correct_output_arr[6] = { //j = 1, i = 0
									 3,8,
									 4,9,
									 5,10 };

    double test_output_arr[6];

    //First bispace (slow index) and splitting
    sparse_bispace<1> spb_1(4);
    vector<size_t> split_points_1;
    split_points_1.push_back(2);
    spb_1.split(split_points_1);

    //Second bispace (fast index) and splitting
    sparse_bispace<1> spb_2(5);
    vector<size_t> split_points_2;
    split_points_2.push_back(2);
    spb_2.split(split_points_2);

    vector< sparse_bispace_any_order > bispaces;
    bispaces.push_back(spb_2 | spb_1);
    bispaces.push_back(spb_1 | spb_2);

    runtime_permutation perm(2);
    perm.permute(0,1);
    block_permute_kernel<double> bpk(perm);


    //We stride the input, not the output
    block_loop bl_1(bispaces);
    bl_1.set_subspace_looped(0,0);
    bl_1.set_subspace_looped(1,1);
    block_loop bl_2(bispaces);
    bl_2.set_subspace_looped(0,1);
    bl_2.set_subspace_looped(1,0);

    sparse_loop_list sll(bispaces);
    sll.add_loop(bl_1);
    sll.add_loop(bl_2);

    vector<double*> ptrs(1,test_output_arr);
    ptrs.push_back(test_input_arr);

    fixed_block_map fbm;
    vector<size_t> fixed_blocks_output(1,1);
    fixed_blocks_output.push_back(0);
    fbm.insert(make_pair(0,fixed_blocks_output));

    sll.run(bpk,ptrs,fbm);

    for(int i = 0; i < 6; ++i)
    {
        if(test_output_arr[i] != correct_output_arr[i])
        {
            fail_test(test_name,__FILE__,__LINE__,
                    "sparse_loop_list::run(...) produced incorrect output");
        }
    }
}
#endif

} /* namespace libtensor */