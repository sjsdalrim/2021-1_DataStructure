/*
자료구조 04분반 소프트웨어학과 20201672 서준상

Implement the BSTIterator class that
represents an iterator over the
in-order traversal of a binary search tree (BST)
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*트리 구조체*/
typedef struct TreeNode {
	struct TreeNode* left;
	int val;
	struct TreeNode* right;
} TreeNode;

/*Tree Node 생성*/  
TreeNode* TreeNodeCreate(int num) {
	TreeNode *newNode = (TreeNode *) malloc ( sizeof(TreeNode) );
	newNode->val = num;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

/*in-order traversal*/
void inorder(struct TreeNode* root, int** value, int* num){
    if (root == NULL) {
        return;
	}
	inorder(root->left, value, num);
	value[0][0] = root->val;
	*value = *value + 1;
	*num = *num + 1;
	inorder(root->right, value, num);
	return;
}

/*BSTIterator 구조체*/
typedef struct BSTIterator {
	int* value;
	int index;
	int num;
} BSTIterator;

/*입력된 Node를 root로 하는 BSTIterator Tree 생성*/
BSTIterator* bSTIteratorCreate(struct TreeNode* rootNode) {
    int** value = malloc( sizeof(int*) );
    value[0] = malloc( sizeof(int) * 1000000 );
    
    int * start = value[0];
    int num = 0;
    inorder(rootNode, value, &num);
    
    BSTIterator * root = malloc(sizeof(BSTIterator));
    root->value = start;
    root->index = 0;
    root->num = num;
    
    return root;
}


int bSTIteratorNext(BSTIterator* obj) {
    int val = obj->value[obj->index];
    obj->index++;
    return val;
}


bool bSTIteratorHasNext(BSTIterator* obj) {
    if (obj->index < obj->num) {
        return true;
	} else {
		return false;
	}
}


void bSTIteratorFree(BSTIterator* obj) {
    free(obj->value);
    free(obj);
}


int main() {
	TreeNode *root = TreeNodeCreate(7);
	root->left = TreeNodeCreate(3);
	root->right = TreeNodeCreate(15);
	root->right->left = TreeNodeCreate(9);
	root->right->right = TreeNodeCreate(20);
	
	BSTIterator *obj = bSTIteratorCreate(root);
	
	int sort1 = bSTIteratorNext(obj);
	printf(" %d\n", sort1);
	
	int sort2 = bSTIteratorNext(obj);
	printf(" %d\n", sort2);
	
	bool TorF1 = bSTIteratorHasNext(obj);
	if (TorF1 == true) {
		printf(" true\n");
	} else {
		printf(" false\n");
	}
	
	int sort3 = bSTIteratorNext(obj);
	printf(" %d\n", sort3);
	
	bool TorF2 = bSTIteratorHasNext(obj);
	if (TorF2 == true) {
		printf(" true\n");
	} else {
		printf(" false\n");
	}
	
	int sort4 = bSTIteratorNext(obj);
	printf(" %d\n", sort4);
	
	bool TorF3 = bSTIteratorHasNext(obj);
	if (TorF3 == true) {
		printf(" true\n");
	} else {
		printf(" false\n");
	}
	
	int sort5 = bSTIteratorNext(obj);
	printf(" %d\n", sort5);
	
	bool TorF4 = bSTIteratorHasNext(obj);
	if (TorF4 == true) {
		printf(" true\n");
	} else {
		printf(" false\n");
	}
	
	return 0;
}
