#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btreedef.h"
#include "btlinkedstack.h"
#include "btree.h"

// 트리의 생성
BTree* createBTree()
{
	BTree *pReturn = NULL;

	pReturn = (BTree*)malloc(sizeof(BTree));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(BTree));
	}
	else {
		printf("오류, 메모리 할당 in createBTree()\n");
		return NULL;
	}

	return pReturn;
}

BTreeNodeData* searchBT(BTree* pBTree, int key) {
	BTreeNodeData* pReturn = NULL;
	BTreeNode* pCurrentNode = NULL;
	int i = 0;

	if (pBTree != NULL) {
		pCurrentNode = pBTree->pRootNode;
		while (pCurrentNode != NULL) {
			for (i = 0; i < pCurrentNode->element[i].key; i++) {
				int parentKey = pCurrentNode->element[i].key;

				if (key == parentKey) {
					pReturn = &pCurrentNode->element[i];
					return pReturn;
				}
				else if (key < parentKey) {
					break;
				}
			}
			pCurrentNode = pCurrentNode->pChildren[i];
		}
	}

	return pReturn;
}

int pushBTreeNode(LinkedStack* pStack, BTreeNode* data)
{
	StackNode node = { 0, };
	node.data = data;

	return pushLS(pStack, node);
}

int insertNodeBT(BTree* pBTree, BTreeNodeData element) {
	int ret = TRUE;
	int i = 0;

	BTreeNode *pParentNode = NULL, *pCurrentNode = NULL, *pNewNode = NULL;
	LinkedStack* pStack = NULL;

	if (pBTree == NULL) {
		ret = FALSE;
		return ret;
	}
	pStack = createLinkedStack();
	if (pStack == NULL) {
		ret = FALSE;
		return ret;
	}

	// INSERT할 leaf node 찾기.
	pCurrentNode = pBTree->pRootNode;
	while (pCurrentNode != NULL) {
		pParentNode = pCurrentNode;
		pushBTreeNode(pStack, pParentNode);

		for (i = 0; i < pCurrentNode->elementCount; i++) {
			int parentKey = pCurrentNode->element[i].key;
			if (element.key == parentKey) {
				printf("오류,중복된 키-[%d],insertNodeBT()\n", element.key);
				ret = FALSE;
				deleteLinkedStack(pStack);
				return ret;
			}
			else if (element.key < parentKey) {
				break;
			}
		}
		pCurrentNode = pCurrentNode->pChildren[i];
	}
	if (pParentNode == NULL) { // ROOT 노드가 아직 없는 경우.
		pBTree->pRootNode = createBTreeNode(element);
	}
	else {
		insertNodeElementBT(pParentNode, element, NULL);

		splitNodeBT(pBTree, pStack);
	}
	ret = TRUE;
	deleteLinkedStack(pStack);

	return ret;
}

void splitNodeBT(BTree* pBTree, LinkedStack* pStack)
{
	StackNode* pParentStackNode = NULL;
	StackNode* pCurrentStackNode = NULL;
	BTreeNode* pParentBTreeNode = NULL;
	BTreeNode* pCurrentBTreeNode = NULL;
	BTreeNode* pNewBTreeNode = NULL;
	BTreeNodeData pivotElement = { 0, };
	int pivotIndex = BTREE_ORDER / 2;
	int i = 0;

	if (pStack == NULL) {
		return;
	}
	pCurrentStackNode = popLS(pStack);
	while (pCurrentStackNode != NULL) {
		pCurrentBTreeNode = pCurrentStackNode->data;
		//BTREE m계수보다 크거나같을때 분할대상..
		if (pCurrentBTreeNode->elementCount >= BTREE_ORDER) {
			pNewBTreeNode = (BTreeNode *)malloc(sizeof(BTreeNode));
			if (pNewBTreeNode != NULL) {
				memset(pNewBTreeNode, 0, sizeof(BTreeNode));
			}
			else {
				printf("Error, malloc() in splitNodeBT()\n");
				break;
			}

			pivotElement = pCurrentBTreeNode->element[pivotIndex];
			memset(&pCurrentBTreeNode->element[pivotIndex], 0, sizeof(BTreeNodeData));

			for (i = pivotIndex + 1; i < BTREE_ORDER; i++) {
				pNewBTreeNode->element[i - pivotIndex - 1] = pCurrentBTreeNode->element[i];
				pNewBTreeNode->pChildren[i - pivotIndex - 1] = pCurrentBTreeNode->pChildren[i];

				memset(&pCurrentBTreeNode->element[i], 0, sizeof(BTreeNodeData));
				pCurrentBTreeNode->pChildren[i] = NULL;
			}
			pNewBTreeNode->pChildren[i - pivotIndex - 1] = pCurrentBTreeNode->pChildren[i];
			pCurrentBTreeNode->pChildren[i] = NULL;
			pNewBTreeNode->elementCount = BTREE_ORDER - pivotIndex - 1;
			pCurrentBTreeNode->elementCount = pivotIndex;

			pParentStackNode = popLS(pStack);
			if (pParentStackNode != NULL) {
				insertNodeElementBT(pParentStackNode->data, pivotElement, pNewBTreeNode);
			}
			else {
				// 트리 전체 Depth가 1증가.
				pBTree->pRootNode = createBTreeNode(pivotElement);
				pBTree->pRootNode->pChildren[0] = pCurrentBTreeNode;
				pBTree->pRootNode->pChildren[1] = pNewBTreeNode;
			}
		}

		if (pCurrentStackNode != NULL) {
			free(pCurrentStackNode);
		}
		pCurrentStackNode = pParentStackNode;
		pParentStackNode = NULL;
	}

	if (pCurrentStackNode != NULL) free(pCurrentStackNode);
	if (pParentStackNode != NULL) free(pParentStackNode);
}


BTreeNode* createBTreeNode(BTreeNodeData element)
{
	BTreeNode* pReturn = NULL;

	pReturn = (BTreeNode *)malloc(sizeof(BTreeNode));
	if (pReturn != NULL) {	// 메모리 할당 성공 검증
		// 데이터 초기화.
		memset(pReturn, 0, sizeof(BTreeNode));
		pReturn->element[0] = element;
		pReturn->elementCount = 1;
	}
	else {
		printf("Error, malloc() in createBTreeNode()\n");
	}

	return pReturn;
}

void insertNodeElementBT(BTreeNode* pCurrentNode,
	BTreeNodeData element,
	BTreeNode* pRChildNode) {
	int i = 0;
	for (i = pCurrentNode->elementCount - 1; i >= 0; i--) {
		int tempKey = pCurrentNode->element[i].key;
		if (element.key < tempKey) {
			pCurrentNode->element[i + 1] = pCurrentNode->element[i];
			pCurrentNode->pChildren[i + 2] = pCurrentNode->pChildren[i + 1];
		}
		else {
			break;
		}
	}
	pCurrentNode->element[i + 1] = element;
	pCurrentNode->pChildren[i + 2] = pRChildNode;
	pCurrentNode->elementCount++;
}