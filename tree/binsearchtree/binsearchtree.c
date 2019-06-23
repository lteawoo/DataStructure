#include <stdio.h>
#include <stdlib.h>
#include "binsearchtree.h"

BinSearchTree* createBinSearchTree()
{
	BinSearchTree *pReturn = NULL;
	pReturn = (BinSearchTree *)malloc(sizeof(BinSearchTree));
	if (pReturn != NULL) {
		pReturn->pRootNode = NULL;
	}
	else {
		printf("오류, 메모리 할당, createBinSearchTree()\n");
	}

	return pReturn;
}

int insertElementBST(BinSearchTree* pBinSearchTree, BinSearchTreeNode element)
{
	int ret = TRUE;
	BinSearchTreeNode* pParentNode = NULL;
	BinSearchTreeNode* pNewNode = NULL;
	if (pBinSearchTree == NULL) {
		ret = FALSE;
		return ret;
	}
	pParentNode = pBinSearchTree->pRootNode;

	while (pParentNode != NULL) {
		if (element.key == pParentNode->key) {
			printf("오류, 중복된 키-[%d],insertElementBST()\n", element.key);
			ret = FALSE;
			return ret;
		}
		else if (element.key < pParentNode->key) {
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
	pNewNode = (BinSearchTreeNode *)malloc(sizeof(BinSearchTreeNode));
	if (pNewNode != NULL) {
		*pNewNode = element;
		pNewNode->pLeftChild = NULL;
		pNewNode->pRightChild = NULL;
		if (pParentNode == NULL) {
			pBinSearchTree->pRootNode = pNewNode;
		}
		else {
			if (pNewNode->key < pParentNode->key) {
				pParentNode->pLeftChild = pNewNode;
			}
			else {
				pParentNode->pRightChild = pNewNode;
			}
		}
		ret = TRUE;
	}
	else {
		printf("오류, 메모리 할당, insertElementBST()\n");
		ret = FALSE;
	}
	return ret;
}

int deleteElementBST(BinSearchTree* pBinSearchTree, int key) {
	int ret = TRUE;
	BinSearchTreeNode* pDelNode = NULL, * pParentNode = NULL;
	BinSearchTreeNode* pPredecessor = NULL, * pSuccessor = NULL;
	BinSearchTreeNode* pChildNode = NULL;

	if (pBinSearchTree == NULL) {
		ret = FALSE;
		return ret;
	}
	pParentNode = NULL;
	pDelNode = pBinSearchTree->pRootNode;
	while (pDelNode != NULL) {
		if (key == pDelNode->key) {
			break;
		}
		pParentNode = pDelNode;
		if (key < pDelNode->key) {
			pDelNode = pDelNode->pLeftChild;
		}
		else {
			pDelNode = pDelNode->pRightChild;
		}
	}
	if (pDelNode == NULL) {
		printf("오류, 존재하지 않는 키-[%d],deleteElementBST()\n", key);
		ret = FALSE;
		return ret;
	}
	if (pDelNode->pLeftChild == NULL && pDelNode->pRightChild == NULL) {
		if (pParentNode != NULL) {
			if (pParentNode->pLeftChild == pDelNode) {
				pParentNode->pLeftChild = NULL;
			}
			else {
				pParentNode->pRightChild = NULL;
			}
		}
		else {
			pBinSearchTree->pRootNode = NULL;
		}
	}

}