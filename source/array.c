#include <xanadu-cctl/array.h>
#include <xanadu-cctl/allocator.h>
#include <xanadu-cctl/algorithm.h>



// array 数据
struct xtl_array_data
{
	xtl_container_type		type;

	char*				data;
	xtl_size_t			size;
	xtl_size_t 			elem_size;
};



/// create a array
_XCCTLAPI_ xtl_array_t __xcall__ xtl_array_new(xtl_size_t _ElemNumber, size_t _ElemSize)
{
	if(_ElemSize == 0)
	{
		return NULL;
	}

	xtl_array_t	_Object = (xtl_array_t)x_posix_malloc(sizeof(struct xtl_array_data));
	if(_Object)
	{
		x_posix_memset(_Object, 0, sizeof(struct xtl_array_data));
		_Object->type = XTL_CONTAINER_ARRAY;
		_Object->size = _ElemNumber;
		_Object->elem_size = _ElemSize;
		_Object->data = (char*)x_posix_malloc((_ElemNumber + 1) * _ElemSize);
		if(_Object->data == NULL)
		{
			x_posix_free(_Object);
			_Object = NULL;
		}
		else
		{
			x_posix_memset(_Object->data, 0, (_ElemNumber + 1) * _ElemSize);
		}
	}
	return _Object;
}

/// free array object
_XCCTLAPI_ void __xcall__ xtl_array_free(xtl_array_t _Object)
{
	if (_Object)
	{
		x_posix_free(_Object->data);
		x_posix_free(_Object);
	}
}





/// container data
_XCCTLAPI_ void* __xcall__ xtl_array_data(xtl_array_t _Object)
{
	return _Object->data;
}

/// container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_array_size(xtl_array_t _Object)
{
	return _Object->size;
}





/// Check if container is empty
_XCCTLAPI_ bool __xcall__ xtl_array_empty(xtl_array_t _Object)
{
	return _Object->size == 0;
}

/// Check if an element exists in a container
_XCCTLAPI_ bool __xcall__ xtl_array_exist(xtl_array_t _Object)
{
	return _Object->size != 0;
}





/// Access the specified element by subscript
_XCCTLAPI_ void* __xcall__ xtl_array_at(xtl_array_t _Object, xtl_size_t _Pos)
{
	return xtl_array_opt_key(_Object, _Pos);
}

/// Returns a reference to the element at specified location pos.
_XCCTLAPI_ void* __xcall__ xtl_array_opt_key(xtl_array_t _Object, xtl_size_t _Pos)
{
	return _Object->data + (_Pos * _Object->elem_size);
}

/// Returns a reference to the first element in the container.
_XCCTLAPI_ void* __xcall__ xtl_array_font(xtl_array_t _Object)
{
	return _Object->data;
}

/// Returns a reference to the last element in the container.
_XCCTLAPI_ void* __xcall__ xtl_array_back(xtl_array_t _Object)
{
	return _Object->data + ((_Object->size - 1) * _Object->elem_size);
}





/// Assigns the given value value to all elements in the container.
_XCCTLAPI_ void __xcall__ xtl_array_fill(xtl_array_t _Object, const void* _Element)
{
	xtl_size_t	vMaxSize = _Object->size * _Object->elem_size;
	xtl_size_t	vIndex = 0;

	if(_Element)
	{
		for(vIndex = 0; vIndex < vMaxSize; vIndex += _Object->elem_size)
		{
			x_posix_memcpy(_Object->data + vIndex, _Element, _Object->elem_size);
		}
	}
	else
	{
		for(vIndex = 0; vIndex < vMaxSize; vIndex += _Object->elem_size)
		{
			x_posix_memset(_Object->data + vIndex, 0, _Object->elem_size);
		}
	}
}

// Swap the contents of a container with the contents of other containers.
_XCCTLAPI_ void __xcall__ xtl_array_swap(xtl_array_t _Object, xtl_array_t _Other)
{
	xtl_algorithm_swap(_Object, _Other, sizeof(struct xtl_array_data));
}





/// the element data pointed to by the iterator
_XCCTLAPI_ void* __xcall__ xtl_array_iter_data(xtl_array_t _Object, xtl_array_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	return _Iterator;
}

/// iterator to the beginning of the container
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_begin(xtl_array_t _Object)
{
	if(_Object->size == 0)
	{
		return XTL_ITERATOR_NULL;
	}
	return (xtl_array_iter_t)(_Object->data);
}

/// iterator to the end of the container
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_end(xtl_array_t _Object)
{
	XANADU_UNUSED(_Object);
	return XTL_ITERATOR_NULL;
}

/// the previous iterator of the current iterator
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_iter_prev(xtl_array_t _Object, xtl_array_iter_t _Iterator)
{
	if(_Object->data > ((char*)_Iterator - _Object->elem_size))
	{
		return xtl_array_end(_Object);
	}
	return (xtl_array_iter_t)(((char*)_Iterator) - _Object->elem_size);
}

/// the next iterator of the current iterator
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_iter_next(xtl_array_t _Object, xtl_array_iter_t _Iterator)
{
	if((_Object->data + (_Object->size * _Object->elem_size)) > ((char*)_Iterator - _Object->elem_size))
	{
		return xtl_array_end(_Object);
	}
	return (xtl_array_iter_t)(((char*)_Iterator) + _Object->elem_size);
}
