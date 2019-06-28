#ifndef _GRAPH_ADJLIST_
#define _GRAPH_ADJLIST_

typedef struct LinkedGraphType
{
	int maxVertexCount;			// �ִ� ��� ����
	int currentVertexCount;		// ���� ���Ǵ� ����� ����
	int graphType;				// �׷��� ����: 1-Undirected, 2-Directed
	LinkedList** ppAdjEdge;		// ���� ������ ���� ����� ����Ʈ (������)�� �迭
	int* pVertex;				// ��� ������ ���� 1���� �迭
} LinkedGraph;