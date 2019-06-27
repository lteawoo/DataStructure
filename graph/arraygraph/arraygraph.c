#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraygraph.h"

ArrayGraph* createArrayGraph(int maxVertexCount) {
	int i = 0, j = 0;
	ArrayGraph* pReturn = NULL;

	if (maxVertexCount > 0) {
		pReturn = (ArrayGraph*)malloc(sizeof(ArrayGraph));
		if (pReturn == NULL) {
			printf("오류, 메모리 할당(1), in createArrayGraph()\n");
			return NULL;
		}
		pReturn->graphType = GRAPH_UNDIRECTED;
		pReturn->maxVertexCount = maxVertexCount;
	}
	else {
		pritnf("오류, 최대 노드 개수는 0보다 커야합니다\n");
		return NULL;
	}
	
	pReturn->pVertex = (int*)malloc(sizeof(int) * maxVertexCount);
	if (pReturn->pVertex == NULL) {
		printf("오류, 메모리할당(2), in createArrayGraph()\n");
		if (pReturn != NULL) free(pReturn);
		return NULL;
	}
	pReturn->ppAdjEdge = (int**)malloc(sizeof(int*) * maxVertexCount);
	if (pReturn->ppAdjEdge == NULL) {
		printf("오류, 메모리할당(3), in createArrayGraph()\n");
		if (pReturn->pVertex != NULL) free(pReturn->pVertex);
		if (pReturn != NULL) free(pReturn);
		return NULL;
	}

	for (i = 0; i < maxVertexCount; i++) {
		pReturn->ppAdjEdge[i] = (int*)malloc(sizeof(int) * maxVertexCount);
		if (pReturn->ppAdjEdge[i] == NULL) {
			printf("오류, 메모리할당(4), in createArrayGraph()\n");
			for (j = 0; j < i - 1; j++) {
				if (pReturn->ppAdjEdge[j] != NULL) free(pReturn->ppAdjEdge[j]);
			}
			if (pReturn->ppAdjEdge != NULL) free(pReturn->ppAdjEdge);
			if (pReturn->pVertex != NULL) free(pReturn->pVertex);
			if (pReturn != NULL) free(pReturn);
			return NULL;
		}
	}

	memset(pReturn->pVertex, NOT_USED, sizeof(int) * maxVertexCount);
	for (i = 0; i < maxVertexCount; i++) {
		memset(pReturn->ppAdjEdge, 0, sizeof(int) * maxVertexCount);
	}

	return pReturn;
}