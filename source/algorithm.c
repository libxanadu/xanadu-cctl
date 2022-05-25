#include <xanadu-cctl/algorithm.h>
#include <xanadu-cctl/allocator.h>


// algorithm container type
typedef struct xtl_algorithm_container_type
{
	xtl_container_type		type;
}xtl_algorithm_container_type;



/// Sort the inner elements of the container, the container type must be an XTL container
_XCCTLAPI_ bool xtl_algorithm_sort(void* _Container, xtl_algorithm_sort_cb_t _CallBack, void* _UserData)
{
	XANADU_UNUSED(_UserData);

	if(_Container == NULL || _CallBack == NULL)
	{
		return false;
	}

	xtl_algorithm_container_type*	vAlgorithmContainer = (xtl_algorithm_container_type*)_Container;
	xtl_container_type		vContainerType = vAlgorithmContainer->type;
	switch (vContainerType)
	{
		case XTL_CONTAINER_ARRAY:
			break;
		case XTL_CONTAINER_DEQUE:
			break;
		case XTL_CONTAINER_LIST:
			break;
		case XTL_CONTAINER_MAP:
			break;
		case XTL_CONTAINER_QUEUE:
			break;
		case XTL_CONTAINER_SET:
			break;
		case XTL_CONTAINER_STACK:
			break;
		case XTL_CONTAINER_VECTOR:
			break;
		default:
			return false;
	}
	return true;
}
