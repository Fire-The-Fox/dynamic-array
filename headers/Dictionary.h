#ifndef ASTRING_INCLUDED
#include "AdvancedString.h"
#endif

#ifndef ARRAY_INCLUDED
#include "Array.h"
#endif

#ifndef _DICTIONARY_
#define _DICTIONARY_

typedef struct {

	StringArray keys;
	Array values;
	short created;

} Dictionary;


void Dictionary_Create(Dictionary *dict, int elementByteSize)
{
	StringArray_Create(&(dict->keys));
	Array_Create(&(dict->values), elementByteSize);
	dict->created = 1;
}

void Dictionary_Append(Dictionary *dict, char *name, void* value)
{
	if (dict->created) {
		StringArray_Append(&(dict->keys), AdvancedString_Convert(name));
		Array_Append(&(dict->values), value);
	}
}

void Dictionary_Replace(Dictionary *dict, char *name, void* value)
{
	if (dict->created) {
		int index = StringArray_Index((dict->keys), AdvancedString_Convert(name));
		Array_Replace(&(dict->values), index, value);
	}
}

void* Dictionary_Get(Dictionary dict, char *key)
{
	if (dict.created) {
		int index = StringArray_Index(dict.keys, AdvancedString_Convert(key));
		return Array_Get(dict.values, index);
	}
	return NULL;
}

#define Dictionary_UGet(dict, key, type) *((type*)Dictionary_Get(dict, key))

void Dictionary_Remove(Dictionary *dict, char *key)
{
	if (dict->created) {
		int index = StringArray_Index(dict->keys, AdvancedString_Convert(key));
		StringArray_Remove(&(dict->keys), index);
		Array_Remove(&(dict->values), index);
	}
}

void Dictionary_Clear(Dictionary *dict)
{
	if (dict->created) {
		StringArray_Clear(&(dict->keys));
		Array_Clear(&(dict->values));
	}
}

#endif
