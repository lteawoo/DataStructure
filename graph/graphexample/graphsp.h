#ifndef _GRAPH_SP_
#define _GRAPH_SP_

// Floyd���� ���ް��ɼ� �˰���
int** checkReachability(LinkedGraph* pGraph);
void printMatrix(int **A, int maxNodeCount);
int isExistEdge(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#endif