#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

typedef struct HeapElementType
{
	int key;
	char data;
} HeapNode;

typedef struct ArrayHeapType
{
	int maxElementCount;
	int currentElementCount;
	HeapNode *pElement;
} ArrayMinHeap, ArrayMinHeap;

ArrayMinHeap* createArrayMinHeap(int maxElementCount);
void deleteArrayMinHeap(ArrayMinHeap* pArrayHeap);
void insertMinHeapAH(ArrayMinHeap* pArrayHeap, HeapNode element);
HeapNode* deleteMinHeapAH(ArrayMinHeap* pArrayHeap);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif