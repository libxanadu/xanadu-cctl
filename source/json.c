#include <xanadu-cctl/json.h>



// json data
struct xtl_json_data
{
	struct xtl_json_data*		prev;
	struct xtl_json_data*		next;
	struct xtl_json_data*		child;

	int 				type;
	char*				name;
	union
	{
		x_llong_t 		v_llong;
		x_double_t 		v_double;
		char*			v_string;
	}value;
};





// Skip extraneous characters from a string
static const char* __xcall__ xtl_json_format_skip(const char* _String)
{
	char 		vChar = 0;
	while(_String)
	{
		vChar = *_String;
		if(vChar == '\0')
		{
			return NULL;
		}
		if(vChar == '\r' || vChar == '\n' || vChar == '\t' || vChar == ' ')
		{
			++_String;
		}
		else
		{
			break;
		}
	}
	return _String;
}

// Check if a character is a number
static const char* __xcall__ xtl_json_format_check_number(const char* _String)
{
	char 		vChar = 0;
	while(_String)
	{
		vChar = _String[0];
		if('0' <= vChar && vChar <= '9')
		{
		}
		else
		{
			switch (vChar)
			{
				case ' ':
				case '.':
				case '+':
				case '-':
				case 'E':
				case 'e':
				case 'X':
				case 'x':
					break;
				default:
					return _String;
			}
		}
		++_String;
	}
	return _String;
}

// Format Json object from string
static const char* __xcall__ xtl_json_from_string(const char* _String, xtl_json_t* _Object)
{
	if(_String == NULL || _Object == NULL)
	{
		return NULL;
	}

	_String = xtl_json_format_skip(_String);
	if(_String == NULL)
	{
		return NULL;
	}

	char 		vChar = _String[0];
	if(0 == x_posix_strncmp(_String, "null", 4))
	{
		*_Object = xtl_json_new_null();
		return xtl_json_format_skip(_String + 4);
	}
	else if(0 == x_posix_strncmp(_String, "true", 4))
	{
		*_Object = xtl_json_new_boolean(true);
		return xtl_json_format_skip(_String + 4);
	}
	else if(0 == x_posix_strncmp(_String, "false", 5))
	{
		*_Object = xtl_json_new_boolean(false);
		return xtl_json_format_skip(_String + 5);
	}
	else if(vChar == '+' || vChar == '-' || ('0' <= vChar && vChar <= '9'))
	{
		const char*	vEnd = xtl_json_format_check_number(_String + 1);
		if(vEnd)
		{
			xtl_size_t 	vSize = vEnd - _String;
			char*		vBuffer = (char*) x_posix_malloc(vSize + 1);
			if(vBuffer)
			{
				x_posix_strncpy(vBuffer, _String, vSize);
				vBuffer[vSize] = 0;

				if(0 == x_posix_strncmp(vBuffer, "0x", 2))
				{
					// number hex
					x_ullong_t	vValue = x_posix_strtoull(vBuffer, NULL, 16);
					*_Object = xtl_json_new_number((x_llong_t)vValue);
				}
				else if(x_posix_stristr(vBuffer, "E") || x_posix_strstr(vBuffer, "."))
				{
					// number double
					x_double_t 	vValue = x_posix_strtod(vBuffer, NULL);
					*_Object = xtl_json_new_double(vValue);
				}
				else if('+' == vChar)
				{
					x_ullong_t	vValue = x_posix_strtoull(vBuffer + 1, NULL, 10);
					*_Object = xtl_json_new_number((x_llong_t)vValue);
				}
				else if('-' == vChar)
				{
					x_llong_t	vValue = x_posix_strtoll(vBuffer, NULL, 10);
					*_Object = xtl_json_new_number(vValue);
				}
				else
				{
					x_ullong_t	vValue = x_posix_strtoull(vBuffer, NULL, 10);
					*_Object = xtl_json_new_number((x_llong_t)vValue);
				}

				x_posix_free(vBuffer);
				return xtl_json_format_skip(_String + vSize);
			}
		}
	}
	else if(vChar == '\"')
	{
		const char*	vEnd = x_posix_strchr(_String + 1, '\"');
		if(vEnd)
		{
			xtl_size_t 	vSize = vEnd - _String - 1;
			if(vSize == 0)
			{
				*_Object = xtl_json_new_string(NULL);
				return xtl_json_format_skip(_String + vSize + 2);
			}
			else
			{
				char*	vBuffer = (char*) x_posix_malloc(vSize + 1);
				if(vBuffer)
				{
					x_posix_strncpy(vBuffer, _String + 1, vSize);
					vBuffer[vSize] = 0;
					*_Object = xtl_json_new_string(vBuffer);
					x_posix_free(vBuffer);
					return xtl_json_format_skip(_String + vSize + 2);
				}
			}
		}
	}
	else if(vChar == '[')
	{
		_String = xtl_json_format_skip(_String + 1);
		if(_String)
		{
			xtl_json_t 	vJsonArray = xtl_json_new_array();
			if(vJsonArray)
			{
				while(_String)
				{
					vChar = _String[0];
					if(vChar == ']')
					{
						*_Object = vJsonArray;
						return xtl_json_format_skip(_String + 1);
					}

					xtl_json_t	vArrayNode = NULL;
					_String = xtl_json_from_string(_String, &vArrayNode);
					if(vArrayNode == NULL)
					{
						_String = NULL;
						break;
					}
					xtl_json_array_append(vJsonArray, vArrayNode);

					_String = xtl_json_format_skip(_String);
					if(_String == NULL)
					{
						break;
					}

					// Check for commas
					if(_String[0] == ',')
					{
						++_String;
					}
					_String = xtl_json_format_skip(_String);
				}
				xtl_json_free(vJsonArray);
			}
		}
	}
	else if(vChar == '{')
	{
		_String = xtl_json_format_skip(_String + 1);
		if(_String)
		{
			xtl_json_t 	vJsonObject = xtl_json_new_object();
			if(vJsonObject)
			{
				while(_String)
				{
					vChar = _String[0];
					if(vChar == '}')
					{
						*_Object = vJsonObject;
						return xtl_json_format_skip(_String + 1);
					}

					// find key
					xtl_json_t	vObjectKey = NULL;
					_String = xtl_json_from_string(_String, &vObjectKey);
					if(vObjectKey == NULL)
					{
						_String = NULL;
						break;
					}
					if(vObjectKey->type != XTL_JSON_TYPE_STRING)
					{
						xtl_json_free(vObjectKey);
						_String = NULL;
						break;
					}

					// find split
					_String = xtl_json_format_skip(_String);
					if(_String == NULL || _String[0] != ':')
					{
						xtl_json_free(vObjectKey);
						_String = NULL;
						break;
					}
					++_String;

					// find value
					xtl_json_t	vObjectValue = NULL;
					_String = xtl_json_from_string(_String, &vObjectValue);
					if(vObjectValue == NULL)
					{
						xtl_json_free(vObjectKey);
						_String = NULL;
						break;
					}
					xtl_json_object_insert(vJsonObject, xtl_json_as_string(vObjectKey), vObjectValue);
					xtl_json_free(vObjectKey);
					_String = xtl_json_format_skip(_String);
					if(_String == NULL)
					{
						break;
					}

					// Check for commas
					if(_String[0] == ',')
					{
						++_String;
					}
					_String = xtl_json_format_skip(_String);
				}
				xtl_json_free(vJsonObject);
			}
		}
	}

	return NULL;
}

// Calculate the length required to convert an object to a string
static xtl_size_t __xcall__ xtl_json_to_string_size(xtl_json_t _Object, int _Format, xtl_size_t _Level)
{
	xtl_size_t	vSize = 0;
	switch (_Object->type)
	{
		case XTL_JSON_TYPE_NULL:
			vSize = 4;
			break;
		case XTL_JSON_TYPE_BOOLEAN:
			vSize = _Object->value.v_llong ? 4 : 5;
			break;
		case XTL_JSON_TYPE_NUMBER:
			vSize = x_posix_snprintf(NULL, 0, "%lld", _Object->value.v_llong);
			break;
		case XTL_JSON_TYPE_DOUBLE:
			vSize = x_posix_snprintf(NULL, 0, "%lf", _Object->value.v_double);
			break;
		case XTL_JSON_TYPE_STRING:
			vSize = x_posix_strlen(_Object->value.v_string) + 2;
			break;
		case XTL_JSON_TYPE_ARRAY:
		{
			// [
			vSize += 1;
			xtl_json_t 	vNode = _Object->child;
			while(vNode)
			{
				// \t * _Level + \n
				vSize += (_Format == XTL_JSON_FORMAT_TAB) ? (_Level + 1 + 1) : 0;

				// value
				vSize += xtl_json_to_string_size(vNode, _Format, _Level + 1);

				// ,
				vSize += vNode->next ? 1 : 0;

				vNode = vNode->next;
			}
			// \t * _Level + \n
			vSize += (_Format == XTL_JSON_FORMAT_TAB) ? (_Level + 1) : 0;
			// ]
			vSize += 1;
		}
			break;
		case XTL_JSON_TYPE_OBJECT:
		{
			// {
			vSize += 1;
			xtl_json_t 	vNode = _Object->child;
			while(vNode)
			{
				// \t * _Level + \n
				vSize += (_Format == XTL_JSON_FORMAT_TAB) ? (_Level + 1 + 1) : 0;

				// "name":
				vSize += x_posix_strlen(vNode->name) + 3;

				// value
				vSize += xtl_json_to_string_size(vNode, _Format, _Level + 1);

				// ,
				vSize += vNode->next ? 1 : 0;

				vNode = vNode->next;
			}
			// \t * _Level + \n
			vSize += (_Format == XTL_JSON_FORMAT_TAB) ? (_Level + 1) : 0;
			// {
			vSize += 1;
		}
			break;
		default:
			break;
	}
	return vSize;
}

// Json build format string
static xtl_size_t __xcall__ xtl_json_to_string_format(char* _String, int _Format, xtl_size_t _Level)
{
	xtl_size_t	vSize = 0;
	if(XTL_JSON_FORMAT_TAB == _Format)
	{
		_String[vSize] = '\n';
		for(vSize = 1; vSize <= _Level; ++vSize)
		{
			_String[vSize] = '\t';
		}
	}
	return vSize;
}

// Convert Json object to string
static xtl_size_t __xcall__ xtl_json_to_string(char* _String, xtl_json_t _Object, int _Format, xtl_size_t _Level)
{
	xtl_size_t	vSize = 0;
	switch (_Object->type)
	{
		case XTL_JSON_TYPE_NULL:
			x_posix_strcpy(_String, "null");
			vSize = 4;
			break;
		case XTL_JSON_TYPE_BOOLEAN:
			x_posix_strcpy(_String, _Object->value.v_llong ? "true" : "false");
			vSize = _Object->value.v_llong ? 4 : 5;
			break;
		case XTL_JSON_TYPE_NUMBER:
			vSize = x_posix_sprintf(_String, "%lld", _Object->value.v_llong);
			break;
		case XTL_JSON_TYPE_DOUBLE:
			vSize = x_posix_sprintf(_String, "%lf", (x_double_t)_Object->value.v_double);
			break;
		case XTL_JSON_TYPE_STRING:
			vSize = x_posix_sprintf(_String, "\"%s\"", _Object->value.v_string);
			break;
		case XTL_JSON_TYPE_ARRAY:
		{
			x_posix_strcpy(_String + vSize, "[");
			vSize += 1;

			xtl_json_t 	vNode = _Object->child;
			while(vNode)
			{
				vSize += xtl_json_to_string_format(_String + vSize, _Format, _Level + 1);

				vSize += xtl_json_to_string(_String + vSize, vNode, _Format, _Level + 1);

				if(vNode->next)
				{
					_String[vSize] = ',';
					vSize += 1;
				}

				vNode = vNode->next;
			}
			vSize += xtl_json_to_string_format(_String + vSize, _Format, _Level);

			x_posix_strcpy(_String + vSize, "]");
			vSize += 1;
		}
			break;
		case XTL_JSON_TYPE_OBJECT:
		{
			x_posix_strcpy(_String + vSize, "{");
			vSize += 1;

			xtl_json_t 	vNode = _Object->child;
			while(vNode)
			{
				vSize += xtl_json_to_string_format(_String + vSize, _Format, _Level + 1);

				vSize += x_posix_sprintf(_String + vSize, "\"%s\"", vNode->name);

				_String[vSize] = ':';
				vSize += 1;

				vSize += xtl_json_to_string(_String + vSize, vNode, _Format, _Level + 1);

				if(vNode->next)
				{
					_String[vSize] = ',';
					vSize += 1;
				}

				vNode = vNode->next;
			}
			vSize += xtl_json_to_string_format(_String + vSize, _Format, _Level);

			x_posix_strcpy(_String + vSize, "}");
			vSize += 1;
		}
			break;
		default:
			break;
	}
	return vSize;
}



// Parse String to Json
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_parse(const char* _String)
{
	if(_String == NULL)
	{
		return NULL;
	}

	xtl_json_t	vJsonValue = NULL;

	xtl_json_from_string(_String, &vJsonValue);

	return vJsonValue;
}

// Format Json to string
_XCCTLAPI_ char* __xcall__ xtl_json_print(xtl_json_t _Object)
{
	return xtl_json_printf(_Object, XTL_JSON_FORMAT_NULL);
}

// Format Json to string
_XCCTLAPI_ char* __xcall__ xtl_json_printf(xtl_json_t _Object, int _Format)
{
	char*		vString = NULL;
	xtl_size_t	vAdvance = xtl_json_to_string_size(_Object, _Format, 0);
	xtl_size_t 	vActual = 0;
	if(vAdvance > 0)
	{
		vString = (char*) x_posix_malloc(vAdvance + 1);
		if(vString)
		{
			// x_posix_memset(vString, 0, vSize + 1);
			vString[vAdvance] = 0;

			vActual = xtl_json_to_string(vString, _Object, _Format, 0);
			if(vAdvance == vActual)
			{
				return vString;
			}
			x_posix_free(vString);
		}
	}
	return NULL;
}





// Create an object of type null
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_null()
{
	xtl_json_t	vObject = (xtl_json_t) x_posix_malloc(sizeof(struct xtl_json_data));
	if(vObject)
	{
		x_posix_memset(vObject, 0, sizeof(struct xtl_json_data));

		vObject->type = XTL_JSON_TYPE_NULL;
	}
	return vObject;
}

// Create an object of type boolean
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_boolean(x_bool_t _Value)
{
	xtl_json_t	vObject = xtl_json_new_number(_Value ? 1 : 0);
	if(vObject)
	{
		vObject->type = XTL_JSON_TYPE_BOOLEAN;
	}
	return vObject;
}

// Create an object of type number
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_number(x_llong_t _Value)
{
	xtl_json_t	vObject = xtl_json_new_null();
	if(vObject)
	{
		vObject->type = XTL_JSON_TYPE_NUMBER;
		vObject->value.v_llong = _Value;
	}
	return vObject;
}

// Create an object of type number
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_double(x_double_t _Value)
{
	xtl_json_t	vObject = xtl_json_new_null();
	if(vObject)
	{
		vObject->type = XTL_JSON_TYPE_DOUBLE;
		vObject->value.v_double = _Value;
	}
	return vObject;
}

// Create an object of type string
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_string(const char* _Value)
{
	xtl_json_t	vObject = xtl_json_new_null();
	if(vObject)
	{
		vObject->type = XTL_JSON_TYPE_STRING;
		vObject->value.v_string = x_posix_strdup(_Value);
	}
	return vObject;
}

// Create an object of type array
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_array()
{
	xtl_json_t	vObject = xtl_json_new_null();
	if(vObject)
	{
		vObject->type = XTL_JSON_TYPE_ARRAY;
	}
	return vObject;
}

// Create an object of type object
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_new_object()
{
	xtl_json_t	vObject = xtl_json_new_null();
	if(vObject)
	{
		vObject->type = XTL_JSON_TYPE_OBJECT;
	}
	return vObject;
}

// Release an object
_XCCTLAPI_ void __xcall__ xtl_json_free(xtl_json_t _Object)
{
	xtl_json_t		node = NULL;
	if(_Object == NULL)
	{
		return;
	}

	// Step 1: Release the child
	xtl_json_free(_Object->child);

	// Step 2: Release the next node
	while(_Object->next)
	{
		node = _Object->next;
		_Object->next = _Object->next->next;
		xtl_json_free(node);
	}

	// Step 3: Free your own memory
	x_posix_free(_Object->name);
	if(_Object->type == XTL_JSON_TYPE_STRING)
	{
		x_posix_free(_Object->value.v_string);
	}
	x_posix_free(_Object);
}





// Get the type of the object
_XCCTLAPI_ int __xcall__ xtl_json_type(xtl_json_t _Object)
{
	return _Object->type;
}

// Get the name of the current Json object
_XCCTLAPI_ const char*  __xcall__ xtl_json_name(xtl_json_t _Object)
{
	return _Object->name;
}

// Get the size of the current object, only returned if the object is of type Array or Object
_XCCTLAPI_ xtl_size_t  __xcall__ xtl_json_size(xtl_json_t _Object)
{
	xtl_size_t	vSize = 0;
	xtl_json_t 	vNode = _Object->child;
	if(_Object->type == XTL_JSON_TYPE_ARRAY || _Object->type == XTL_JSON_TYPE_OBJECT)
	{
		while(vNode)
		{
			++vSize;
			vNode = vNode->next;
		}
	}
	return vSize;
}





// Check if object type is null
_XCCTLAPI_ bool __xcall__ xtl_json_is_null(xtl_json_t _Object)
{
	return _Object->type == XTL_JSON_TYPE_NULL;
}

// Check if object type is boolean
_XCCTLAPI_ bool __xcall__ xtl_json_is_boolean(xtl_json_t _Object)
{
	return _Object->type == XTL_JSON_TYPE_BOOLEAN;
}

// Check if object type is number
_XCCTLAPI_ bool __xcall__ xtl_json_is_number(xtl_json_t _Object)
{
	return _Object->type == XTL_JSON_TYPE_NUMBER || _Object->type == XTL_JSON_TYPE_DOUBLE;
}

// Check if object type is string
_XCCTLAPI_ bool __xcall__ xtl_json_is_string(xtl_json_t _Object)
{
	return _Object->type == XTL_JSON_TYPE_STRING;
}

// Check if object type is array
_XCCTLAPI_ bool __xcall__ xtl_json_is_array(xtl_json_t _Object)
{
	return _Object->type == XTL_JSON_TYPE_ARRAY;
}

// Check if object type is object
_XCCTLAPI_ bool __xcall__ xtl_json_is_object(xtl_json_t _Object)
{
	return _Object->type == XTL_JSON_TYPE_OBJECT;
}





// Convert the value of the object to boolean
_XCCTLAPI_ bool __xcall__ xtl_json_as_boolean(xtl_json_t _Object)
{
	if(_Object->type == XTL_JSON_TYPE_BOOLEAN)
	{
		return _Object->value.v_llong;
	}
	return false;
}

// Convert the value of the object to llong
_XCCTLAPI_ x_llong_t __xcall__ xtl_json_as_llong(xtl_json_t _Object)
{
	if(_Object->type == XTL_JSON_TYPE_NUMBER || _Object->type == XTL_JSON_TYPE_DOUBLE)
	{
		return _Object->value.v_llong;
	}
	return 0;
}

// Convert the value of the object to ullong
_XCCTLAPI_ x_ullong_t __xcall__ xtl_json_as_ullong(xtl_json_t _Object)
{
	if(_Object->type == XTL_JSON_TYPE_NUMBER || _Object->type == XTL_JSON_TYPE_DOUBLE)
	{
		return (x_ullong_t)_Object->value.v_llong;
	}
	return 0;
}

// Convert the value of the object to double
_XCCTLAPI_ x_double_t __xcall__ xtl_json_as_double(xtl_json_t _Object)
{
	if(_Object->type == XTL_JSON_TYPE_NUMBER || _Object->type == XTL_JSON_TYPE_DOUBLE)
	{
		return (x_double_t)_Object->value.v_double;
	}
	return 0.0f;
}

// Convert the value of the object to string
_XCCTLAPI_ const char* __xcall__ xtl_json_as_string(xtl_json_t _Object)
{
	if(_Object->type == XTL_JSON_TYPE_STRING)
	{
		return (const char*)_Object->value.v_string;
	}
	return NULL;
}





// Get the child of the specified subscript of the json array
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_array_item(xtl_json_t _Object, xtl_size_t _Pos)
{
	xtl_json_t 	vNode = _Object->child;
	if(_Object->type == XTL_JSON_TYPE_ARRAY)
	{
		while(vNode && _Pos)
		{
			--_Pos;
			vNode = vNode->next;
		}
		return vNode;
	}
	return NULL;
}

// Add an object at the beginning of the json array
_XCCTLAPI_ void __xcall__ xtl_json_array_prepend(xtl_json_t _Object, xtl_json_t _Item)
{
	if(_Object->type != XTL_JSON_TYPE_ARRAY)
	{
		return;
	}

	if(_Object->child)
	{
		_Item->next = _Object->child;
		_Object->child->prev = _Item;
		_Object->child = _Item;
	}
	else
	{
		_Object->child = _Item;
		_Item->prev = NULL;
		_Item->next = NULL;
	}
}

// Add an object to the end of the json array
_XCCTLAPI_ void __xcall__ xtl_json_array_append(xtl_json_t _Object, xtl_json_t _Item)
{
	xtl_json_t 	vNode = _Object->child;
	if(_Object->type != XTL_JSON_TYPE_ARRAY)
	{
		return;
	}

	if(_Object->child)
	{
		while(vNode->next)
		{
			vNode = vNode->next;
		}
		vNode->next = _Item;
		_Item->prev = vNode;
		_Item->next = NULL;
	}
	else
	{
		_Object->child = _Item;
		_Item->prev = NULL;
		_Item->next = NULL;
	}
}

// Insert an object at the specified subscript of the json array
_XCCTLAPI_ void __xcall__ xtl_json_array_insert(xtl_json_t _Object, xtl_size_t _Pos, xtl_json_t _Item)
{
	xtl_json_t	vNode = NULL;
	if(_Object->type != XTL_JSON_TYPE_ARRAY)
	{
		return;
	}

	if(_Pos == 0)
	{
		xtl_json_array_prepend(_Object, _Item);
	}
	else
	{
		vNode = xtl_json_array_item(_Object, _Pos);
		if(vNode == NULL)
		{
			xtl_json_array_append(_Object, _Item);
		}
		else
		{
			if(vNode->next)
			{
				vNode->next->prev = _Item;
			}
			_Item->next = vNode->next;
			_Item->prev = vNode;
			vNode->next = _Item;
		}
	}
}

// Removes the specified child of the Json array object
_XCCTLAPI_ void __xcall__ xtl_json_array_remove(xtl_json_t _Object, xtl_size_t _Pos)
{
	xtl_json_t	vNode = xtl_json_array_detach(_Object, _Pos);
	if(vNode)
	{
		xtl_json_free(vNode);
	}
}

// Detach the specified children of a Json array object
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_array_detach(xtl_json_t _Object, xtl_size_t _Pos)
{
	xtl_json_t	vNode = NULL;
	if(_Object->type != XTL_JSON_TYPE_ARRAY)
	{
		return NULL;
	}

	if(_Pos == 0)
	{
		if(_Object->child)
		{
			vNode = _Object->child;
			_Object->child = _Object->child->next;
			if(_Object->child)
			{
				_Object->child->prev = NULL;
			}
		}
	}
	else
	{
		vNode = xtl_json_array_item(_Object, _Pos);
		if(vNode)
		{
			if(vNode->next)
			{
				vNode->next->prev = vNode->prev;
			}
			vNode->prev->next = vNode->next;
		}
	}

	if(vNode)
	{
		vNode->prev = NULL;
		vNode->next = NULL;
	}
	return vNode;
}





// Get the child of the specified subscript of the json array
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_object_item(xtl_json_t _Object, const char* _Key)
{
	xtl_json_t 	vNode = _Object->child;
	if(_Object->type == XTL_JSON_TYPE_OBJECT && _Key)
	{
		while(vNode)
		{
			if(vNode->name && 0 == x_posix_strcmp(vNode->name, _Key))
			{
				break;
			}
			vNode = vNode->next;
		}
		return vNode;
	}
	return NULL;
}

// Insert an object at the specified subscript of the json array
_XCCTLAPI_ void __xcall__ xtl_json_object_insert(xtl_json_t _Object, const char* _Key, xtl_json_t _Item)
{
	xtl_json_t 	vNode = _Object->child;
	if(_Object->type != XTL_JSON_TYPE_OBJECT || _Key == NULL || _Item == NULL)
	{
		return;
	}

	if(_Item->name != _Key)
	{
		x_posix_free(_Item->name);
		_Item->name = x_posix_strdup(_Key);
	}

	vNode = xtl_json_object_detach(_Object, _Key);
	if(vNode)
	{
		_Item->prev = vNode->prev;
		_Item->next = vNode->next;
		if(vNode == _Object->child)
		{
			_Object->child = _Item;
		}

		// free object
		vNode->prev = NULL;
		vNode->next = NULL;
		xtl_json_free(vNode);
	}
	else
	{
		if(_Object->child)
		{
			vNode = _Object->child;
			while(vNode->next)
			{
				vNode = vNode->next;
			}

			_Item->next = NULL;
			_Item->prev = vNode;
			vNode->next = _Item;
		}
		else
		{
			_Object->child = _Item;
		}
	}
}

// Removes the specified child of the Json array object
_XCCTLAPI_ void __xcall__ xtl_json_object_remove(xtl_json_t _Object, const char* _Key)
{
	xtl_json_t	vNode = xtl_json_object_detach(_Object, _Key);
	if(vNode)
	{
		xtl_json_free(vNode);
	}
}

// Detach the specified children of a Json array object
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_object_detach(xtl_json_t _Object, const char* _Key)
{
	xtl_json_t	vNode = NULL;
	if(_Object->type != XTL_JSON_TYPE_OBJECT || _Key == NULL)
	{
		return NULL;
	}

	vNode = xtl_json_object_item(_Object, _Key);
	if(vNode)
	{
		if(vNode->next)
		{
			vNode->next->prev = vNode->prev;
		}
		if(vNode->prev)
		{
			vNode->prev->next = vNode->next;
		}
		else
		{
			_Object->child = NULL;
		}
	}

	if(vNode)
	{
		vNode->prev = NULL;
		vNode->next = NULL;
	}
	return vNode;
}





// Get the forward start iterator of the json object
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_begin(xtl_json_t _Object)
{
	return (xtl_json_iter_t)_Object->child;
}

// Get the forward end iterator of the json object
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_end(xtl_json_t _Object)
{
	XANADU_UNUSED(_Object);

	return NULL;
}

// child data of the current iterator
_XCCTLAPI_ xtl_json_t __xcall__ xtl_json_iter_data(xtl_json_t _Object, xtl_json_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	return (xtl_json_t)_Iterator;
}

// the previous iterator of the current iterator
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_prev(xtl_json_t _Object, xtl_json_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	xtl_json_t	vNode = (xtl_json_t)_Iterator;
	return (xtl_json_iter_t)vNode->prev;
}

// the next iterator of the current iterator
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_next(xtl_json_t _Object, xtl_json_iter_t _Iterator)
{
	XANADU_UNUSED(_Object);

	xtl_json_t	vNode = (xtl_json_t)_Iterator;
	return (xtl_json_iter_t)vNode->next;
}

// removes this iterator from the object and returns the next iterator
_XCCTLAPI_ xtl_json_iter_t __xcall__ xtl_json_iter_erase(xtl_json_t _Object, xtl_json_iter_t _Iterator)
{
	xtl_json_t	vCurrent = _Object->child;
	xtl_json_t	vNode = (xtl_json_t)_Iterator;
	if(_Object->child && _Iterator)
	{
		if(_Object->child == vNode)
		{
			_Object->child = _Object->child->next;
			if(_Object->child)
			{
				_Object->child->prev = NULL;
			}

			// free node
			vNode->prev = NULL;
			vNode->next = NULL;
			xtl_json_free(vNode);

			return (xtl_json_iter_t)_Object->child;
		}
		else
		{
			while(vCurrent)
			{
				if(vCurrent == vNode)
				{
					if(vCurrent->next)
					{
						vCurrent->next->prev = vCurrent->prev;
					}
					if(vCurrent->prev)
					{
						vCurrent->prev->next = vCurrent->next;
					}
					_Iterator = (xtl_json_iter_t)vCurrent->next;

					// free node
					vNode->prev = NULL;
					vNode->next = NULL;
					xtl_json_free(vNode);

					return _Iterator;
				}
				vCurrent = vCurrent->next;
			}
		}
	}
	return NULL;
}
