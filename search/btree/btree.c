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

		for (i = 0; i < pCurrentNode->elementcount; i++) {
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