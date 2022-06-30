#ifndef			_XANADU_CCTL_JSON_H_
#define			_XANADU_CCTL_JSON_H_

#include <xanadu-cctl/header.h>

XANADU_CXX_EXTERN_BEGIN


// json data
struct xtl_json_data;
typedef struct xtl_json_data*			xtl_json_t;

// json iterator type
struct xtl_json_iter_data;
typedef struct xtl_json_iter_data*		xtl_json_iter_t;

#define XTL_JSON_TYPE_NULL			(0)
#define XTL_JSON_TYPE_BOOLEAN			(1)
#define XTL_JSON_TYPE_NUMBER			(2)
#define XTL_JSON_TYPE_DOUBLE			(3)
#define XTL_JSON_TYPE_STRING			(4)
#define XTL_JSON_TYPE_ARRAY			(5)
#define XTL_JSON_TYPE_OBJECT			(6)

#define XTL_JSON_FORMAT_NULL			(0)
#define XTL_JSON_FORMAT_TAB			(1)



// Parse String to Json
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_parse(const char* _String);

// Format Json to string
_XCCTLAPI_ char* __xcall__ xtl_json_print(xtl_json_t _Object);

// Format Json to string
_XCCTLAPI_ char* __xcall__ xtl_json_printf(xtl_json_t _Object, int _Format);





// Create an object of type null
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_null();

// Create an object of type boolean
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_boolean(x_bool_t _Value);

// Create an object of type number
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_number(x_llong_t _Value);

// Create an object of type number
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_double(x_double_t _Value);

// Create an object of type string
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_string(const char* _Value);

// Create an object of type array
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_array();

// Create an object of type object
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_object();

// Release an object
_XCCTLAPI_ void __xcall__ xtl_json_free(xtl_json_t _Object);





// Get the type of the object
_XCCTLAPI_ int __xcall__ xtl_json_type(xtl_json_t _Object);

// Get the name of the current Json object
_XCCTLAPI_ const char*  __xcall__ xtl_json_name(xtl_json_t _Object);

// Get the size of the current object, only returned if the object is of type Array or Object
_XCCTLAPI_ xtl_size_t  __xcall__ xtl_json_size(xtl_json_t _Object);





// Check if object type is null
_XCCTLAPI_ bool __xcall__ xtl_json_is_null(xtl_json_t _Object);

// Check if object type is boolean
_XCCTLAPI_ bool __xcall__ xtl_json_is_boolean(xtl_json_t _Object);

// Check if object type is number
_XCCTLAPI_ bool __xcall__ xtl_json_is_number(xtl_json_t _Object);

// Check if object type is string
_XCCTLAPI_ bool __xcall__ xtl_json_is_string(xtl_json_t _Object);

// Check if object type is array
_XCCTLAPI_ bool __xcall__ xtl_json_is_array(xtl_json_t _Object);

// Check if object type is object
_XCCTLAPI_ bool __xcall__ xtl_json_is_object(xtl_json_t _Object);





// Convert the value of the object to boolean
_XCCTLAPI_ bool __xcall__ xtl_json_as_boolean(xtl_json_t _Object);

// Convert the value of the object to llong
_XCCTLAPI_ x_llong_t __xcall__ xtl_json_as_llong(xtl_json_t _Object);

// Convert the value of the object to ullong
_XCCTLAPI_ x_ullong_t __xcall__ xtl_json_as_ullong(xtl_json_t _Object);

// Convert the value of the object to double
_XCCTLAPI_ x_double_t __xcall__ xtl_json_as_double(xtl_json_t _Object);

// Convert the value of the object to string
_XCCTLAPI_ const char* __xcall__ xtl_json_as_string(xtl_json_t _Object);





// Get the child of the specified subscript of the json array
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_array_item(xtl_json_t _Object, xtl_size_t _Pos);

// Add an object at the beginning of the json array
_XCCTLAPI_ void __xcall__ xtl_json_array_prepend(xtl_json_t _Object, xtl_json_t _Item);

// Add an object to the end of the json array
_XCCTLAPI_ void __xcall__ xtl_json_array_append(xtl_json_t _Object, xtl_json_t _Item);

// Insert an object at the specified subscript of the json array
_XCCTLAPI_ void __xcall__ xtl_json_array_insert(xtl_json_t _Object, xtl_size_t _Pos, xtl_json_t _Item);

// Removes the specified child of the Json array object
_XCCTLAPI_ void __xcall__ xtl_json_array_remove(xtl_json_t _Object, xtl_size_t _Pos);

// Detach the specified children of a Json array object
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_array_detach(xtl_json_t _Object, xtl_size_t _Pos);





// Get the child of the specified subscript of the json array
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_object_item(xtl_json_t _Object, const char* _Key);

// Insert an object at the specified subscript of the json array
_XCCTLAPI_ void __xcall__ xtl_json_object_insert(xtl_json_t _Object, const char* _Key, xtl_json_t _Item);

// Removes the specified child of the Json array object
_XCCTLAPI_ void __xcall__ xtl_json_object_remove(xtl_json_t _Object, const char* _Key);

// Detach the specified children of a Json array object
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_object_detach(xtl_json_t _Object, const char* _Key);





// Get the forward start iterator of the json object
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_begin(xtl_json_t _Object);

// Get the forward end iterator of the json object
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_end(xtl_json_t _Object);

// child data of the current iterator
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_iter_data(xtl_json_t _Object, xtl_json_iter_t _Iterator);

// the previous iterator of the current iterator
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_prev(xtl_json_t _Object, xtl_json_iter_t _Iterator);

// the next iterator of the current iterator
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_next(xtl_json_t _Object, xtl_json_iter_t _Iterator);

// removes this iterator from the object and returns the next iterator
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_erase(xtl_json_t _Object, xtl_json_iter_t _Iterator);



XANADU_CXX_EXTERN_END

#endif
