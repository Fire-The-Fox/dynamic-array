## Note
This repository is an anrchive, reffer to actual fox libraries

# dynamic-array
C header files for simple dynamic sized array manipulation

These header files work together and creates complex but simple to use arrays like: `StringArray`, `Array` and last but not least `Dictionary` which is not array by 100% but it contains 2 arrays and every value can be searched by key

## Usage
Use of `int` with `Array`
```c
#include "headers/Array.h"
#include <stdio.h>

int main() {
	
	Array array;
	int number = 5, number3 = 14;
	
	// This step is required otherwise computer is going to complain
	Array_Create(&array, sizeof(int)); // []
	
	Array_Append(&array, &number); // [5]
	
	for (int i = 0; i < 10; i++) {
		int number2 = i + 10;
		Array_Append(&array, &number2); // Adds numbers 10, 11, 12, ..., 19 to our array
	}
	
	Array_Insert(&array, 3, &number); // [5, 10, 11, 5, 12, 13, 14, 15, 16, 17, 18, 19]
	Array_Replace(&array, 9, &number); //    [5, 10, 11, 5, 12, 13, 14, 15, 16, 5, 18, 19]
	Array_Remove(&array, 5); //          [5, 10, 11, 5, 12, 14, 15, 16, 5, 18, 19]
	
	printf("Index of 14 is: %d\n", Array_Index(array, &number3)); // Index of 14 is: 5
	 
	 // print values of our array in nice way
	printf("[");
	for (int i = 0; i < array.size-1; i++) {
		printf("%d, ", Array_UGet(array, i, int));
	}
	printf("%d]\n", Array_UGet(array, array.size-1, int));
	
	// After we are done with using our array, we need to clear it to prevent memory leaks
	Array_Clear(&array);
	
	return 0;
}
```
<br>

Use of own data types with `Array`
```c
typedef struct {
	int health;
	int defence;
	char *name;
} player;
...
Array array;
Array_Create(&array, sizeof(player));
...
Array_UGet(array, 0, player);
...
```
<br>

Use of `int` with `Dictionary`

```c
#include "headers/Dictionary.h"
#include <stdio.h>

int main() {

	//               🍎  🍌  🍋  🍇  🍓
	int prices[] = {25, 10, 20, 5, 15};
	char* names[] = {"Apple", "Banana", "Lemon", "Grapes", "Strawberry"};
	Dictionary dict;
	
	// This step is required otherwise computer is going to complain
	Dictionary_Create(&dict, sizeof(int)); // {}
	
	Dictionary_Append(&dict, names[0], &prices[0]); // {"Apple": 25}
	
	// lets add leftover elements
	for (int i = 1; i < 5; i++) {
		Dictionary_Append(&dict, names[i], &prices[i]);
	}
	
	// Grapes looks cheap, lets change price with strawberry
	Dictionary_Replace(&dict, "Grapes", &prices[4]);
	Dictionary_Replace(&dict, "Strawberry", &prices[3]);
	
	// We are out of stock with Bananas, lets remove them
	Dictionary_Remove(&dict, "Banana");
	
	// Our leftover
	printf("{");
	for (int i = 0; i < dict.keys.size-1; i++) {
		char *key = StringArray_GetCharPointer(dict.keys, i);
		printf("\"%s\": %d, ", key, Dictionary_UGet(dict, key, int));
	}
	char *key = StringArray_GetCharPointer(dict.keys, dict.keys.size-1);
	printf("\"%s\": %d}\n", key, Dictionary_UGet(dict, key, int));
	
	return 0;
}
```
<br>

Use of own data types with `Dictionary`
It's same as for `Array`
