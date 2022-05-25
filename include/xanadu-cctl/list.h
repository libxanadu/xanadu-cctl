#ifndef			_XANADU_CCTL_LIST_H_
#define			_XANADU_CCTL_LIST_H_

#include <xanadu-cctl/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// list type
struct xtl_list_data;
typedef struct xtl_list_data*			xtl_list_t;

// list iterator type
struct xtl_list_iter_data;
typedef struct xtl_list_iter_data*		xtl_list_iter_t;



/// create a list
/// \param _ElementSize : The size of a single element
/// \return : list container
_XCCTLAPI_ xtl_list_t __xcall__ xtl_list_new(xtl_size_t _ElementSize);

/// free list object
/// \param _Object : list container
_XCCTLAPI_ void __xcall__ xtl_list_free(xtl_list_t _Object);



/// container size
/// \param _Object : list container
/// \return : container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_list_size(xtl_list_t _Object);

/// the maximum size of the container
/// \param _Object : list container
/// \return : maximum size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_list_max_size(xtl_list_t _Object);



/// Check if container is empty
/// \param _Object : list container
/// \return : Returns true if the container is empty, otherwise returns false
_XCCTLAPI_ bool __xcall__ xtl_list_empty(xtl_list_t _Object);

/// Check if an element exists in a container
/// \param _Object : list container
/// \return : Returns true if the container has an element, false if it is empty
_XCCTLAPI_ bool __xcall__ xtl_list_exist(xtl_list_t _Object);



/// Empty all data in container
/// \param _Object : list container
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_list_clear(xtl_list_t _Object);

/// Resize the container
/// \param _Object : list container
/// \param _Size : new number of elements
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_list_resize(xtl_list_t _Object, xtl_size_t _Size);



/// Replaces the elements of the container with the specified number of elements
/// \param _Object : list container
/// \param _Count : the number of items for the new element
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_list_assign(xtl_list_t _Object, xtl_size_t _Count, const void* _Element);



/// append an element to the end
/// \param _Object : list container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_list_push_back(xtl_list_t _Object, const void* _Element);

/// Insert an element at the head
/// \param _Object : list container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_list_push_front(xtl_list_t _Object, const void* _Element);



/// append an element to the end
/// \param _Object : list container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_list_emplace_back(xtl_list_t _Object, void* _Element);

/// Insert an element at the head
/// \param _Object : list container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_list_emplace_front(xtl_list_t _Object, void* _Element);



/// the element data pointed to by the iterator
/// \param _Object : list container
/// \param _Iterator : list iterator
/// \return : data pointer
_XCCTLAPI_ void* __xcall__ xtl_list_iter_data(xtl_list_t _Object, xtl_list_iter_t _Iterator);

/// iterator to the beginning of the container
/// \param _Object : list container
/// \return : list iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_begin(xtl_list_t _Object);

/// iterator to the end of the container
/// \param _Object : list container
/// \return : list iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_end(xtl_list_t _Object);

/// the previous iterator of the current iterator
/// \param _Object : list container
/// \param _Iterator : list iterator
/// \return : the previous iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_iter_prev(xtl_list_t _Object, xtl_list_iter_t _Iterator);

/// the next iterator of the current iterator
/// \param _Object : list container
/// \param _Iterator : list iterator
/// \return : the next iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_iter_next(xtl_list_t _Object, xtl_list_iter_t _Iterator);



/// emoves the element specified by the iterator
/// \param _Object : list container
/// \param _Iterator : list iterator
/// \return : the next iterator
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_erase(xtl_list_t _Object, xtl_list_iter_t _Iterator);



#if defined(__cplusplus)
}
#endif


#endif
