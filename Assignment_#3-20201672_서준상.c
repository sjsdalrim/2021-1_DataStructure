#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

# define MAX_WORD_LENGTH 20
# define MAX_MEAN_LENGTH 200

typedef struct element {
	char word[MAX_WORD_LENGTH];
	char mean[MAX_MEAN_LENGTH];
} element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;


TreeNode* searchBST(TreeNode* root, element key) {
	TreeNode* p;
	int compare;
	p = root;
	
	while (p != NULL) {
		compare = strcmp(key.word, p->key.word);
		
		if (compare < 0) {
			p = p->left;
		} else if (compare > 0) {
			p = p->right;
		} else {
			printf("\n찾은 단어 : %s\n", p->key.word);
			return p;
		}
		
	}
	
	return p;
}


TreeNode* insertKey(TreeNode* p, element key) {
	TreeNode* newNode;
	int compare;
	
	if (p == NULL) {
		newNode = (TreeNode*)malloc(sizeof(TreeNode));
		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	} else {
		compare = strcmp(key.word, p->key.word);
		
		if (compare < 0) {
			p->left = insertKey(p->left, key);
			return p;
		} else if (compare > 0) {
			p->right = insertKey(p->right, key);
			return p;
		} else {
			printf("이미 같은 단어가 있습니다\n");
			return p;
		}
	}
	
}


void insert(TreeNode** root, element key) {
	*root = insertKey(*root, key);
}


void deleteNode(TreeNode* root, element key) {
	TreeNode* parent, * p, * succ, * succ_parent;
	TreeNode* child;
	
	parent = NULL;
	p = root;
	
	while ( (p != NULL) && (strcmp(p->key.word, key.word) != 0) ) {
		parent = p;
		
		if (strcmp(key.word, p->key.word) < 0) {
			p = p->left;
		} else {
			p = p->right;
		}
	}
	
	succ_parent = p;
	if (p == NULL) {
		printf("찾는 키가 이진트리에 없습니다\n");
		return;
	}
	
	if ( (p->left == NULL) && (p->right == NULL) ) {
		
		if (parent != NULL) {
			
			if (parent->left == p) {
				parent->left = NULL;
			} else {
				parent->right = NULL;
			}
			
		} else {
			root = NULL;
		}
		
	} else if ( (p->left == NULL) || (p->right == NULL) ) {
		
		if (p->left != NULL) {
			child = p->left;
		} else {
			child = p->right;
		}
		
		if (parent != NULL) {
			
			if (parent->left == p) {
				parent->left = child;
			} else {
				parent->right = child;
			}
			
		} else {
			root = child;
		}
		
	} else {
		succ = p->right;
		
		while (succ->left != NULL) {
			succ_parent = succ;
			succ = succ->left;
		}
		
		if (succ_parent->left == succ) {
			succ_parent->left = succ->right;
		} else {
			succ_parent->right = succ->right;
		}
		
		p->key = succ->key;
		p = succ;
	}
	
	free(p);
}


int getHeight(TreeNode* root) {
	
	int height = 0;
	if (root != NULL) {
		if ( getHeight(root->left) < getHeight(root->right) ) {
			height = getHeight(root->right) + 1;
		} else {
			height = getHeight(root->left) + 1;
		}
	}
	
	return height;
}


int getNumberofNode(TreeNode* root) {
	int count = 0;
	
	if (root != NULL) {
		if ( (root->left == NULL) && (root->right == NULL) ) {
			return 1;
		} else {
			return getNumberofNode(root->left) + getNumberofNode(root->right) + 1;
		}
	}
	
	return 0;
}


void menu() {
	printf("\n*-------------------------*\n");
	printf("\t 1 : 입력\n");
	printf("\t 2 : 삭제\n");
	printf("\t 3 : 검색\n");
	printf("\t 4 : 출력\n");
	printf("\t 5 : 종료\n");
	printf("\t 6 : Print height of Tree\n");
	printf("\t 7 : Output the total number of nodes\n");
	printf("\t 8 : Delete all nodes\n");
	printf("*-------------------------*\n");
}


void inorderDisplay(TreeNode* root) {
	
	if (root) {
		inorderDisplay(root->left);
		printf("%s : %s\n", root->key.word, root->key.mean);
		inorderDisplay(root->right);
	}
	
}


void main() {
	
	char choice;
	element e;
	TreeNode* root = NULL;
	TreeNode* temp;
	
	do {
		menu();
		choice = getchar();getchar();
		
		switch (choice - '0') {
			case 1:
				printf("\n[단어 입력] 단어를 입력하세요 : ");
				gets(e.word);
				printf("[단어 입력] 단어 뜻을 입력하세요 : ");
				gets(e.mean);
				insert(&root, e);
				break;
			case 2:
				printf("\n[단어 삭제] 삭제할 단어 : ");
				gets(e.word);
				deleteNode(root, e);
				break;
			case 3:
				printf("\n[단어 검색] 검색할 단어 : ");
				gets(e.word);
				
				temp = searchBST(root, e);
				if (temp != NULL) {
					printf("단어 뜻 : %s\n", temp->key.mean);
				} else {
					printf("\n사전에 없는 단어입니다\n");
				}
				break;
			case 4:
				printf("\t [사전 출력]\n\n");
				inorderDisplay(root);
				printf("\n\t [사전 끝]\n");
				break;
			case 6:
				printf("\nHeight of Tree : %d\n", getHeight(root));
				break;
			case 7:
				printf("\nTotal number of nodes : %d\n", getNumberofNode(root));
				break;
			case 8:
				root = NULL;
				printf("\nComplete deleting all nodes in Tree\n");
				break;
		}
	} while ( (choice - '0') != 5 );
	
}

