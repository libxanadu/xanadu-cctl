#include <xanadu-cctl/allocator.h>



/// 根据输入参数计算容量
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_calculation_capacity(xtl_size_t _Size)
{
	xtl_size_t	capacity = XTL_DEFAULT_CAPACITY;
	while(capacity <= _Size)
	{
		capacity <<= 1;
	}
	return capacity;
}

/// 容器允许的最大长度
/// \return : 允许的最大长度
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_max_size()
{
	return (xtl_pos_t)-1;
}
