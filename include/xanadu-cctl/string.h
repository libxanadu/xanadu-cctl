#ifndef			_XANADU_CCTL_STRING_H_
#define			_XANADU_CCTL_STRING_H_

#include <xanadu-cctl/header.h>

XANADU_CXX_EXTERN_BEGIN


// string type
struct xtl_string_data;
typedef struct xtl_string_data*			xtl_string_t;

// string iterator type
struct xtl_string_iter_data;
typedef struct xtl_string_iter_data*		xtl_string_iter_t;



/// create a string
/// \param _String : Pointer to a null-terminated string, you can pass NULL
/// \return : string container
_XCCTLAPI_ xtl_string_t __xcall__ xtl_string_new(const char* _String);

/// free string object
/// \param _Object : container object
_XCCTLAPI_ void __xcall__ xtl_string_free(xtl_string_t _Object);





/// container data
/// \param _Object : container object
/// \return : data pointer
_XCCTLAPI_ char* __xcall__ xtl_string_data(xtl_string_t _Object);

/// container size
/// \param _Object : container object
/// \return : container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_string_size(xtl_string_t _Object);

/// container capacity
/// \param _Object : container object
/// \return : container capacity
_XCCTLAPI_ xtl_size_t __xcall__ xtl_string_capacity(xtl_string_t _Object);





/// Check if container is empty
/// \param _Object : container object
/// \return : Returns true if the container is empty, otherwise returns false
_XCCTLAPI_ bool __xcall__ xtl_string_empty(xtl_string_t _Object);

/// Check if an element exists in a container
/// \param _Object : container object
/// \return : Returns true if the container has an element, false if it is empty
_XCCTLAPI_ bool __xcall__ xtl_string_exist(xtl_string_t _Object);





/// Access the specified element by subscript
/// \param _Object : container object
/// \param _Pos : element subscript
/// \return : Returns the element address on success, NULL on failure
_XCCTLAPI_ void* __xcall__ xtl_string_at(xtl_string_t _Object, xtl_size_t _Pos);





/// Empty all data in container
/// \param _Object : container object
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_string_clear(xtl_string_t _Object);

/// Resize the container
/// \param _Object : container object
/// \param _Size : new number of elements
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_string_resize(xtl_string_t _Object, xtl_size_t _Size);





/// append an element to the end
/// \param _Object : container object
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_string_push_back(xtl_string_t _Object, char _Element);

/// Insert an element at the head
/// \param _Object : container object
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_string_push_front(xtl_string_t _Object, char _Element);

/// Inserts an element at the specified subscript
/// \param _Object : container object
/// \param _Pos : subscript to be inserted
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_string_insert(xtl_string_t _Object, xtl_size_t _Pos, const void* _Element);

/// Replaces the elements of the container with the specified number of elements
/// \param _Object : container object
/// \param _Count : the number of items for the new element
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_string_assign(xtl_string_t _Object, xtl_size_t _Count, char _Element);





/// the element data pointed to by the iterator
/// \param _Object : container object
/// \param _Iterator : iterator object for container
/// \return : data pointer
_XCCTLAPI_ void* __xcall__ xtl_string_iter_data(xtl_string_t _Object, xtl_string_iter_t _Iterator);

/// iterator to the beginning of the container
/// \param _Object : container object
/// \return : string iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_begin(xtl_string_t _Object);

/// iterator to the end of the container
/// \param _Object : container object
/// \return : string iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_end(xtl_string_t _Object);

/// the previous iterator of the current iterator
/// \param _Object : container object
/// \param _Iterator : iterator object for container
/// \return : the previous iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_iter_prev(xtl_string_t _Object, xtl_string_iter_t _Iterator);

/// the next iterator of the current iterator
/// \param _Object : container object
/// \param _Iterator : iterator object for container
/// \return : the next iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_iter_next(xtl_string_t _Object, xtl_string_iter_t _Iterator);





/// emoves the element specified by the iterator
/// \param _Object : container object
/// \param _Iterator : iterator object for container
/// \return : the next iterator
_XCCTLAPI_ xtl_string_iter_t __xcall__ xtl_string_erase(xtl_string_t _Object, xtl_string_iter_t _Iterator);



XANADU_CXX_EXTERN_END

#endif
