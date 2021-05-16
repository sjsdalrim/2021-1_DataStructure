/*
자료구조 04분반 소프트웨어학과 20201672 서준상

implementation of the doubly linked list

val = the value of the current node
next = a pointer / reference to the next node
prev = the previous node in the linked list
# all nodes in the linked list are 0-indexed
*/

#include<stdio.h>
#include<stdlib.h>


typedef struct MyLinkedList {
	int val;
	struct MyLinkedList * prev;
	struct MyLinkedList * next;
} MyLinkedList;


/* */
MyLinkedList* myLinkedListCreate() {
	
	MyLinkedList* head = (MyLinkedList *) malloc ( sizeof(MyLinkedList) );
    head->prev = NULL;
	head->next = NULL; // 헤드만 생성
	
	return head;
	
}


/* */
int myLinkedListGet( MyLinkedList* obj, int index ) {
	
	int i = 0;
	MyLinkedList* nowNode = obj->next;
	if (index < 0) {
		return -1;
	}
	
	while ( (nowNode != NULL) && (i < index) ) {
		nowNode = nowNode->next;
		i = i + 1;
	}
	
	if ( (nowNode == NULL) || (i > index) ) {
		return -1;
	}
	
	return nowNode->val;
	
}


/* */
void myLinkedListAddAtHead( MyLinkedList* obj, int val ) {
	
	MyLinkedList* newHead = (MyLinkedList *) malloc ( sizeof(MyLinkedList) );
	newHead->val = val;
	
    newHead->prev = obj;
	newHead->next = obj->next;
	obj->next = newHead;       // 헤드 뒤 0번 자리에 노드를 저장함 
	
}


/* */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
	
	MyLinkedList* nowNode = obj;
	
	MyLinkedList* newTail = (MyLinkedList *) malloc ( sizeof(MyLinkedList) );
	newTail->val = val;
	
	while (nowNode->next) {
		nowNode = nowNode->next;
	}
	
	nowNode->next = newTail;
    newTail->prev = nowNode;
	newTail->next = NULL;
}


/* */
void myLinkedListAddAtIndex( MyLinkedList* obj, int index, int val ) {
	
	MyLinkedList *nowNode;
	MyLinkedList *newNode = (MyLinkedList *) malloc ( sizeof(MyLinkedList) );
	
	newNode->val = val;
	
	int i = 0;
	if (index == 0) {
		newNode->next = obj->next;
		obj->next = newNode;
		
	} else {
		nowNode = obj;
		while ( (nowNode != NULL) && i < index) {
			nowNode = nowNode->next;
			i = i + 1;
		}
		
		if ( (nowNode == NULL) || i > index) {
			return;
		}
		
		newNode->next = nowNode->next;
        newNode->prev = nowNode;
		nowNode->next = newNode;
	}
	
}


/* */
void myLinkedListDeleteAtIndex( MyLinkedList* obj, int index ) {
	
	MyLinkedList* nowNode = obj;
	
	if (index < 0) {
		return;
	}
	
	int i = 0;
	while ( (nowNode->next != NULL) && (i < index) ) {
		nowNode = nowNode->next;
		i = i + 1;
	}
	
	if ( (nowNode->next == NULL) || i > index) {
		return;
	}
	
	MyLinkedList* nextNode = nowNode->next;
	
	nowNode->next = nextNode->next;
    if ( nextNode->next != NULL ) {
        nowNode = nextNode->next;
        nowNode->prev = nextNode->prev;
    }
	free(nextNode);
	
}


/* */
void myLinkedListFree( MyLinkedList* obj ) {
	MyLinkedList* nowNode = obj->next;
	MyLinkedList* nextNode;
	
	while ( nowNode != NULL ) {
		nextNode = nowNode->next;
		free(nowNode);
		nowNode = nextNode;
	}
	
    obj->prev = NULL;
	obj->next = NULL;
	
}


/* */
int main() {
	
	MyLinkedList * obj = myLinkedListCreate();
	
	myLinkedListAddAtHead(obj, 1);
	
	myLinkedListAddAtTail(obj, 3);
	
	myLinkedListAddAtIndex(obj, 1, 2);      //linked list becomes 1->2->3
	int value1 = myLinkedListGet(obj, 1);   //return 2
	printf(" %d\n", value1);
	
	myLinkedListDeleteAtIndex(obj, 1);      //linked list becomes 1->3
	int value2 =  myLinkedListGet(obj, 1);  //return 3
	printf(" %d\n", value2);
	
	myLinkedListFree(obj);
	myLinkedListAddAtHead(obj, 7);
	int value3 = myLinkedListGet(obj, 1);
	//Free 한 뒤, Head만 추가했으니 0번에만 값이 존재해야 한다. 1번은 NULL(-1로 출력)
	printf(" %d\n", value3);
	
	return 0;
}
