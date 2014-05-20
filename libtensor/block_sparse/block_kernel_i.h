/*
 * block_kernel_i_new.h
 *
 *  Created on: Nov 13, 2013
 *      Author: smanzer
 */

#ifndef BLOCK_KERNEL_I_NEW_H_
#define BLOCK_KERNEL_I_NEW_H_

#include <vector>
#include "sparse_defs.h"
#include "../exception.h"

namespace libtensor {

template<typename T>
class block_kernel_i
{
public:
	virtual void operator()(const std::vector<T*>& ptrs, const std::vector< dim_list >& dim_lists) = 0;
	virtual ~block_kernel_i() {}
};
} // namespace libtensor


#endif /* BLOCK_KERNEL_I_NEW_H_ */
