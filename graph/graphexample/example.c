#include <stdio.h>
#include <stdlib.h>
#include "graphlinkedlist.h"
#include "linkedgraph.h"
#include "graphsp.h"

int main(int argc, char *argv[])
{
	int i = 0;
	LinkedGraph *pG = NULL;
	int **A = NULL;

	// 그래프 생성
	pG = createLinkedDirectedGraph(8);
	if (pG != NULL) {
		// 그래프 초기화: 노드 추가
		for (i = 0; i < 8; i++) {
			addVertexLG(pG, i);
		}

		// 그래프 초기화: 간선 추가
		addEdgewithWeightLG(pG, 0, 3, 1);
		addEdgewithWeightLG(pG, 1, 0, 1);
		addEdgewithWeightLG(pG, 2, 0, 5);
		addEdgewithWeightLG(pG, 2, 3, 7);
		addEdgewithWeightLG(pG, 2, 4, 3);
		addEdgewithWeightLG(pG, 2, 6, 1);
		addEdgewithWeightLG(pG, 4, 3, 2);
		addEdgewithWeightLG(pG, 5, 4, 1);
		addEdgewithWeightLG(pG, 5, 7, 7);
		addEdgewithWeightLG(pG, 6, 1, 3);
		addEdgewithWeightLG(pG, 6, 4, 1);
		addEdgewithWeightLG(pG, 6, 7, 1);
		addEdgewithWeightLG(pG, 7, 1, 1);

		printf("G1:\n");
		displayLinkedGraph(pG);

		printf("\nFloyd 도달가능성 구하기:\n");
		A = checkReachability(pG);

		// 그래프 삭제
		if (A != NULL) {
			int r = 0;
			int maxNodeCount = getMaxVertexCountLG(pG);
			for (r = 0; r < maxNodeCount; r++) {
				free(A[r]);
			}
			free(A);
		}
		deleteLinkedGraph(pG);
	}

	return 0;
}