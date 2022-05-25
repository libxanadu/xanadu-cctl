#ifndef			_XANADU_CCTL_STACK_H_
#define			_XANADU_CCTL_STACK_H_

#include <xanadu-cctl/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// stack type
struct xtl_stack_data;
typedef struct xtl_stack_data*			xtl_stack_t;



/// create a stack
/// \param _ElementSize : The size of a single element
/// \return : stack container
_XCCTLAPI_ xtl_stack_t __xcall__ xtl_stack_new(xtl_size_t _ElementSize);

/// free stack object
/// \param _Object : stack container
_XCCTLAPI_ void __xcall__ xtl_stack_free(xtl_stack_t _Object);



/// container size
/// \param _Object : stack container
/// \return : container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_stack_size(xtl_stack_t _Object);

/// the maximum size of the container
/// \param _Object : stack container
/// \return : maximum size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_stack_max_size(xtl_stack_t _Object);



/// Check if container is empty
/// \param _Object : stack container
/// \return : Returns true if the container is empty, otherwise returns false
_XCCTLAPI_ bool __xcall__ xtl_stack_empty(xtl_stack_t _Object);

/// Check if an element exists in a container
/// \param _Object : stack container
/// \return : Returns true if the container has an element, false if it is empty
_XCCTLAPI_ bool __xcall__ xtl_stack_exist(xtl_stack_t _Object);



/// Empty all data in container
/// \param _Object : stack container
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_stack_clear(xtl_stack_t _Object);



/// Insert element at the top
/// \param _Object : stack container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_stack_push(xtl_stack_t _Object, const void* _Element);

/// Insert element at the top
/// \param _Object : stack container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_stack_emplace(xtl_stack_t _Object, void* _Element);

/// remove element from top
/// \param _Object : stack container
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_stack_pop(xtl_stack_t _Object);

/// access top element
/// \param _Object : stack container
/// \return : data pointer
_XCCTLAPI_ void* __xcall__ xtl_stack_top(xtl_stack_t _Object);



#if defined(__cplusplus)
}
#endif


#endif
