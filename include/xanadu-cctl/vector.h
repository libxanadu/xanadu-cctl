#ifndef			_XANADU_CCTL_VECTOR_H_
#define			_XANADU_CCTL_VECTOR_H_

#include <xanadu-cctl/header.h>


XANADU_CXX_EXTERN_BEGIN


// vector type
struct xtl_vector_data;
typedef struct xtl_vector_data*			xtl_vector_t;

// vector iterator type
struct xtl_vector_iter_data;
typedef struct xtl_vector_iter_data*		xtl_vector_iter_t;



/// create a vector
/// \param _ElementSize : The size of a single element
/// \return : vector container
_XCCTLAPI_ xtl_vector_t __xcall__ xtl_vector_new(xtl_size_t _ElementSize);

/// free vector object
/// \param _Object : vector container
_XCCTLAPI_ void __xcall__ xtl_vector_free(xtl_vector_t _Object);



/// container data
/// \param _Object : vector container
/// \return : data pointer
_XCCTLAPI_ void* __xcall__ xtl_vector_data(xtl_vector_t _Object);

/// container size
/// \param _Object : vector container
/// \return : container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_size(xtl_vector_t _Object);

/// container capacity
/// \param _Object : vector container
/// \return : 容器的容量
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_capacity(xtl_vector_t _Object);



/// Check if container is empty
/// \param _Object : vector container
/// \return : Returns true if the container is empty, otherwise returns false
_XCCTLAPI_ bool __xcall__ xtl_vector_empty(xtl_vector_t _Object);

/// Check if an element exists in a container
/// \param _Object : vector container
/// \return : Returns true if the container has an element, false if it is empty
_XCCTLAPI_ bool __xcall__ xtl_vector_exist(xtl_vector_t _Object);



/// Access the specified element by subscript
/// \param _Object : vector container
/// \param _Pos : element subscript
/// \return : Returns the element address on success, NULL on failure
_XCCTLAPI_ void* __xcall__ xtl_vector_at(xtl_vector_t _Object, xtl_size_t _Pos);



/// Empty all data in container
/// \param _Object : vector container
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_vector_clear(xtl_vector_t _Object);

/// Resize the container
/// \param _Object : vector container
/// \param _Size : new number of elements
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_vector_resize(xtl_vector_t _Object, xtl_size_t _Size);



/// append an element to the end
/// \param _Object : vector container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_vector_push_back(xtl_vector_t _Object, const void* _Element);

/// Insert an element at the head
/// \param _Object : vector container
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_vector_push_front(xtl_vector_t _Object, const void* _Element);

/// Inserts an element at the specified subscript
/// \param _Object : vector container
/// \param _Pos : subscript to be inserted
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_vector_insert(xtl_vector_t _Object, xtl_size_t _Pos, const void* _Element);

/// Replaces the elements of the container with the specified number of elements
/// \param _Object : vector container
/// \param _Count : the number of items for the new element
/// \param _Element : the memory pointer of the element
/// \return : Returns true on success, false on failure
_XCCTLAPI_ bool __xcall__ xtl_vector_assign(xtl_vector_t _Object, xtl_size_t _Count, const void* _Element);



/// the element data pointed to by the iterator
/// \param _Object : vector container
/// \param _Iterator : vector iterator
/// \return : data pointer
_XCCTLAPI_ void* __xcall__ xtl_vector_iter_data(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);

/// iterator to the beginning of the container
/// \param _Object : vector container
/// \return : vector iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_begin(xtl_vector_t _Object);

/// iterator to the end of the container
/// \param _Object : vector container
/// \return : vector iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_end(xtl_vector_t _Object);

/// the previous iterator of the current iterator
/// \param _Object : vector container
/// \param _Iterator : vector iterator
/// \return : the previous iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_prev(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);

/// the next iterator of the current iterator
/// \param _Object : vector container
/// \param _Iterator : vector iterator
/// \return : the next iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_next(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);



/// emoves the element specified by the iterator
/// \param _Object : vector container
/// \param _Iterator : vector iterator
/// \return : the next iterator
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_erase(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);



XANADU_CXX_EXTERN_END


#endif
