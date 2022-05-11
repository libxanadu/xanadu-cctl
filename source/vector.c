#include <xanadu-cctl/vector.h>
#include <xanadu-cctl/allocator.h>



// vector 数据
struct xtl_vector_data
{
	char*				data;
	xtl_size_t			size;
	xtl_size_t 			capacity;
	xtl_size_t 			element_size;
};



/// 创建一个vector
_XCCTLAPI_ xtl_vector_t __xcall__ xtl_vector_new(size_t _ElementSize)
{
	if(_ElementSize == 0)
	{
		return NULL;
	}

	xtl_vector_t	_Object = (xtl_vector_t)x_posix_malloc(sizeof(struct xtl_vector_data));
	if(_Object)
	{
		x_posix_memset(_Object, 0, sizeof(struct xtl_vector_data));
		_Object->element_size = _ElementSize;
		_Object->capacity = XTL_DEFAULT_CAPACITY;
		_Object->data = (char*)x_posix_malloc(_ElementSize * _Object->capacity);
		if(_Object->data == NULL)
		{
			x_posix_free(_Object);
			_Object = NULL;
		}
		else
		{
			x_posix_memset(_Object->data, 0, _ElementSize * _Object->capacity);
		}
	}
	return _Object;
}

/// 释放一个vector
_XCCTLAPI_ void __xcall__ xtl_vector_free(xtl_vector_t _Object)
{
	if (_Object)
	{
		x_posix_free(_Object->data);
		x_posix_free(_Object);
	}
}





/// 获取容器的具体数据指针
_XCCTLAPI_ void* __xcall__ xtl_vector_data(xtl_vector_t _Object)
{
	return _Object->data;
}

/// 获取容器的大小
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_size(xtl_vector_t _Object)
{
	return _Object->size;
}

/// 获取容器的容量
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_capacity(xtl_vector_t _Object)
{
	return _Object->capacity;
}





/// 容器是否为空
_XCCTLAPI_ bool __xcall__ xtl_vector_empty(xtl_vector_t _Object)
{
	return _Object->size == 0;
}

/// 容器是否存在元素
_XCCTLAPI_ bool __xcall__ xtl_vector_exist(xtl_vector_t _Object)
{
	return _Object->size != 0;
}





/// 根据下标访问指定的元素
_XCCTLAPI_ void* __xcall__ xtl_vector_at(xtl_vector_t _Object, xtl_size_t _Pos)
{
	if(_Object->size <= _Pos)
	{
		return NULL;
	}
	return _Object->data + (_Pos * _Object->element_size);
}





/// 清空容器
_XCCTLAPI_ bool __xcall__ xtl_vector_clear(xtl_vector_t _Object)
{
	x_posix_free(_Object->data);
	_Object->size = 0;
	_Object->capacity = xtl_allocator_calculation_capacity(_Object->size);
	_Object->data = (char*)x_posix_malloc(_Object->element_size * _Object->capacity);
	return _Object->data;
}

/// 构建空间
_XCCTLAPI_ bool __xcall__ xtl_vector_resize(xtl_vector_t _Object, xtl_size_t _Size)
{
	char*		new_data = NULL;
	xtl_size_t 	new_capacity = 0;

	if(_Object->size > _Size)
	{
		x_posix_memset(_Object->data + (_Size * _Object->element_size), 0, _Object->size - _Size);
		_Object->size = _Size;
	}
	else if(_Object->size < _Size)
	{
		if(_Object->capacity <= _Size)
		{
			new_capacity = xtl_allocator_calculation_capacity(_Size);
			new_data = (char*)x_posix_malloc(new_capacity * _Object->element_size);
			if(new_data == NULL)
			{
				return false;
			}
			x_posix_memcpy(new_data, _Object->data, _Object->size * _Object->element_size);
			x_posix_memset(new_data + (_Object->size * _Object->element_size), 0, (new_capacity - _Object->size) * _Object->element_size);

			x_posix_free(_Object->data);
			_Object->capacity = new_capacity;
			_Object->data = new_data;
		}
		x_posix_memset(_Object->data + (_Size * _Object->element_size), 0, _Object->size - _Size);
		_Object->size = _Size;
	}
	return true;
}





/// 在尾部追加一个元素
_XCCTLAPI_ bool __xcall__ xtl_vector_push_back(xtl_vector_t _Object, const void* _Element)
{
	if(_Element == NULL || false == xtl_vector_resize(_Object, _Object->size + 1))
	{
		return false;
	}

	x_posix_memcpy(_Object->data + (_Object->size * _Object->element_size), _Element, _Object->element_size);
	_Object->size += 1;
	return true;
}

/// 在头部插入一个元素
_XCCTLAPI_ bool __xcall__ xtl_vector_push_front(xtl_vector_t _Object, const void* _Element)
{
	if(_Element == NULL || false == xtl_vector_resize(_Object, _Object->size + 1))
	{
		return false;
	}

	x_posix_memmove(_Object->data + _Object->element_size, _Object->data, _Object->size * _Object->element_size);
	x_posix_memcpy(_Object->data, _Element, _Object->element_size);
	_Object->size += 1;
	return true;
}

/// 在指定下标处插入一个元素
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

	x_posix_memmove(_Object->data + ((_Pos + 1) * _Object->element_size), _Object->data + (_Pos * _Object->element_size), (_Object->size - _Pos) * _Object->element_size);
	x_posix_memcpy(_Object->data + (_Pos * _Object->element_size), _Element, _Object->element_size);
	_Object->size += 1;
	return true;
}

/// 将容器的元素替换为指定数量的元素
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
		x_posix_memcpy(_Object->data + (vIndex * _Object->element_size), _Element, _Object->element_size);
	}
	return true;
}





/// 获取迭代器的数据
_XCCTLAPI_ void* __xcall__ xtl_vector_iter_data(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	return _Iterator;
}

/// 获取指向开头的迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_begin(xtl_vector_t _Object)
{
	if(_Object->size == 0)
	{
		return XTL_ITERATOR_NULL;
	}
	return (xtl_vector_iter_t)(_Object->data);
}

/// 获取指向末尾的迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_end(xtl_vector_t _Object)
{
	XANADU_UNUSED(_Object);
	return XTL_ITERATOR_NULL;
}

/// 当前迭代器的上一个迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_prev(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	if(_Object->data > ((char*)_Iterator - _Object->element_size))
	{
		return xtl_vector_end(_Object);
	}
	return (xtl_vector_iter_t)(((char*)_Iterator) - _Object->element_size);
}

/// 当前迭代器的下一个迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_next(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	if((_Object->data + (_Object->size * _Object->element_size)) > ((char*)_Iterator - _Object->element_size))
	{
		return xtl_vector_end(_Object);
	}
	return (xtl_vector_iter_t)(((char*)_Iterator) + _Object->element_size);
}





/// 移除迭代器指定的元素
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_erase(xtl_vector_t _Object, xtl_vector_iter_t _Iterator)
{
	xtl_size_t 		full_size = _Object->size * _Object->element_size;
	char*			iter_data = (char*)_Iterator;

	if(iter_data > (_Object->data + full_size - _Object->element_size))
	{
		x_posix_memset(iter_data, 0, _Object->element_size);
		--_Object->size;
		return xtl_vector_end(_Object);
	}
	else
	{
		x_posix_memcpy(iter_data, iter_data + _Object->element_size, _Object->element_size);
		--_Object->size;
		x_posix_memset(_Object->data + (_Object->size * _Object->element_size), 0, _Object->element_size);
		return (xtl_vector_iter_t)iter_data;
	}
}
