#ifndef _GRAPH_ADJLIST_
#define _GRAPH_ADJLIST_

typedef struct LinkedGraphType
{
	int maxVertexCount;			// 최대 노드 개수
	int currentVertexCount;		// 현재 사용되는 노드의 개수
	int currentEdgeCount;		// 현재 사용되는 간선의 개수
	int graphType;				// 그래프 종류: 1-Undirected, 2-Directed
	LinkedList** ppAdjEdge;		// 간선 저장을 위한 ㅇ녀결 리스트 (포인터)의 배열
	int* pVertex;				// 노드 저장을 위한 1차원 배열
} LinkedGraph;

LinkedGraph* createLinkedGraph(int maxVertexCount);
LinkedGraph* createLinkedDirectedGraph(int maxVertexCount);
void deleteLinkedGraph(LinkedGraph* pGraph);
int isEmptyLG(LinkedGraph* pGraph);
int addVertexLG(LinkedGraph* pGraph, int vertexID);
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight);
int checkVertexValid(LinkedGraph* pGraph, int vertexID);
int removeVertexLG(LinkedGraph* pGraph, int vertexID);
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
void deleteGraphNode(LinkedList* pList, int delVertexID);
int findGraphNodePosition(LinkedList* pList, int vertexID);
int getEdgeCountLG(LinkedGraph* pGraph);
int getVertexCountLG(LinkedGraph* pGraph);
int getMaxVertexCountLG(LinkedGraph* pGraph);
int getGraphTypeLG(LinkedGraph* pGraph);
void displayLinkedGraph(LinkedGraph pGraph);
#endif

#ifndef _COMMON_GRAPH_DEF_
#define _COMMON_GRAPH_DEF_

#define USED					1
#define NOT_USED				0

#define SUCCESS					1
#define FAIL					0

#define TRUE					1
#define FALSE					0

#define GRAPH_UNDIRECTED		1
#define GRAPH_DIRECTED			2
#endif