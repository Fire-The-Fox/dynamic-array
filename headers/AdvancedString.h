#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef ASTRING_INCLUDED

typedef struct {

    char *data;
} AdvancedString;


typedef struct {

    AdvancedString *data;
    int size;
    short created;
} StringArray;


void StringArray_Create(StringArray* array)
{
    array->size = 0;
    array->data = (AdvancedString*) malloc(array->size * sizeof(AdvancedString));
    array->created = 1;
}


AdvancedString StringArray_Get(StringArray array, int index)
{
    AdvancedString empty = {""};

    if(array.created) return *(array.data+index);

    printf("INFO: Did you initialize StringArray?\n");
    return empty;
}

char* StringArray_GetCharPointer(StringArray array, int index)
{
    if (array.created) return (array.data+index)->data;
    return "";
}


void StringArray_Append(StringArray* array, AdvancedString string)
{
    if(array->created) {

        array->size++;
        array->data = realloc(array->data, array->size * sizeof(AdvancedString));

        *(array->data+array->size-1) = string;

    } else {
        printf("INFO: Did you initialize StringArray?\n");
    }
}


void StringArray_Insert(StringArray* array, int index, AdvancedString value)
{
    if(array->created) {

        if (array->size > index){

            array->size++;
            array->data = realloc(array->data, array->size * sizeof(AdvancedString));

            for (int i = array->size; i > index; i--){
                *(array->data+i-1) = *(array->data+i-2);
            }

            *(array->data+index) = value;

        } else if (array->size == index) {
            StringArray_Append(array, value);

        } else {
            printf("INFO: Index is bigger than size of StringArray\n");
        }

    } else {
        printf("INFO: Did you initialize StringArray?\n");
    }
}


void StringArray_Set(StringArray* array, int index, AdvancedString string)
{
    if(array->created) {

        if (array->size >= index) *(array->data+index) = string;
        else printf("INFO: Index is bigger than size-1 of StringArray\n");

    } else {
        printf("INFO: Did you initialize StringArray?\n");
    }
}


void StringArray_Remove(StringArray* array, int index)
{
    if(array->created) {

        if (array->size > index) {
            for (int i = index; i < (array->size-1); i++) {
                *(array->data + i) = *(array->data + (i + 1));
            }

            array->size--;
            array->data = realloc(array->data, array->size * sizeof(AdvancedString));
        }

    } else {
        printf("INFO: Did you initialize StringArray?\n");
    }

}

int StringArray_Index(StringArray array, AdvancedString value);

void StringArray_Clear(StringArray* array)
{
    free(array->data);

    array->created = 0;
    array->size = 0;
}

#define AdvancedString_StartsWith(str, character) ((*(str.data+0)) == (character) ? 1 : 0 )
#define AdvancedString_EndsWith(str, character) ((*(str.data+strlen(str.data)-1)) == (character) ? 1 : 0 )

AdvancedString AdvancedString_Convert(char *string)
{
    AdvancedString tmp = {string};
    return tmp;
}

char *AdvancedString_Unconvert(AdvancedString string) 
{
    return string.data;
}

int AdvancedString_Count(AdvancedString string, char locate)
{
    int detections = 0;

    for (int i = 0; i < (int) strlen(string.data); i++){

        if (locate == *(string.data+i)) detections += 1;
    }

    return detections;
}

int AdvancedString_Find(AdvancedString string, char locate)
{
    int i;

    for(i = 0; i < (int) strlen(string.data); i++) {

        if (*(string.data+i) == locate) break;

    }
    return i;
}

AdvancedString AdvancedString_Add(AdvancedString string, char character)
{
    if (string.data == NULL) string.data = "";

    char *tmp_string = (char*) calloc(sizeof(AdvancedString), strlen(string.data)+1);

    strcpy(tmp_string, string.data);
    
    *(tmp_string+strlen(string.data)) = character;

    string.data = strdup(tmp_string);

    return string;
}

AdvancedString AdvancedString_Replace(AdvancedString string, char old, char new, int count)
{
    if (string.data == NULL) string.data = "";

    int replaced = 0;
    char *copy = (char*) calloc(sizeof(AdvancedString), strlen(string.data)+1);

    if (count == 0) count = strlen(string.data);

    *(copy+0) = ' ';

    for (int i = 0; i < strlen(string.data); i++) {

        if (new != '\0') {
            *(copy+i) = *(string.data+i);
            if (*(string.data+i) == old && replaced < count) {
                *(copy+i) = new;
                replaced++;
            }
        } else {
            if (*(string.data+i) == old && replaced < count) {
                i++;
                replaced++;
            }
            *(copy+i-replaced) = *(string.data+i);
        }
    }

    *(copy+strlen(copy)) = '\0';

    string.data = strdup(copy);

    return string;
}


int AdvancedString_Compare(AdvancedString string, AdvancedString string1)
{
    if (strcmp(string.data, string1.data) == 0) return 1;
    return 0;
}


StringArray AdvancedString_Split(AdvancedString string, char SplitChar)
{
    StringArray temp;

    StringArray_Create(&temp);

    AdvancedString temp_string = {""};

    for (int i = 0; i < (int) strlen(string.data); i++){

        if(*(string.data+i) == SplitChar){

            temp_string = AdvancedString_Add(temp_string, '\000');
            StringArray_Append(&temp, temp_string);
            temp_string.data = "";

        } else {
            temp_string = AdvancedString_Add(temp_string, *(string.data+i));
        }
    }

    StringArray_Append(&temp, temp_string);
    return temp;
}

AdvancedString AdvancedInput()
{

    char user_input;

    AdvancedString user_string;

    while (1) {
        user_input = getchar();

        if (user_input == '\n') break;

        user_string = AdvancedString_Add(user_string, user_input);
        
    }

    return user_string;
}


int StringArray_Index(StringArray array, AdvancedString value)
{
    int index;

    for (index = 0; index < array.size; index++) {
        if (AdvancedString_Compare(StringArray_Get(array, index), value)) break;
    }

    if (index < array.size) return index;
    else return -1;
}

#endif

#define ASTRING_INCLUDED