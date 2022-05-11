#include <xanadu-cctl/allocator.h>



/// 复制一份数据，如果数据为空，则初始化为'\0'
_XCCTLAPI_ void* __xcall__ xtl_allocator_data_clone(const void* _Data, xtl_size_t _Size)
{
	void*		data = x_posix_malloc(_Size);
	if(data)
	{
		if(_Data == NULL)
		{
			x_posix_memset(data, 0, _Size);
		}
		else
		{
			x_posix_memcpy(data, _Data, _Size);
		}
	}
	return data;
}

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
