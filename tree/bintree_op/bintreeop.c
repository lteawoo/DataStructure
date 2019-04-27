#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"
#include "bintreeop.h"

BinTree* copyBinTree(BinTree* pSource)
{
	BinTree* pReturn = NULL;
	if (pSource != NULL) {
		pReturn = (BinTree *)malloc(sizeof(BinTree));
		if (pReturn != NULL) {
			pReturn->pRootNode = copyBinTreeNode(pSource->pRootNode);
		}
		else {
			printf("오류, 메모리 할당, copyBinTree()\n");
		}
	}
	return pReturn;
}

BinTreeNode* copyBinTreeNode(BinTreeNode* pSourceNode) {
	BinTreeNode* pReturn = NULL;
	if (pSourceNode != NULL) {
		pReturn = (BinTreeNode *)malloc(sizeof(BinTreeNode));
		if (pReturn != NULL) {
			*pReturn = *pSourceNode;
			pReturn->pLeftChild = copyBinTreeNode(getLeftChildNodeBT(pSourceNode));
			pReturn->pRightChild = copyBinTreeNode(getRightChildNodeBT(pSourceNode));
		}
		else {
			printf("오류, 메모리 할당, copyBinTreeNode()\n");
		}
	}
}

int equalBinTree(BinTree* pFirst, BinTree* pSecond)
{
	int ret = FALSE;

	if (pFirst == NULL && pSecond == NULL) {
		ret = TRUE;
	}
	else if (pFirst != NULL && pSecond != NULL && equalBinTreeNode(pFirst->pRootNode, pSecond->pRootNode) == TRUE) {
		ret = TRUE;
	}

	return ret;
}

int equalBinTreeNode(BinTreeNode* pFirst, BinTreeNode *pSecond)
{
	int ret = FALSE;

	if (pFirst == NULL && pSecond == NULL) {
		ret = TRUE;
	}
	else if (pFirst != NULL && pSecond != NULL
		&& pFirst->data == pSecond->data
		&& equalBinTreeNode(pFirst->pLeftChild, pSecond->pLeftChild) == TRUE
		&& equalBinTreeNode(pFirst->pRightChild, pSecond->pRightChild) == TRUE) {
		ret = TRUE;
	}
	
	return ret;
}

int getNodeCountBT(BinTree* pSource)
{
	int ret = 0;
	if (pSource != NULL) {
		ret = getNodeCountBTNode(pSource->pRootNode);
	}
}

int getNodeCountBTNode(BinTreeNode* pSource)
{
	int ret = 0;
	if (pSource != NULL) {
		ret = getNodeCountBTNode(pSource->pLeftChild)
			+ getNodeCountBTNode(pSource->pRightChild) + 1;
	}

	return ret;
}

int getLeafNodeCountBT(BinTree* pSource)
{
	int ret = 0;
	if (pSource != NULL) {
		ret = getLeafNodeCountBTNode(pSource->pRootNode);
	}

	return ret;
}

int getLeafNodeCountBTNode(BinTreeNode* pSource)
{
	int ret = 0;
	if (pSource != NULL) {
		if (pSource->pLeftChild == NULL && pSource->pRightChild == NULL) {
			ret = 1;
		}
		else {
			ret = getLeafNodeCountBTNode(pSource->pLeftChild)
				+ getLeafNodeCountBTNode(pSource->pRightChild);
		}
	}

	return ret;
}