#include <xanadu-cctl/allocator.h>



/// Copy a copy of the data, if the data is empty, it is initialized to 0
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

/// Calculate the required container capacity based on size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_calculation_capacity(xtl_size_t _Size)
{
	xtl_size_t	capacity = XTL_DEFAULT_CAPACITY;
	while(capacity <= _Size)
	{
		capacity <<= 1;
	}
	return capacity;
}

/// The maximum length allowed by the container
/// \return : maximum length
_XCCTLAPI_ xtl_size_t __xcall__ xtl_allocator_max_size()
{
	return (xtl_pos_t)-1;
}
