#include <xanadu-cctl/stack.h>
#include <xanadu-cctl/allocator.h>



// stack 元素
typedef struct xtl_stack_node
{
	struct xtl_stack_node*		next;

	void*				data;
}xtl_stack_node;

// stack 类型
struct xtl_stack_data
{
	xtl_container_type		type;

	xtl_stack_node*			root;
	xtl_size_t			size;
	xtl_size_t 			element_size;
};




// 创建一个元素
static xtl_stack_node* xtl_stack_node_emplace(void* _Element)
{
	xtl_stack_node*		node = (xtl_stack_node*) x_posix_malloc(sizeof(xtl_stack_node));
	if(node)
	{
		x_posix_memset(node, 0, sizeof(xtl_stack_node));
		node->data = _Element;
	}
	return node;
}

// 创建一个元素
static xtl_stack_node* xtl_stack_node_new(const void* _Element, xtl_size_t _Size)
{
	xtl_stack_node*		node = NULL;
	void*			data = xtl_allocator_data_clone(_Element, _Size);
	if(data == NULL)
	{
		return NULL;
	}

	node = xtl_stack_node_emplace(data);
	if(node == NULL)
	{
		x_posix_free(data);
	}
	return node;
}




/// create a stack
_XCCTLAPI_ xtl_stack_t __xcall__ xtl_stack_new(xtl_size_t _ElementSize)
{
	xtl_stack_t	_Object = (xtl_stack_t) x_posix_malloc(sizeof(struct xtl_stack_data));
	if(_Object)
	{
		x_posix_memset(_Object, 0, sizeof(struct xtl_stack_data));
		_Object->type = XTL_CONTAINER_STACK;
		_Object->size = 0;
		_Object->element_size = _ElementSize;
		_Object->root = (xtl_stack_node*) x_posix_malloc(sizeof(xtl_stack_node));
		if(_Object->root == NULL)
		{
			x_posix_free(_Object);
			_Object = NULL;
		}
		else
		{
			x_posix_memset(_Object->root, 0, sizeof(struct xtl_stack_node));
		}
	}
	return _Object;
}

/// free stack object
_XCCTLAPI_ void __xcall__ xtl_stack_free(xtl_stack_t _Object)
{
	xtl_stack_clear(_Object);
	if(_Object->root)
	{
		x_posix_free(_Object->root);
		_Object->root = NULL;
	}
	x_posix_free(_Object);
}





/// container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_stack_size(xtl_stack_t _Object)
{
	return _Object->size;
}

/// the maximum size of the container
_XCCTLAPI_ xtl_size_t __xcall__ xtl_stack_max_size(xtl_stack_t _Object)
{
	XANADU_UNUSED(_Object);
	return xtl_allocator_max_size();
}





/// Check if container is empty
_XCCTLAPI_ bool __xcall__ xtl_stack_empty(xtl_stack_t _Object)
{
	return _Object->size == 0;
}

/// Check if an element exists in a container
_XCCTLAPI_ bool __xcall__ xtl_stack_exist(xtl_stack_t _Object)
{
	return _Object->size != 0;
}





/// Empty all data in container
_XCCTLAPI_ bool __xcall__ xtl_stack_clear(xtl_stack_t _Object)
{
	xtl_stack_node*		node = NULL;
	while(_Object->root->next)
	{
		node = _Object->root->next;
		_Object->root->next = _Object->root->next->next;
		x_posix_free(node->data);
		x_posix_free(node);
	}
	return true;
}





/// Insert element at the top
_XCCTLAPI_ bool __xcall__ xtl_stack_push(xtl_stack_t _Object, const void* _Element)
{
	return xtl_stack_emplace(_Object, xtl_allocator_data_clone(_Element, _Object->element_size));
}

/// Insert element at the top
_XCCTLAPI_ bool __xcall__ xtl_stack_emplace(xtl_stack_t _Object, void* _Element)
{
	// 构建一个节点
	xtl_stack_node*		new_node = xtl_stack_node_emplace(_Element);
	if(new_node == NULL)
	{
		return false;
	}

	new_node->next = _Object->root->next;
	_Object->root->next = new_node;
	++(_Object->size);

	return true;
}

/// remove element from top
_XCCTLAPI_ bool __xcall__ xtl_stack_pop(xtl_stack_t _Object)
{
	xtl_stack_node*		node = NULL;
	if(_Object->root->next)
	{
		node = _Object->root->next;
		_Object->root->next = _Object->root->next->next;
		x_posix_free(node->data);
		x_posix_free(node);
		return true;
	}
	else
	{
		return false;
	}
}

/// access top element
_XCCTLAPI_ void* __xcall__ xtl_stack_top(xtl_stack_t _Object)
{
	if(_Object->root->next)
	{
		return _Object->root->next->data;
	}
	else
	{
		return NULL;
	}
}
