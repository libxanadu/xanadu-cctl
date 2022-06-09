#ifndef			_XANADU_CCTL_ALGORITHM_H_
#define			_XANADU_CCTL_ALGORITHM_H_

#include <xanadu-cctl/header.h>


XANADU_CXX_EXTERN_BEGIN


/// Sort callback
/// \param _Value1 : value 1
/// \param _Value2 : value 2
/// \param _UserData : callback parameter
/// \return : Less than return (-1/<0), equal return (0/=0), greater than return (1/>0)
typedef int (__xcall__ * xtl_algorithm_sort_cb_t)(const void* _Value1, const void* _Value2, void* _UserData);



/// TODO: Not implemented
/// Sort the inner elements of the container, the container type must be an XTL container
/// \param _Container : XTL container
/// \param _CallBack : Sort callback
/// \param _UserData : callback parameter
/// \return : Returns true if the container has an element, false if it is empty
_XCCTLAPI_ bool xtl_algorithm_sort(void* _Container, xtl_algorithm_sort_cb_t _CallBack, void* _UserData);


XANADU_CXX_EXTERN_END


#endif
