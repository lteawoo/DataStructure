#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btreedef.h"
#include "btlinkedstack.h"
#include "btree.h"

// Ʈ���� ����
BTree* createBTree()
{
	BTree *pReturn = NULL;

	pReturn = (BTree*)malloc(sizeof(BTree));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(BTree));
	}
	else {
		printf("����, �޸� �Ҵ� in createBTree()\n");
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