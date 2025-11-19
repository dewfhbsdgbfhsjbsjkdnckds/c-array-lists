#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct arraylist {
	int capacity;
	int size;
	int *arr;
};
typedef struct arraylist arraylist;
// creates an empty list of capacity N
arraylist createList(int capacity){
	arraylist list = {
		capacity,
		0,
		malloc(capacity * sizeof(int))
	};
	return list;
}
// adds the element to the end of the list
void addToList(arraylist *list, int num){
	if (list->size == list->capacity){
		int *oldpointer = list->arr;
		list->arr = malloc(list->capacity * 2);
		memcpy(list->arr, oldpointer, list->size * sizeof(int));
		list->capacity *= 2;
		free(oldpointer);
	}
	list->arr[list->size] = num;
	list->size++;
}
// ugly for speed, extra function calls add overhead
// copies SRC onto DST
void listConcat(struct arraylist *list1, struct arraylist *list2){
	if (list1->capacity < (list1->size + list2->size)){
		int *list1pointer = list1->arr;
		list1->arr = malloc((list1->size + list2->size) * sizeof(int));
		list1->capacity = list1->size + list2->size;
		memcpy(list1->arr, list1pointer, list1->size * sizeof(int));
		free(list1pointer);
	}
	// only have to increment by 1 per int, because an int pointer is specifically 1 number per int
	memcpy(list1->arr + list1->size, list2->arr, list2->size * sizeof(int));
	list1->size += list2->size;
}
int main(){
	arraylist mylist = createList(20);
	arraylist secondList = createList(5);
	addToList(&mylist, 1);
	addToList(&mylist, 2);
	addToList(&mylist, 3);
	addToList(&secondList, 4);
	addToList(&secondList, 5);
	addToList(&secondList, 6);
	addToList(&secondList, 7);
	addToList(&secondList, 8);
	listConcat(&mylist, &secondList);
	for(int i = 0; i < mylist.size; i++){
		printf("%d\n", mylist.arr[i]);
	}
	return 0;
}
