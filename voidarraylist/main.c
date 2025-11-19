#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct arraylist {
	int capacity;
	int size;
	void *arr;
	int dataSize;
};
typedef struct arraylist arraylist;
// creates an empty list of capacity N
arraylist createList(int capacity, int sizeOfData){
	arraylist list = {
		capacity,
		0,
		malloc(capacity * sizeOfData),
		sizeOfData
	};
	return list;
}
// copies the element to the end of the list
void addToList(arraylist *list, void *dataPointer, int sizeOfData){
	if (list->size == list->capacity){
		void *oldpointer = list->arr;
		list->arr = malloc(list->capacity * 2);
		memcpy(list->arr, oldpointer, list->size * list->dataSize);
		list->capacity *= 2;
		free(oldpointer);
	}
	memcpy(list->arr + list->size * list->dataSize, dataPointer, sizeOfData);
	list->size++;
}
// ugly for speed, extra function calls add overhead
// copies SRC onto DST
void listConcat(struct arraylist *list1, struct arraylist *list2){
	if (list1->capacity < (list1->size + list2->size)){
		void *list1pointer = list1->arr;
		list1->arr = malloc(list1->size * list1->dataSize + list2->size * list2->dataSize);
		list1->capacity = list1->size + list2->size;
		memcpy(list1->arr, list1pointer, list1->size * list1->dataSize);
		free(list1pointer);
	}
	memcpy(list1->arr + (list1->size * list1->dataSize), list2->arr, list2->size * list2->size);
	list1->size += list2->size;
}
void* getItem(arraylist *list, int index){
	void *pointer = list->arr;
	pointer += index * list->dataSize;
	return pointer;
}
int main(){
	struct person{
		int age;
		char *name;
		int heightCm;
		int weightKg;
	};
	arraylist personList = createList(8, sizeof(struct person));
	struct person Bob = {
		16,
		"Bob",
		170,
		90
	};
	struct person Alice = {
		18,
		"Alice",
		190,
		90
	};
	addToList(&personList, &Bob, sizeof(struct person));
	addToList(&personList, &Alice, sizeof(struct person));
	for(int i = 0; i < personList.size; i++){
		printf("person %d\n", i);
		struct person *personPointer = (struct person*)getItem(&personList, i);
		personPointer->heightCm+=200;
		printf("name: %s\n", personPointer->name);
		printf("Height (in cm): %d\n", personPointer->heightCm);
		printf("Weight (in kg): %d\n", personPointer->weightKg);
		printf("\n");
	}
	return 0;
}
