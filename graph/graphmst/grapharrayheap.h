#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

typedef struct HeapElementType
{
	int key;
	int fromVertexID;
	int toVertexID;
} HeapNode;

typedef struct ArrayHeapType
{
	int maxElementCount;
	int currentElementCount;
	HeapNode *pElement;
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap* createArrayMaxHeap(int maxElementCount);
void deleteArrayMaxHeap(ArrayMaxHeap* pArrayHeap);
void insertMaxHeapAH(ArrayMaxHeap* pArrayHeap, HeapNode element);
HeapNode* deleteMaxHeapAH(ArrayMaxHeap* pArrayHeap);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif