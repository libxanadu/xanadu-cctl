#ifndef			_XANADU_CCTL_STACK_H_
#define			_XANADU_CCTL_STACK_H_

#include <xanadu-cctl/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// stack 类型
struct xtl_stack_data;
typedef struct xtl_stack_data*			xtl_stack_t;



/// 创建一个stack
/// \param _ElementSize : 单个元素的大小
/// \return : stack容器
_XCCTLAPI_ xtl_stack_t __xcall__ xtl_stack_new(xtl_size_t _ElementSize);

/// 释放一个stack
/// \param _Object : stack容器
_XCCTLAPI_ void __xcall__ xtl_stack_free(xtl_stack_t _Object);



/// 获取容器的大小
/// \param _Object : stack容器
/// \return : 容器的大小
_XCCTLAPI_ xtl_size_t __xcall__ xtl_stack_size(xtl_stack_t _Object);

/// 获取容器的最大大小
/// \param _Object : stack容器
/// \return : 容器的容量
_XCCTLAPI_ xtl_size_t __xcall__ xtl_stack_max_size(xtl_stack_t _Object);



/// 容器是否为空
/// \param _Object : stack容器
/// \return : 当容器为空时返回true，否则返回false
_XCCTLAPI_ bool __xcall__ xtl_stack_empty(xtl_stack_t _Object);

/// 容器是否存在元素
/// \param _Object : stack容器
/// \return : 当容器存在元素时返回true，为空时返回false
_XCCTLAPI_ bool __xcall__ xtl_stack_exist(xtl_stack_t _Object);



/// 清空容器
/// \param _Object : stack容器
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_stack_clear(xtl_stack_t _Object);



/// 在顶部插入元素
/// \param _Object : stack容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_stack_push(xtl_stack_t _Object, const void* _Element);

/// 在顶部插入元素
/// \param _Object : stack容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_stack_emplace(xtl_stack_t _Object, void* _Element);

/// 从顶部移除元素
/// \param _Object : stack容器
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_stack_pop(xtl_stack_t _Object);

/// 访问顶部元素
/// \param _Object : stack容器
/// \return : 数据指针
_XCCTLAPI_ void* __xcall__ xtl_stack_top(xtl_stack_t _Object);



#if defined(__cplusplus)
}
#endif


#endif
