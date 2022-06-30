#ifndef			_XANADU_CCTL_ALLOCATOR_H_
#define			_XANADU_CCTL_ALLOCATOR_H_

#include <xanadu-cctl/header.h>

XANADU_CXX_EXTERN_BEGIN


/// 容器类型
typedef enum xtl_container_type
{
	XTL_CONTAINER_ARRAY			= 0,
	XTL_CONTAINER_DEQUE			= 1,
	XTL_CONTAINER_LIST			= 2,
	XTL_CONTAINER_MAP			= 3,
	XTL_CONTAINER_QUEUE			= 4,
	XTL_CONTAINER_SET			= 5,
	XTL_CONTAINER_STACK			= 6,
	XTL_CONTAINER_VECTOR			= 7,
	XTL_CONTAINER_STRING			= 8,
	XTL_CONTAINER_UNKNOWN			= 9
}xtl_container_type;


// Allocator handle
struct xtl_allocator_data;
typedef struct xtl_allocator_data*		xtl_allocator_t;



/// Copy a copy of the data, if the data is empty, it is initialized to 0
/// \param _Data : data pointer
/// \param _Size : Data length
/// \return : copied data
_XCCTLAPI_ void* __xcall__ xtl_allocator_data_clone(const void* _Data, xtl_size_t _Size);

/// Calculate the required container capacity based on size
/// \param _Size : the size you want to allocate
/// \return : Calculated capacity
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_calculation_capacity(xtl_size_t _Size);

/// The maximum length allowed by the container
/// \return : maximum length
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_max_size();



XANADU_CXX_EXTERN_END

#endif
