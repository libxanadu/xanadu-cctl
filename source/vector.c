#include <xanadu-cctl/vector.h>
#include <xanadu-cctl/allocator.h>



// vector 数据
struct xtl_vector_data
{
	xtl_container_type		type;

	char*				data;
	xtl_size_t			size;
	xtl_size_t 			capacity;
	xtl_size_t 			elem_size;
};



/// create a vector
_XCCTLAPI_ xtl_vector_t __xcall__ xtl_vector_new(size_t _ElemSize)
{
	if(_ElemSize == 0)
	{
		return NULL;
	}

	xtl_vector_t	_Object = (xtl_vector_t)x_posix_malloc(sizeof(struct xtl_vector_data));
	if(_Object)
	{
		x_posix_memset(_Object, 0, sizeof(struct xtl_vector_data));
		_Object->type = XTL_CONTAINER_VECTOR;
		_Object->size = 0;
		_Object->elem_size = _ElemSize;
		_Object->capacity = XTL_DEFAULT_CAPACITY;
		_Object->data = (char*)x_posix_malloc(_ElemSize * _Object->capacity);
		if(_Object->data == NULL)
		{
			x_posix_free(_Object);
			_Object = NULL;
		}
		else
		{
			x_posix_memset(_Object->data, 0, _ElemSize * _Object->capacity);
		}
	}
	return _Object;
}

/// free vector object
_XCCTLAPI_ void __xcall__ xtl_vector_free(xtl_vector_t _Object)
{
	if (_Object)
	{
		x_posix_free(_Object->data);
		x_posix_free(_Object);
	}
}





/// container data
_XCCTLAPI_ void* __xcall__ xtl_vector_data(xtl_vector_t _Object)
{
	return _Object->data;
}

/// container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_size(xtl_vector_t _Object)
{
	return _Object->size;
}

/// container capacity
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_capacity(xtl_vector_t _Object)
{
	return _Object->capacity;
}





/// Check if container is empty
_XCCTLAPI_ bool __xcall__ xtl_vector_empty(xtl_vector_t _Object)
{
	return _Object->size == 0;
}

/// Check if an element exists in a container
_XCCTLAPI_ bool __xcall__ xtl_vector_exist(xtl_vector_t _Object)
{
	return _Object->size != 0;
}





/// Access the specified element by subscript
_XCCTLAPI_ void* __xcall__ xtl_vector_at(xtl_vector_t _Object, xtl_size_t _Pos)
{
	if(_Object->size <= _Pos)
	{
		return NULL;
	}
	return _Object->data + (_Pos * _Object->elem_size);
}





/// Empty all data in container
_XCCTLAPI_ bool __xcall__ xtl_vector_clear(xtl_vector_t _Object)
{
	x_posix_free(_Object->data);
	_Object->size = 0;
	_Object->capacity = xtl_allocator_calculation_capacity(_Object->size);
	_Object->data = (char*)x_posix_malloc(_Object->elem_size * _Object->capacity);
	return _Object->data;
}

/// Resize the container
_XCCTLAPI_ bool __xcall__ xtl_vector_resize(xtl_vector_t _Object, xtl_size_t _Size)
{
	char*		new_data = NULL;
	xtl_size_t 	new_capacity = 0;

	if(_Object->size > _Size)
	{
		x_posix_memset(_Object->data + (_Size * _Object->elem_size), 0, _Object->size - _Size);
		_Object->size = _Size;
	}
	else if(_Object->size < _Size)
	{
		if(_Object->capacity <= _Size)
		{
			new_capacity = xtl_allocator_calculation_capacity(_Size);
			new_data = (char*)x_posix_malloc(new_capacity * _Object->elem_size);
			if(new_data == NULL)
			{
				return false;
			}
			x_posix_memcpy(new_data, _Object->data, _Object->size * _Object->elem_size);
			x_posix_memset(new_data + (_Object->size * _Object->elem_size), 0, (new_capacity - _Object->size) * _Object->elem_size);

			x_posix_free(_Object->data);
			_Object->capacity = new_capacity;
			_Object->data = new_data;
		}
		x_posix_memset(_Object->data + (_Size * _Object->elem_size), 0, _Object->size - _Size);
		_Object->size = _Size;
	}
	return true;
}





/// append an element to the end
_XCCTLAPI_ bool __xcall__ xtl_vector_push_back(xtl_vector_t _Object, const void* _Element)
{
	if(_Element == NULL || false == xtl_vector_resize(_Object, _Object->size + 1))
	{
		return false;
	}

	x_posix_memcpy(_Object->data + (_Object->size * _Object->elem_size), _Element, _Object->elem_size);
	_Object->size += 1;
	return true;
}

/// Insert an element at the head
_XCCTLAPI_ bool __xcall__ xtl_vector_push_front(xtl_vector_t _Object, const void* _Element)
{
	if(_Element == NULL || false == xtl_vector_resize(_Object, _Object->size + 1))
	{
		return false;
	}

	x_posix_memmove(_Object->data + _Object->elem_size, _Object->data, _Object->size * _Object->elem_size);
	x_posix_memcpy(_Object->data, _Element, _Object->elem_size);
	_Object->size += 1;
	return true;
}

/// Inserts an element at the specified subscript
_XCCTLAPI_ bool __xcall__ xtl_vector_insert(xtl_vector_t _Object, xtl_size_t _Pos, const void* _Element)
{
	if(_Element == NULL || false == xtl_vector_resize(_Object, _Object->size + 1))
	{
		return false;
	}

	if(_Pos > _Object->size)
	{
		_Pos = _Object->size;
	}

	x_posix_memmove(_Object->data + ((_Pos + 1) * _Object->elem_size), _Object->data + (_Pos * _Object->elem_size), (_Object->size - _Pos) * _Object->elem_size);
	x_posix_memcpy(_Object->data + (_Pos * _Object->elem_size), _Element, _Object->elem_size);
	_Object->size += 1;
	return true;
}

/// Replaces the elements of the container with the specified number of elements
_XCCTLAPI_ bool __xcall__ xtl_vector_assign(xtl_vector_t _Object, xtl_size_t _Count, const void* _Element)
{
	if(_Element == NULL)
	{
		return false;
	}

	xtl_vector_clear(_Object);
	if(false == xtl_vector_clear(_Object) || false == xtl_vector_resize(_Object, _Count))
	{
		return false;
	}

	for(xtl_size_t vIndex = 0; vIndex < _Count; ++vIndex)
	{
		x_posix_memcpy(_Object->data + (vIndex * _Object->elem_size), _Element, _Object->elem_size);
	}
	return true;
}





/// the element data pointed to by the iterator
_XCCTLAPI_ void* __xcall__ xtl_vector_iter_data(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	return _Iterator;
}

/// iterator to the beginning of the container
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_begin(xtl_vector_t _Object)
{
	if(_Object->size == 0)
	{
		return XTL_ITERATOR_NULL;
	}
	return (xtl_vector_iter_t)(_Object->data);
}

/// iterator to the end of the container
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_end(xtl_vector_t _Object)
{
	XANADU_UNUSED(_Object);
	return XTL_ITERATOR_NULL;
}

/// the previous iterator of the current iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_prev(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	if(_Object->data > ((char*)_Iterator - _Object->elem_size))
	{
		return xtl_vector_end(_Object);
	}
	return (xtl_vector_iter_t)(((char*)_Iterator) - _Object->elem_size);
}

/// the next iterator of the current iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_next(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	if((_Object->data + (_Object->size * _Object->elem_size)) > ((char*)_Iterator - _Object->elem_size))
	{
		return xtl_vector_end(_Object);
	}
	return (xtl_vector_iter_t)(((char*)_Iterator) + _Object->elem_size);
}





/// emoves the element specified by the iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_erase(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	xtl_size_t 		full_size = _Object->size * _Object->elem_size;
	char*			iter_data = (char*)_Iterator;

	if(iter_data > (_Object->data + full_size - _Object->elem_size))
	{
		x_posix_memset(iter_data, 0, _Object->elem_size);
		--_Object->size;
		return xtl_vector_end(_Object);
	}
	else
	{
		x_posix_memcpy(iter_data, iter_data + _Object->elem_size, _Object->elem_size);
		--_Object->size;
		x_posix_memset(_Object->data + (_Object->size * _Object->elem_size), 0, _Object->elem_size);
		return (xtl_vector_iter_t)iter_data;
	}
}
