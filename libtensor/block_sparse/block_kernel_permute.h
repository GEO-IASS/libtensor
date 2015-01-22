/*
 * block_kernel_permute.h
 *
 *  Created on: Nov 13, 2013
 *      Author: smanzer
 */
#ifndef BLOCK_KERNEL_PERMUTE_H
#define BLOCK_KERNEL_PERMUTE_H


#include <numeric>
#include "runtime_permutation.h"
#include "block_kernel_i.h"

namespace libtensor
{

template<typename T>
class block_kernel_permute: public libtensor::block_kernel_i<block_kernel_permute<T>,T>
{
private:
    runtime_permutation m_perm;
    static const char *k_clazz; //!< Class name

public:
	block_kernel_permute(const runtime_permutation& perm) : m_perm(perm) {}
	void operator()(const std::vector<T*>& ptrs, const std::vector< dim_list >& dim_lists);

    //Recurse internal permutation handler
    //Also used by contract2 kernel to circumvent expensive vector arguments of primary operator
    void permute(T* output_ptr,
    		const T* input_ptr,
    		const dim_list& output_dims,
    		const dim_list& input_dims,
    		size_t output_offset = 0,size_t input_offset = 0,size_t level = 0);
};

template<typename T>
const char* block_kernel_permute<T>::k_clazz = "block_kernel_permute<T>";

} /* namespace libtensor */

template<typename T>
void libtensor::block_kernel_permute<T>::permute(T* output_ptr,
		const T* input_ptr, const dim_list& output_dims,
		const dim_list& input_dims, size_t output_offset, size_t input_offset,
		size_t level)
{
    //Is this index permuted?
    size_t input_level = m_perm[level];

    //Determine the increment of the input array
    size_t input_incr = 1;
    if(input_level != (output_dims.size() - 1))
    {
        input_incr = std::accumulate(&input_dims[1]+input_level,&input_dims[0]+input_dims.size(),1,std::multiplies<size_t>());
    }

    if(level == (output_dims.size() - 1))
    {
        for(size_t i = 0; i < output_dims.back(); ++i)
        {
            output_ptr[output_offset + i] = input_ptr[input_offset + i*input_incr];
        }
    }
    else
    {
        size_t output_incr = std::accumulate(&output_dims[1]+level,&output_dims[0]+output_dims.size(),1,std::multiplies<size_t>());
        for(size_t i = 0; i < output_dims[level]; ++i)
        {
            permute(output_ptr,input_ptr,output_dims,input_dims,output_offset,input_offset,level+1);

            output_offset += output_incr;
            input_offset += input_incr;

        }
    }
}

template<typename T>
void libtensor::block_kernel_permute<T>::operator()(
		const std::vector<T*>& ptrs, const std::vector<dim_list>& dim_lists)
{
#ifdef LIBTENSOR_DEBUG 
	//One input one output?
	if(ptrs.size() != dim_lists.size() || ptrs.size() != 2)
	{
		throw bad_parameter(g_ns, k_clazz,"operator(...)",
				__FILE__, __LINE__, "must pass two pointers and two dim_lists");
	}

	//Output and input same dimension?
	if(dim_lists[0].size() != dim_lists[1].size())
	{
		throw bad_parameter(g_ns, k_clazz,"operator(...)",
				__FILE__, __LINE__, "output and input blocks do not have the same dimensionality");
	}

    //We generate the correct output dims based on our permutation
    dim_list real_output_dims(dim_lists[1].size());
    for(size_t i = 0; i < dim_lists[1].size(); ++i)
    {
        real_output_dims[i] = dim_lists[1][m_perm[i]];
    }

    //Did the user request rational output dimensions?
    for(size_t i = 0; i < dim_lists[0].size(); ++i)
    {
    	if(real_output_dims[i] != dim_lists[0][i])
    	{
			throw bad_parameter(g_ns, k_clazz,"operator(...)",
					__FILE__, __LINE__, "invalid output dimensions requested");
    	}
    }
#endif

    permute(ptrs[0],ptrs[1],dim_lists[0],dim_lists[1]);
}

#endif /* BLOCK_KERNEL_PERMUTE_H */
