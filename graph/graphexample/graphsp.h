#ifndef _GRAPH_SP_
#define _GRAPH_SP_

// Floyd변형 도달가능성 알고리즘
int** checkReachability(LinkedGraph* pGraph);
void printMatrix(int **A, int maxNodeCount);
int isExistEdge(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#endif