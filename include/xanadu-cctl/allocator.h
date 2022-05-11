#ifndef			_XANADU_CCTL_ALLOCATOR_H_
#define			_XANADU_CCTL_ALLOCATOR_H_

#include <xanadu-cctl/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// Allocator 句柄
struct xtl_allocator_data;
typedef struct xtl_allocator_data*		xtl_allocator_t;



/// 根据输入参数计算容量
/// \param _Size : 想要分配的大小
/// \return : 计算后的容量
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_calculation_capacity(xtl_size_t _Size);

/// 容器允许的最大长度
/// \return : 允许的最大长度
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_max_size();



#if defined(__cplusplus)
}
#endif


#endif
