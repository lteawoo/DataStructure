#ifndef _GRAPH_ADJLIST_
#define _GRAPH_ADJLIST_

typedef struct LinkedGraphType
{
	int maxVertexCount;			// 최대 노드 개수
	int currentVertexCount;		// 현재 사용되는 노드의 개수
	int graphType;				// 그래프 종류: 1-Undirected, 2-Directed
	LinkedList** ppAdjEdge;		// 간선 저장을 위한 ㅇ녀결 리스트 (포인터)의 배열
	int* pVertex;				// 노드 저장을 위한 1차원 배열
} LinkedGraph;