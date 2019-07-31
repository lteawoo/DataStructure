#include <stdio.h>
#include <stdlib.h>
#include "graphlinkedlist.h"
#include "linkedgraph.h"
#include "graphsp.h"

// Floyd �˰����� ����-���ް��ɼ����ϱ�
int** checkReachability(LinkedGraph* pGraph) {
	int **pReturn = NULL;
	int r = 0, s = 0, v = 0;
	int weight = 0;
	int maxNodeCount = 0;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return NULL;
	}
	maxNodeCount = getMaxVertexCountLG(pGraph);
	printf("��� ����: %d\n", maxNodeCount);

	pReturn = (int **)malloc(sizeof(int*) * maxNodeCount);
	if (pReturn == NULL) {
		printf("���� �޸��Ҵ�(1) in shortestPathFloyd()\n");
		return NULL;
	}

	for (r = 0; r < maxNodeCount; r++) {
		pReturn[r] = (int *)malloc(sizeof(int) * maxNodeCount);
		if (pReturn[r] == NULL) {
			for (s = 0; s < r - 1; s++) {
				if (pReturn[s] != NULL) free(pReturn[s]);
			}
			if (pReturn != NULL) free(pReturn);
			printf("����, �޸��Ҵ�(2) in shortestPathFloyd()\n");
			return NULL;
		}
	}

	//�ʱ�ȭ, �迭 pReturn�� �ʱ�ȭ
	for (r = 0; r < maxNodeCount; r++) {
		for (s = 0; s < maxNodeCount; s++) {
			if (r == s) {
				pReturn[r][s] = 0;
			}
			else {
				pReturn[r][s] = isExistEdge(pGraph, r, s);
			}
		}
	}
	printMatrix(pReturn, maxNodeCount);

	//Step 1. ���� Loop
	for (v = 0; v < maxNodeCount; v++) {
		for (r = 0; r < maxNodeCount; r++) {
			if (pReturn[r][v] == TRUE) {
				for (s = 0; s < maxNodeCount; s++) {
					if (pReturn[v][s] == TRUE) {
						pReturn[r][s] = TRUE;
					}
				}
			}
		}

		printf("[%d]-����\n", v + 1);
		printMatrix(pReturn, maxNodeCount);
	}

	return pReturn;
}

void printMatrix(int **A, int maxNodeCount) {
	int r = 0;
	int s = 0;

	for (s = 0; s < maxNodeCount; s++) {
		printf("\t%d", s);
	}
	printf("\n");

	for (r = 0; r < maxNodeCount; r++) {
		printf("%d:\t", r);
		for (s = 0; s < maxNodeCount; s++) {
			printf("%d\t", A[r][s]);
		}
		printf("\n");
	}
}

int isExistEdge(LinkedGraph* pGraph, int fromVertexID, int toVertexID) {
	int pReturn = FALSE;
	int position = 0;
	LinkedList* pEdgeList = NULL;
	ListNode* pListNode = NULL;

	if (pGraph != NULL) {
		pEdgeList = pGraph->ppAdjEdge[fromVertexID];
		if (pEdgeList != NULL) {
			position = findGraphNodePosition(pEdgeList, toVertexID);
			if (position >= 0) {
				pListNode = getLLElement(pEdgeList, position);
				if (pListNode != NULL) {
					pReturn = TRUE;
				}
			}
		}
	}

	return pReturn;
}