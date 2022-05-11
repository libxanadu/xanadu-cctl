#ifndef			_XANADU_CCTL_VECTOR_H_
#define			_XANADU_CCTL_VECTOR_H_

#include <xanadu-cctl/header.h>


#if defined(__cplusplus)
extern "C" {
#endif


// vector 句柄
struct xtl_vector_data;
typedef struct xtl_vector_data*			xtl_vector_t;

// vector iterator 类型
struct xtl_vector_iter_data;
typedef struct xtl_vector_iter_data*		xtl_vector_iter_t;



/// 创建一个vector
/// \param _ElementSize : 单个元素的大小
/// \return : vector容器
_XCCTLAPI_ xtl_vector_t __xcall__ xtl_vector_new(xtl_size_t _ElementSize);

/// 释放一个vector
/// \param _Object : vector容器
_XCCTLAPI_ void __xcall__ xtl_vector_free(xtl_vector_t _Object);



/// 获取容器的具体数据指针
/// \param _Object : vector容器
/// \return : 数据指针
_XCCTLAPI_ void* __xcall__ xtl_vector_data(xtl_vector_t _Object);

/// 获取容器的大小
/// \param _Object : vector容器
/// \return : 容器的大小
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_size(xtl_vector_t _Object);

/// 获取容器的容量
/// \param _Object : vector容器
/// \return : 容器的容量
_XCCTLAPI_ xtl_size_t __xcall__ xtl_vector_capacity(xtl_vector_t _Object);



/// 容器是否为空
/// \param _Object : vector容器
/// \return : 当容器为空时返回true，否则返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_empty(xtl_vector_t _Object);

/// 容器是否存在元素
/// \param _Object : vector容器
/// \return : 当容器存在元素时返回true，为空时返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_exist(xtl_vector_t _Object);



/// 根据下标访问指定的元素
/// \param _Object : vector容器
/// \param _Pos : 元素下标
/// \return : 成功时返回元素地址，失败时返回NULL
_XCCTLAPI_ void* __xcall__ xtl_vector_at(xtl_vector_t _Object, xtl_size_t _Pos);



/// 清空容器
/// \param _Object : vector容器
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_clear(xtl_vector_t _Object);

/// 构建空间
/// \param _Object : vector容器
/// \param _Size : 新的空间大小
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_resize(xtl_vector_t _Object, xtl_size_t _Size);



/// 在尾部追加一个元素
/// \param _Object : vector容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_push_back(xtl_vector_t _Object, const void* _Element);

/// 在头部插入一个元素
/// \param _Object : vector容器
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_push_front(xtl_vector_t _Object, const void* _Element);

/// 在指定下标处插入一个元素
/// \param _Object : vector容器
/// \param _Pos : 需要插入的下标
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_insert(xtl_vector_t _Object, xtl_size_t _Pos, const void* _Element);

/// 将容器的元素替换为指定数量的元素
/// \param _Object : vector容器
/// \param _Count : 新元素的项数
/// \param _Element : 元素内存的指针
/// \return : 成功返回true，失败返回false
_XCCTLAPI_ bool __xcall__ xtl_vector_assign(xtl_vector_t _Object, xtl_size_t _Count, const void* _Element);



/// 获取迭代器的数据
/// \param _Object : vector容器
/// \param _Iterator : vector迭代器
/// \return : 数据指针
_XCCTLAPI_ void* __xcall__ xtl_vector_iter_data(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);

/// 获取指向开头的迭代器
/// \param _Object : vector容器
/// \return : vector迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_begin(xtl_vector_t _Object);

/// 获取指向末尾的迭代器
/// \param _Object : vector容器
/// \return : vector迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_end(xtl_vector_t _Object);

/// 当前迭代器的上一个迭代器
/// \param _Object : vector容器
/// \param _Iterator : vector迭代器
/// \return : 上一个迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_prev(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);

/// 当前迭代器的下一个迭代器
/// \param _Object : vector容器
/// \param _Iterator : vector迭代器
/// \return : 下一个迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_iter_next(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);



/// 移除迭代器指定的元素
/// \param _Object : vector容器
/// \param _Iterator : vector迭代器
/// \return : 下一个迭代器
_XCCTLAPI_ xtl_vector_iter_t __xcall__ xtl_vector_erase(xtl_vector_t _Object, xtl_vector_iter_t _Iterator);



#if defined(__cplusplus)
}
#endif


#endif
