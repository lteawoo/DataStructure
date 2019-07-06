#include <stdio.h>
#include <stdlib.h>
#include "graphlinkedlist.h"
#include "linkedgraph.h"
#include "linkedstack.h"
#include "graphtraversal.h"

int pushLSForDFS(LinkedStack* pStack, int nodeID)
{
	StackNode node = { 0, };
	node.data = nodeID;
	return pushLS(pStack, node);
}

void traversalDFS(LinkedGraph* pGraph, int startVertexID) {
	int i = 0;
	int vertexID = 0;
	LinkedStack* pStack = NULL;
	StackNode* pStackNode = NULL;
	ListNode *pListNode = NULL;
	int *pVisited = NULL;

	if (pGraph == NULL) {
		return;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		return;
	}

	pVisited = (int*)malloc(sizeof(int) * pGraph->maxVertexCount);
	if (pVisited == NULL) {
		printf("오류, 메모리 할당 in traversalDFS()\n");
		return;
	}

	//초기화
	for (i = 0; i < pGraph->maxVertexCount; i++) {
		pVisited[i] = FALSE;
	}

	pVisited[startVertexID] = TRUE;
	pushLSForDFS(pStack, startVertexID);

	while (isLinkedStackEmpty(pStack) == FALSE) {
		pStackNode = popLS(pStack);
		if (pStackNode != NULL) {
			vertexID = pStackNode->data;
			printf("[%d]-방문\n", vertexID);

			pListNode = pGraph->ppAdjEdge[vertexID]->headerNode.pLink;
			while (pListNode != NULL) {
				int vertexID = pListNode->data.vertexID;
				if (pVisited[vertexID] == FALSE) {
					pVisited[vertexID] = TRUE;
					pushLSForDFS(pStack, vertexID);
				}

				pListNode = pListNode->pLink;
			}
		}
	}

	free(pVisited);
	deleteLinkedStack(pStack);
}