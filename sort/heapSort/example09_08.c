#include <stdio.h>
#include <stdlib.h>
#include "arrayheap.h"

void printArray(int value[], int count);

void heapSort(int value[], int count) {
	int i = 0;
	ArrayMinHeap* pHeap = NULL;

	pHeap = createArrayMinHeap(count);
	if (pHeap != NULL) {
		HeapNode node;
		
		for (i = 0; i < count; i++) {
			node.key = value[i];
			insertMinHeapAH(pHeap, node);
		}

		for (i = 0; i < count; i++) {
			HeapNode *pNode = deleteMinHeapAH(pHeap);
			if(pNode != NULL) {
				value[i] = pNode->key;
				free(pNode);
			}
		}
		
		deleteArrayMinHeap(pHeap);
	}
	else {
		printf("Error, createArrayMinHeap() in heapSort()\n");
		return;
	}
}

int main(int argc, char *argv[]) {
	int values[] = { 80, 50, 70, 10, 60, 20, 40, 30 };

	printf("Before Sort\n");
	printArray(values, 8);

	heapSort(values, 8);

	printf("\nAfter Sort\n");
	printArray(values, 8);

	return 0;
}

void printArray(int value[], int count)
{
	int i = 0;
	for (i = 0; i < count; i++) {
		printf("%d ", value[i]);
	}
	printf("\n");
}