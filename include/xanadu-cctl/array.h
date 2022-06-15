#ifndef			_XANADU_CCTL_ARRAY_H_
#define			_XANADU_CCTL_ARRAY_H_

#include <xanadu-cctl/header.h>


XANADU_CXX_EXTERN_BEGIN


// array type
struct xtl_array_data;
typedef struct xtl_array_data*			xtl_array_t;

// array iterator type
struct xtl_array_iter_data;
typedef struct xtl_array_iter_data*		xtl_array_iter_t;



/// create a array
/// \param _ElemNumber : Number of elements of this object
/// \param _ElemSize : The size of a single element
/// \return : array container
_XCCTLAPI_ xtl_array_t __xcall__ xtl_array_new(xtl_size_t _ElemNumber, xtl_size_t _ElemSize);

/// free array object
/// \param _Object : container object
_XCCTLAPI_ void __xcall__ xtl_array_free(xtl_array_t _Object);





/// container data
/// \param _Object : container object
/// \return : data pointer
_XCCTLAPI_ void* __xcall__ xtl_array_data(xtl_array_t _Object);

/// container size
/// \param _Object : container object
/// \return : container size
_XCCTLAPI_ xtl_size_t __xcall__ xtl_array_size(xtl_array_t _Object);





/// Check if container is empty
/// \param _Object : container object
/// \return : Returns true if the container is empty, otherwise returns false
_XCCTLAPI_ bool __xcall__ xtl_array_empty(xtl_array_t _Object);

/// Check if an element exists in a container
/// \param _Object : container object
/// \return : Returns true if the container has an element, false if it is empty
_XCCTLAPI_ bool __xcall__ xtl_array_exist(xtl_array_t _Object);





/// Access the specified element by subscript
/// \param _Object : container object
/// \param _Pos : element subscript
/// \return : Returns the element address on success, NULL on failure
_XCCTLAPI_ void* __xcall__ xtl_array_at(xtl_array_t _Object, xtl_size_t _Pos);

/// Returns a reference to the element at specified location pos.
/// \param _Object : container object
/// \param _Pos : element subscript
/// \return : Returns the element address on success, NULL on failure
_XCCTLAPI_ void* __xcall__ xtl_array_opt_key(xtl_array_t _Object, xtl_size_t _Pos);

/// Returns a reference to the first element in the container.
/// \param _Object : container object
/// \return : Returns the element address on success, NULL on failure
_XCCTLAPI_ void* __xcall__ xtl_array_font(xtl_array_t _Object);

/// Returns a reference to the last element in the container.
/// \param _Object : container object
/// \return : Returns the element address on success, NULL on failure
_XCCTLAPI_ void* __xcall__ xtl_array_back(xtl_array_t _Object);





/// Assigns the given value value to all elements in the container.
/// \param _Object : container object
/// \param _Element : the value to assign to the elements
_XCCTLAPI_ void __xcall__ xtl_array_fill(xtl_array_t _Object, const void* _Element);

/// Swap the contents of a container with the contents of other containers.
/// \param _Object : container object
/// \param _Other : container object
_XCCTLAPI_ void __xcall__ xtl_array_swap(xtl_array_t _Object, xtl_array_t _Other);





/// the element data pointed to by the iterator
/// \param _Object : container object
/// \param _Iterator : iterator object for container
/// \return : data pointer
_XCCTLAPI_ void* __xcall__ xtl_array_iter_data(xtl_array_t _Object, xtl_array_iter_t _Iterator);

/// iterator to the beginning of the container
/// \param _Object : container object
/// \return : array iterator
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_begin(xtl_array_t _Object);

/// iterator to the end of the container
/// \param _Object : container object
/// \return : array iterator
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_end(xtl_array_t _Object);

/// the previous iterator of the current iterator
/// \param _Object : container object
/// \param _Iterator : iterator object for container
/// \return : the previous iterator
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_iter_prev(xtl_array_t _Object, xtl_array_iter_t _Iterator);

/// the next iterator of the current iterator
/// \param _Object : container object
/// \param _Iterator : iterator object for container
/// \return : the next iterator
_XCCTLAPI_ xtl_array_iter_t __xcall__ xtl_array_iter_next(xtl_array_t _Object, xtl_array_iter_t _Iterator);



XANADU_CXX_EXTERN_END


#endif
