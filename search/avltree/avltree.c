#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avldef.h"
#include "avllinkedstack.h"
#include "avltree.h"

// 트리의 생성
AVLTree* createAVLTree()
{
	AVLTree *pReturn = NULL;

	pReturn = (AVLTree *)malloc(sizeof(AVLTree));
	if (pReturn != NULL) {		// 메모리 할당 성공 검증
		// 데이터 초기화
		memset(pReturn, 0, sizeof(AVLTree));
	}
	else {
		printf("오류, malloc() in createAVLTree()\n");
		return NULL;
	}

	return pReturn;
}

// (반복적) 탐색.
AVLTreeNode* searchAVL(AVLTree* pAVLTree, int key) {
	AVLTreeNode* pReturn = NULL;
	AVLTreeNode* pNode = NULL;

	if (pAVLTree == NULL) {
		return NULL;
	}

	pNode = pAVLTree->pRootNode;
	if (pNode == NULL) {
		return NULL;
	}

	while (pNode != NULL) {
		if (key == pNode->data.key) {
			pReturn = pNode;
			break;
		}
		else if (key < pNode->data.key) {
			pNode = pNode->pLeftChild;
		}
		else {
			pNode = pNode->pRightChild;
		}
	}

	return pReturn;
}

// 새로운 노드 삽입.
int insertNodeAVL(AVLTree* pAVLTree, AVLTreeNodeData element) {
	int ret = TRUE;
	AVLTreeNode* pParentNode = NULL;
	AVLTreeNode* pNewNode = NULL;
	LinkedStack* pStack = NULL;

	if (pAVLTree == NULL) {
		ret = FALSE;
		return ret;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		ret = FALSE;
		return ret;
	}

	pParentNode = pAVLTree->pRootNode;
	while (pParentNode != NULL) {
		pushAVLTreeNode(pStack, pParentNode);

		if (element.key == pParentNode->data.key) {
			printf("오류, 중복된 키[%d]가 존재합니다, insertNodeAVL()\n", element.key);
			ret = FALSE;
			return ret;
		}
		else if (element.key < pParentNode->data.key) {
			if (pParentNode->pLeftChild == NULL) {
				break;
			}
			else {
				pParentNode = pParentNode->pLeftChild;
			}
		}
		else {
			if (pParentNode->pRightChild == NULL) {
				break;
			}
			else {
				pParentNode = pParentNode->pRightChild;
			}
		}
	}

	pNewNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
	if (pNewNode != NULL) { // 메모리 할당 성공 검증
		// 데이터 초기화
		memset(pNewNode, 0, sizeof(AVLTreeNode));
		pNewNode->data = element;
		pNewNode->height = 1;
	}
	else {
		printf("오류, malloc() in insertNodeAVL()\n");
		deleteLinkedStack(pStack);
		return FALSE;
	}

	if (pParentNode == NULL) {
		pAVLTree->pRootNode = pNewNode;
	}
	else {
		if (pNewNode->data.key < pParentNode->data.key) {
			pParentNode->pLeftChild = pNewNode;
		}
		else {
			pParentNode->pRightChild = pNewNode;
		}
	}
	ret = TRUE;

	balanceAVLTree(pAVLTree, pStack);

	deleteLinkedStack(pStack);

	return ret;
}