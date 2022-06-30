#include <xanadu-cctl/string.h>
#include <xanadu-cctl/allocator.h>



// string 数据
struct xtl_string_data
{
	xtl_container_type		type;

	char*				data;
	xtl_size_t			size;
	xtl_size_t 			capacity;
};



/// create a string
_XCCTLAPI_ xtl_string_t __xcall__ xtl_string_new(const char* _String)
{
	xtl_size_t	_Size = x_posix_strlen(_String);
	xtl_string_t	_Object = (xtl_string_t)x_posix_malloc(sizeof(struct xtl_string_data));
	if(_Object)
	{
		x_posix_memset(_Object, 0, sizeof(struct xtl_string_data));
		_Object->type = XTL_CONTAINER_STRING;
		_Object->size = _Size;
		_Object->capacity = xtl_allocator_calculation_capacity(_Size + 1);
		_Object->data = (char*)x_posix_malloc(_Object->capacity);
		if(_Object->data == NULL)
		{
			x_posix_free(_Object);
			_Object = NULL;
		}
		else
		{
			if(_String)
			{
				x_posix_strcpy(_Object->data, _String);
			}
			x_posix_memset(_Object->data + _Object->size, 0, _Object->capacity);
		}
	}
	return _Object;
}

/// free string object
_XCCTLAPI_ void __xcall__ xtl_string_free(xtl_string_t _Object)
{
	if (_Object)
	{
		x_posix_free(_Object->data);
		x_posix_free(_Object);
	}
}





/// container data
_XCCTLAPI_ char* __xcall__ xtl_string_data(xtl_string_t _Object)
{
	return _Object->data;
}

/// container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_string_size(xtl_string_t _Object)
{
	return _Object->size;
}

/// container capacity
_XCCTLAPI_ xtl_size_t __xcall__ xtl_string_capacity(xtl_string_t _Object)
{
	return _Object->capacity;
}





/// Check if container is empty
_XCCTLAPI_ bool __xcall__ xtl_string_empty(xtl_string_t _Object)
{
	return _Object->size == 0;
}

/// Check if an element exists in a container
_XCCTLAPI_ bool __xcall__ xtl_string_exist(xtl_string_t _Object)
{
	return _Object->size != 0;
}





/// Access the specified element by subscript
_XCCTLAPI_ void* __xcall__ xtl_string_at(xtl_string_t _Object, xtl_size_t _Pos)
{
	if(_Object->size <= _Pos)
	{
		return NULL;
	}
	return _Object->data + _Pos;
}





/// Empty all data in container
_XCCTLAPI_ bool __xcall__ xtl_string_clear(xtl_string_t _Object)
{
	x_posix_free(_Object->data);
	_Object->size = 0;
	_Object->capacity = xtl_allocator_calculation_capacity(_Object->size + 1);
	_Object->data = (char*)x_posix_malloc(_Object->capacity);
	if(_Object->data)
	{
		x_posix_memset(_Object->data, 0, _Object->capacity);
	}
	return _Object->data;
}

/// Resize the container
_XCCTLAPI_ bool __xcall__ xtl_string_resize(xtl_string_t _Object, xtl_size_t _Size)
{
	char*		new_data = NULL;
	xtl_size_t 	new_capacity = 0;

	if(_Object->size > _Size)
	{
		x_posix_memset(_Object->data + _Size, 0, _Object->size - _Size);
		_Object->size = _Size;
	}
	else if(_Object->size < _Size)
	{
		if(_Object->capacity <= _Size)
		{
			new_capacity = xtl_allocator_calculation_capacity(_Size + 1);
			new_data = (char*)x_posix_malloc(new_capacity);
			if(new_data == NULL)
			{
				return false;
			}
			x_posix_memcpy(new_data, _Object->data, _Object->size);
			x_posix_memset(new_data + _Object->size, 0, new_capacity - _Object->size);

			x_posix_free(_Object->data);
			_Object->capacity = new_capacity;
			_Object->data = new_data;
		}
		x_posix_memset(_Object->data + _Size, 0, _Object->size - _Size);
		_Object->size = _Size;
	}
	return true;
}





/// append an element to the end
_XCCTLAPI_ bool __xcall__ xtl_string_push_back(xtl_string_t _Object, char _Element)
{
	if(false == xtl_string_resize(_Object, _Object->size + 1))
	{
		return false;
	}

	_Object->data[_Object->size] = _Element;
	_Object->size += 1;
	return true;
}

/// Insert an element at the head
_XCCTLAPI_ bool __xcall__ xtl_string_push_front(xtl_string_t _Object, char _Element)
{
	if(false == xtl_string_resize(_Object, _Object->size + 1))
	{
		return false;
	}

	x_posix_memmove(_Object->data + 1, _Object->data, _Object->size);
	_Object->data[0] = _Element;
	_Object->size += 1;
	return true;
}

/// Inserts an element at the specified subscript
_XCCTLAPI_ bool __xcall__ xtl_string_insert(xtl_string_t _Object, xtl_size_t _Pos, const void* _Element)
{
	xtl_size_t 	vElemSize = x_posix_strlen(_Element);
	if(vElemSize == 0 || false == xtl_string_resize(_Object, _Object->size + vElemSize))
	{
		return false;
	}

	if(_Pos > _Object->size)
	{
		_Pos = _Object->size;
	}

	x_posix_memmove(_Object->data + (_Pos + vElemSize), _Object->data + _Pos, _Object->size - _Pos);
	x_posix_memcpy(_Object->data + _Pos, _Element, vElemSize);
	_Object->size += 1;
	return true;
}

/// Replaces the elements of the container with the specified number of elements
_XCCTLAPI_ bool __xcall__ xtl_string_assign(xtl_string_t _Object, xtl_size_t _Count, char _Element)
{
	if(false == xtl_string_clear(_Object) || false == xtl_string_resize(_Object, _Count))
	{
		return false;
	}

	for(xtl_size_t vIndex = 0; vIndex < _Count; ++vIndex)
	{
		_Object->data[vIndex] = _Element;
	}
	return true;
}





/// the element data pointed to by the iterator
_XCCTLAPI_ void* __xcall__ xtl_string_iter_data(xtl_string_t _Object, xtl_string_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	return _Iterator;
}

/// iterator to the beginning of the container
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_begin(xtl_string_t _Object)
{
	if(_Object->size == 0)
	{
		return XTL_ITERATOR_NULL;
	}
	return (xtl_string_iter_t)(_Object->data);
}

/// iterator to the end of the container
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_end(xtl_string_t _Object)
{
	XANADU_UNUSED(_Object);
	return XTL_ITERATOR_NULL;
}

/// the previous iterator of the current iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_iter_prev(xtl_string_t _Object, xtl_string_iter_t _Iterator)
{
	if(_Object->data > ((char*)_Iterator - 1))
	{
		return xtl_string_end(_Object);
	}
	return (xtl_string_iter_t)(((char*)_Iterator) - 1);
}

/// the next iterator of the current iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_iter_next(xtl_string_t _Object, xtl_string_iter_t _Iterator)
{
	if((_Object->data + _Object->size) > ((char*)_Iterator - 1))
	{
		return xtl_string_end(_Object);
	}
	return (xtl_string_iter_t)(((char*)_Iterator) + 1);
}





/// emoves the element specified by the iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_erase(xtl_string_t _Object, xtl_string_iter_t _Iterator)
{
	xtl_size_t 		full_size = _Object->size;
	char*			iter_data = (char*)_Iterator;

	if(iter_data < _Object->data || (_Object->data + full_size - 1) < iter_data)
	{
		return xtl_string_end(_Object);
	}

	if(iter_data == (_Object->data + full_size - 1))
	{
		x_posix_memset(iter_data, 0, 1);
		--_Object->size;
		return xtl_string_end(_Object);
	}
	else
	{
		x_posix_memcpy(iter_data, iter_data + 1, 1);
		--_Object->size;
		x_posix_memset(_Object->data + _Object->size, 0, 1);
		return (xtl_string_iter_t)iter_data;
	}
}
