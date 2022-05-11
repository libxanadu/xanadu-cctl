#ifndef			_XANADU_CCTL_LIST_H_
#define			_XANADU_CCTL_LIST_H_

#include <xanadu-cctl/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// list 类型
struct xtl_list_data;
typedef struct xtl_list_data*			xtl_list_t;

// list iterator 类型
struct xtl_list_iter_data;
typedef struct xtl_list_iter_data*		xtl_list_iter_t;



/// 创建一个list
/// \param _ElementSize : 单个元素的大小
/// \return : list容器
_XCCTLAPI_ xtl_list_t __xcall__ xtl_list_new(xtl_size_t _ElementSize);

/// 释放一个list
/// \param _Object : list容器
_XCCTLAPI_ void __xcall__ xtl_list_free(xtl_list_t _Object);



/// 获取容器的大小
/// \param _Object : list容器
/// \return : 容器的大小
_XCCTLAPI_ xtl_size_t __xcall__ xtl_list_size(xtl_list_t _Object);

/// 获取容器的最大大小
/// \param _Object : list容器
/// \return : 容器的容量
_XCCTLAPI_ xtl_size_t __xcall__ xtl_list_max_size(xtl_list_t _Object);



/// 容器是否为空
/// \param _Object : list容器
/// \return : 当容器为空时返回true，否则返回false
_XCCTLAPI_ bool __xcall__ xtl_list_empty(xtl_list_t _Object);

/// 容器是否存在元素
/// \param _Object : list容器
/// \return : 当容器存在元素时返回true，为空时返回false
_XCCTLAPI_ bool __xcall__ xtl_list_exist(xtl_list_t _Object);



/// 清空容器
/// \param _Object : list容器
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_list_clear(xtl_list_t _Object);

/// 构建空间
/// \param _Object : list容器
/// \param _Size : 新的空间大小
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_list_resize(xtl_list_t _Object, xtl_size_t _Size);



/// 将容器的元素替换为指定数量的元素
/// \param _Object : list容器
/// \param _Count : 新元素的项数
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_list_assign(xtl_list_t _Object, xtl_size_t _Count, const void* _Element);



/// 在尾部追加一个元素
/// \param _Object : list容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_list_push_back(xtl_list_t _Object, const void* _Element);

/// 在头部插入一个元素
/// \param _Object : list容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_list_push_front(xtl_list_t _Object, const void* _Element);



/// 在尾部追加一个元素
/// \param _Object : list容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_list_emplace_back(xtl_list_t _Object, void* _Element);

/// 在头部插入一个元素
/// \param _Object : list容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_list_emplace_front(xtl_list_t _Object, void* _Element);



/// 获取迭代器的数据
/// \param _Object : list容器
/// \param _Iterator : list迭代器
/// \return : 数据指针
_XCCTLAPI_ void* __xcall__ xtl_list_iter_data(xtl_list_t _Object, xtl_list_iter_t _Iterator);

/// 获取指向开头的迭代器
/// \param _Object : list容器
/// \return : list迭代器
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_begin(xtl_list_t _Object);

/// 获取指向末尾的迭代器
/// \param _Object : list容器
/// \return : list迭代器
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_end(xtl_list_t _Object);

/// 当前迭代器的上一个迭代器
/// \param _Object : list容器
/// \param _Iterator : list迭代器
/// \return : 上一个迭代器
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_iter_prev(xtl_list_t _Object, xtl_list_iter_t _Iterator);

/// 当前迭代器的下一个迭代器
/// \param _Object : list容器
/// \param _Iterator : list迭代器
/// \return : 下一个迭代器
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_iter_next(xtl_list_t _Object, xtl_list_iter_t _Iterator);



/// 移除迭代器指定的元素
/// \param _Object : list容器
/// \param _Iterator : list迭代器
/// \return : 下一个迭代器
_XCCTLAPI_ xtl_list_iter_t __xcall__ xtl_list_erase(xtl_list_t _Object, xtl_list_iter_t _Iterator);



#if defined(__cplusplus)
}
#endif


#endif
