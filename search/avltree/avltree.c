#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avldef.h"
#include "avllinkedstack.h"
#include "avltree.h"

// Ʈ���� ����
AVLTree* createAVLTree()
{
	AVLTree *pReturn = NULL;

	pReturn = (AVLTree *)malloc(sizeof(AVLTree));
	if (pReturn != NULL) {		// �޸� �Ҵ� ���� ����
		// ������ �ʱ�ȭ
		memset(pReturn, 0, sizeof(AVLTree));
	}
	else {
		printf("����, malloc() in createAVLTree()\n");
		return NULL;
	}

	return pReturn;
}

// (�ݺ���) Ž��.
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

// ���ο� ��� ����.
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
			printf("����, �ߺ��� Ű[%d]�� �����մϴ�, insertNodeAVL()\n", element.key);
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
	if (pNewNode != NULL) { // �޸� �Ҵ� ���� ����
		// ������ �ʱ�ȭ
		memset(pNewNode, 0, sizeof(AVLTreeNode));
		pNewNode->data = element;
		pNewNode->height = 1;
	}
	else {
		printf("����, malloc() in insertNodeAVL()\n");
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