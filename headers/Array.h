/*
 * DynamicArrays - group of header files for dynamic sized array manipulation
 * Copyright (C) 2022 Ján Gajdoš
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef ARRAY_INCLUDED

typedef struct {

    void* data;
    int size;
    short created;
    int elementByteSize;

} Array;


void Array_Create(Array* array, int elementByteSize)
{
    array->size = 0;
    array->created = 1;

    array->elementByteSize = elementByteSize;
    array->data = calloc(1, array->elementByteSize);
}

void Array_Append(Array *array, void *item)
{
    if (array->created) {

        array->size++;

        array->data = realloc(array->data, array->size * array->elementByteSize);
        memcpy(array->data + (array->size-1) * array->elementByteSize, item, array->elementByteSize);
    } else printf("INFO: Did you initialize Array?\n");
}

void* Array_Get(Array array, int index)
{
    if (array.created) return ((void*) array.data+(index) * array.elementByteSize);
    return NULL;
}

#define Array_UGet(array, index, type) *((type*)Array_Get(array, index))

void Array_Insert(Array *array, int index, void *item)
{
    if (array->created) {
		array->size++;
		array->data = realloc(array->data, array->size * array->elementByteSize);

		for (int i = array->size; i > index; i--){
		    memcpy(array->data + (i - 1) * array->elementByteSize, array->data + (i - 2) * array->elementByteSize, array->elementByteSize);
		}

		memcpy(array->data + index * array->elementByteSize, item, array->elementByteSize);
    } else printf("INFO: Did you initialize Array?\n");
}

void Array_Replace(Array *array, int index, void *item)
{
	if (array->created) {
		if (array->size > index) memcpy(array->data + index * array->elementByteSize, item, array->elementByteSize);
		else printf("INFO: Index is bigger than size-1 of Array\n");
	} else printf("INFO: Did you initialize Array?\n");
}

void Array_Remove(Array *array, int index) 
{
	if (array->created) {
		
		if (array->size > index) {
			
			for (int i = index; i < (array->size-1); i++) {
				memcpy(array->data + i * array->elementByteSize, array->data + (i + 1) * array->elementByteSize, array->elementByteSize);	
            }
		
			array->size--;
            array->data = realloc(array->data, array->size * array->elementByteSize);
		} else printf("INFO: Index is bigger than size-1 of Array\n");
	} else printf("INFO: Did you initialize Array?\n");
}

int Array_Index(Array array, void* item)
{
	int index;
	if (array.created) {
		for (index = 0; index < array.size; index++) {
			if (memcmp(item, Array_Get(array, index), array.elementByteSize) == 0) {
				break;
			}
		}
		return (index < array.size) ? index : -1;

	} else printf("INFO: Did you initialize Array?\n");
	return -1;
}

void Array_Clear(Array *array)
{
	if (array->created){

	    free(array->data);
	
	    array->created = 0;
	    array->size = 0;
		array->elementByteSize = 0;
	}  else printf("INFO: Did you initialize Array?\n");
}
#endif

#define ARRAY_INCLUDED
