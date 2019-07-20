#ifndef _GRAPH_MST_KRUSKAL_
#define _GRAPH_MST_KRUSKAL_

// kruskal �˰���
LinkedGraph *mstKruskal(LinkedGrpah* pGraph);

// ���� �׷���G�� ������ ����ġ ���� ������������ ����
ArrayMinHeap *orderEdges(LinkedGraph* pGraph);

// ��ȯ �˻�
int checkCycle(LinkedGraph* pGraph, int fromVertexID, int toVertexID);

#endif