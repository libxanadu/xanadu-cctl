#include <xanadu-cctl/list.h>
#include <xanadu-cctl/allocator.h>



// list 元素
typedef struct xtl_list_node
{
	struct xtl_list_node*		prev;
	struct xtl_list_node*		next;

	void*				data;
}xtl_list_node;

// list 类型
struct xtl_list_data
{
	xtl_container_type		type;

	xtl_list_node*			root;
	xtl_size_t			size;
	xtl_size_t 			elem_size;
};





// 创建一个元素
static xtl_list_node* xtl_list_node_emplace(void* _Element)
{
	xtl_list_node*		node = (xtl_list_node*) x_posix_malloc(sizeof(xtl_list_node));
	if(node)
	{
		x_posix_memset(node, 0, sizeof(xtl_list_node));
		node->data = _Element;
	}
	return node;
}

// 创建一个元素
static xtl_list_node* xtl_list_node_new(const void* _Element, xtl_size_t _Size)
{
	xtl_list_node*		node = NULL;
	void*			data = xtl_allocator_data_clone(_Element, _Size);
	if(data == NULL)
	{
		return NULL;
	}

	node = xtl_list_node_emplace(data);
	if(node == NULL)
	{
		x_posix_free(data);
	}
	return node;
}

// 定位指定下标的元素
static xtl_list_node* xtl_list_node_at(xtl_list_t _Object, xtl_pos_t _Pos)
{
	xtl_size_t		vIndex = 0;
	xtl_list_node*		node = _Object->root->next;

	// 定位下标至指定长度
	for(; vIndex < _Pos && node; ++vIndex)
	{
		node = node->next;
	}
	return node;
}




/// create a list
_XCCTLAPI_ xtl_list_t __xcall__ xtl_list_new(xtl_size_t _ElemSize)
{
	xtl_list_t	_Object = (xtl_list_t) x_posix_malloc(sizeof(struct xtl_list_data));
	if(_Object)
	{
		x_posix_memset(_Object, 0, sizeof(struct xtl_list_data));
		_Object->type = XTL_CONTAINER_LIST;
		_Object->size = 0;
		_Object->elem_size = _ElemSize;
		_Object->root = (xtl_list_node*) x_posix_malloc(sizeof(xtl_list_node));
		if(_Object->root == NULL)
		{
			x_posix_free(_Object);
			_Object = NULL;
		}
		else
		{
			x_posix_memset(_Object->root, 0, sizeof(struct xtl_list_node));
		}
	}
	return _Object;
}

/// free list object
_XCCTLAPI_ void __xcall__ xtl_list_free(xtl_list_t _Object)
{
	xtl_list_clear(_Object);
	if(_Object->root)
	{
		x_posix_free(_Object->root);
		_Object->root = NULL;
	}
	x_posix_free(_Object);
}





/// container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_list_size(xtl_list_t _Object)
{
	return _Object->size;
}

/// the maximum size of the container
_XCCTLAPI_ xtl_size_t __xcall__ xtl_list_max_size(xtl_list_t _Object)
{
	XANADU_UNUSED(_Object);
	return xtl_allocator_max_size();
}





/// Check if container is empty
_XCCTLAPI_ bool __xcall__ xtl_list_empty(xtl_list_t _Object)
{
	return _Object->size == 0;
}

/// Check if an element exists in a container
_XCCTLAPI_ bool __xcall__ xtl_list_exist(xtl_list_t _Object)
{
	return _Object->size != 0;
}





/// Empty all data in container
_XCCTLAPI_ bool __xcall__ xtl_list_clear(xtl_list_t _Object)
{
	return xtl_list_resize(_Object, 0);
}

/// Resize the container
_XCCTLAPI_ bool __xcall__ xtl_list_resize(xtl_list_t _Object, xtl_size_t _Size)
{
	xtl_size_t		vIndex = 0;
	xtl_list_node*		node = NULL;
	xtl_list_node*		new_node = NULL;

	if(_Object->size > _Size)
	{
		// 定位下标至指定长度
		node = xtl_list_node_at(_Object, _Size);

		// 移除上一个节点的后节点链接
		node->prev->next = NULL;

		// 循环删除此节点及后续节点
		while(node)
		{
			x_posix_free(node->data);
			if(node->next)
			{
				node = node->next;
				x_posix_free(node->prev);
			}
			else
			{
				x_posix_free(node);
				node = NULL;
			}
		}

		_Object->size = _Size;
	}
	else if(_Object->size < _Size)
	{
		// 定位至末尾节点
		node = xtl_list_node_at(_Object, _Object->size);

		// 循环添加节点
		for(; vIndex < _Size; ++vIndex)
		{
			// 如果没有成功申请内存，则返回false
			new_node = xtl_list_node_new(NULL, _Object->elem_size);
			if(new_node == NULL)
			{
				return false;
			}

			if(node)
			{
				node->next = new_node;
				new_node->prev = node;
			}
			else
			{
				// 如果末尾节点为空，则表示没有节点
				_Object->root->next = new_node;
				new_node->prev = _Object->root;
				node = new_node;
			}
			++(_Object->size);
		}
	}
	return true;
}





/// append an element to the end
_XCCTLAPI_ bool __xcall__ xtl_list_push_back(xtl_list_t _Object, const void* _Element)
{
	return xtl_list_emplace_back(_Object, xtl_allocator_data_clone(_Element, _Object->elem_size));
}

/// Insert an element at the head
_XCCTLAPI_ bool __xcall__ xtl_list_push_front(xtl_list_t _Object, const void* _Element)
{
	return xtl_list_emplace_front(_Object, xtl_allocator_data_clone(_Element, _Object->elem_size));
}





/// append an element to the end
_XCCTLAPI_ bool __xcall__ xtl_list_emplace_back(xtl_list_t _Object, void* _Element)
{
	xtl_list_node*		node = NULL;
	xtl_list_node*		new_node = NULL;

	// 构建一个节点
	new_node = xtl_list_node_emplace(_Element);
	if(new_node == NULL)
	{
		return false;
	}

	// 定位至末尾节点
	node = xtl_list_node_at(_Object, _Object->size);
	if(node)
	{
		node->next = new_node;
		new_node->prev = node;
	}
	else
	{
		// 如果末尾节点为空，则表示没有节点
		_Object->root->next = new_node;
		new_node->prev = _Object->root;
	}

	++(_Object->size);

	return true;
}

/// Insert an element at the head
_XCCTLAPI_ bool __xcall__ xtl_list_emplace_front(xtl_list_t _Object, void* _Element)
{
	xtl_list_node*		new_node = NULL;

	// 构建一个节点
	new_node = xtl_list_node_emplace(_Element);
	if(new_node == NULL)
	{
		return false;
	}

	// 增加至list
	new_node->next = _Object->root->next;
	new_node->prev = _Object->root;
	if(_Object->root->next)
	{
		_Object->root->next->prev = new_node;
	}
	_Object->root->next = new_node;

	++(_Object->size);

	return true;
}





/// the element data pointed to by the iterator
_XCCTLAPI_ void* __xcall__ xtl_list_iter_data(xtl_list_t _Object, xtl_list_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	xtl_list_node*		node = (xtl_list_node*)_Iterator;

	if(_Iterator == NULL)
	{
		return NULL;
	}

	return node->data;
}

/// iterator to the beginning of the container
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_begin(xtl_list_t _Object)
{
	if(_Object->size == 0)
	{
		return XTL_ITERATOR_NULL;
	}
	return (xtl_list_iter_t)(_Object->root->next);
}

/// iterator to the end of the container
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_end(xtl_list_t _Object)
{
	XANADU_UNUSED(_Object);
	return XTL_ITERATOR_NULL;
}

/// the previous iterator of the current iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_iter_prev(xtl_list_t _Object, xtl_list_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	xtl_list_node*		node = (xtl_list_node*)_Iterator;
	if(node)
	{
		return (xtl_list_iter_t)(node->prev);
	}
	return XTL_ITERATOR_NULL;
}

/// the next iterator of the current iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_iter_next(xtl_list_t _Object, xtl_list_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	xtl_list_node*		node = (xtl_list_node*)_Iterator;
	if(node)
	{
		return (xtl_list_iter_t)(node->next);
	}
	return XTL_ITERATOR_NULL;
}





/// emoves the element specified by the iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_erase(xtl_list_t _Object, xtl_list_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	xtl_list_iter_t		new_iter = XTL_ITERATOR_NULL;
	xtl_list_node*		node = (xtl_list_node*)_Iterator;
	if(node)
	{
		node->prev->next = node->next;
		if(node->next)
		{
			node->next->prev = node->prev;
			new_iter = (xtl_list_iter_t)node->next;
		}
		x_posix_free(node->data);
		x_posix_free(node);
		--_Object->size;
	}
	return new_iter;
}
