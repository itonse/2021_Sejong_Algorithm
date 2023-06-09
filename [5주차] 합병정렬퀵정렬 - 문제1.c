#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

int n, n2;

typedef struct node {   // 노드 구조 정의
	int data;
	struct node* next;
}Node;

Node* getNode(void) {
	Node* L;

	L = (Node*)malloc(sizeof(Node));

	return L;
}

void insertNode(Node* L, int x) {
	Node* newNode;
	Node* temp;

	temp = L;

	newNode = getNode();
	newNode->next = NULL;
	newNode->data = x;

	if (L->data == 0)
		L->data = x;
	else {
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = newNode;
	}
}

Node* partition(Node* L, int k) { // 리스트의 뒷부분
	int i;
	Node* copyL, * L2 = NULL;

	copyL = L;
	for (i = 0; i < k - 1; i++)
		copyL = copyL->next;

	L2 = copyL->next;
	copyL->next = NULL;

	return L2;
}

Node* merge(Node* L1, Node* L2) {
	Node* a, * b, * temp, * L3;

	a = L1;
	b = L2;

	if (a->data <= b->data) {
		L3 = a;
		temp = a;
		a = a->next;
	}
	else {
		L3 = b;
		temp = b;
		b = b->next;
	}

	while ((a != NULL && b != NULL)) {
		if (a->data <= b->data) {
			temp->next = a;

			a = a->next;
			temp = temp->next;
		}
		else {
			temp->next = b;

			b = b->next;
			temp = temp->next;
		}
	}
	while (b != NULL) {
		temp->next = b;
		b = b->next;
		temp = temp->next;
	}
	while (a != NULL) {
		temp->next = a;
		a = a->next;
		temp = temp->next;
	}

	return L3;
}

Node* mergeSort(Node* L) {
	Node* L2;

	L2 = NULL;
	if (L->next != NULL) {
		L2 = partition(L, n2 / 2);
		n2 = n2 / 2 + 1;

		L = mergeSort(L);
		L2 = mergeSort(L2);
		L = merge(L, L2);
	}

	return L;
}

int main() {
	int i, x;
	Node* L;

	scanf("%d", &n);
	n2 = n;

	L = getNode();
	L->next = NULL;
	L->data = 0;

	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		insertNode(L, x);
	}

	L = mergeSort(L);

	while (L != NULL) {
		printf(" %d", L->data);
		L = L->next;
	}

	free(L);
	return 0;
}