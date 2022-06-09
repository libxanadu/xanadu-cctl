#ifndef			_XANADU_CCTL_HEADER_H_
#define			_XANADU_CCTL_HEADER_H_

#include <xanadu-posix/xanadu.h>



// xanadu cctl 导出宏
#if defined(XANADU_CCTL_BUILD_STATIC)
#define			_XCCTLAPI_
#else
#if defined(XANADU_CCTL_BUILD_LOCAL)
#define			_XCCTLAPI_					XANADU_COMPILER_API_EXP
#else
#define			_XCCTLAPI_					XANADU_COMPILER_API_IMP
#endif
#endif


XANADU_CXX_EXTERN_BEGIN

// xanadu cctl 类型定义
typedef			size_t						xtl_pos_t;
typedef			size_t 						xtl_size_t;

// xanadu cctl 宏定义
#define 		XTL_POS_NULL					((xtl_pos_t)-1)
#define 		XTL_ITERATOR_NULL				(NULL)
#define 		XTL_DEFAULT_CAPACITY				(8)

XANADU_CXX_EXTERN_END


#endif
