#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int key;
	struct node* next;
}Node;

int hx(int x, int M) {
	return (x % M);
}

void initBucketArray(Node* hash, int M) {
	int i;

	for (i = 0; i < M; i++) {
		(hash + i)->next = NULL;
	}
}

void insertItem(int k, int M, Node* hash) {
	int v;
	Node* newnode, * temp;

	v = hx(k, M);

	newnode = (Node*)malloc(sizeof(Node));
	newnode->next = NULL;
	newnode->key = k;

	temp = hash + v;
	if (temp->next == NULL) {
		temp->next = newnode;
	}
	else {
		newnode->next = temp->next;
		temp->next = newnode;
	}
}


int findElement(int k, int M, Node* hash) {
	int v, cnt = 1, flag = 0;
	Node* temp;

	v = hx(k, M);
	temp = hash + v;

	while (temp->next != NULL) {
		if (temp->next->key == k) {
			flag = 1;
			break;
		}
		temp = temp->next;
		++cnt;
	}

	if (flag == 1)
		return cnt;
	else
		return 0;
}

int removeElement(int k, int M, Node* hash) {
	int v, cnt = 1, flag = 0;
	Node* temp, * temp2 = NULL;

	v = hx(k, M);
	temp = hash + v;

	while (temp->next != NULL) {
		if (temp->next->key == k) {
			temp2 = temp->next;

			if (temp->next->next == NULL)
				temp->next = NULL;
			else
				temp->next = temp->next->next;
			flag = 1;
			break;
		}

		temp = temp->next;
		++cnt;
	}
	free(temp2);

	if (flag == 1)
		return cnt;
	else
		return 0;
}

void printHashTable(int M, Node* hash) {
	int i;
	Node* temp;

	for (i = 0; i < M; i++) {
		temp = hash + i;
		while (temp->next != NULL) {
			printf(" %d", temp->next->key);
			temp = temp->next;
		}
	}

}

int main() {
	int M, k, result, loop = 1;
	char choose;
	Node* hash;

	scanf("%d", &M);

	hash = (Node*)malloc(M * sizeof(Node));

	initBucketArray(hash, M);

	while (loop) {
		scanf("%c", &choose);

		switch (choose) {
		case 'i':
			scanf("%d", &k);

			insertItem(k, M, hash);
			break;

		case 's':
			scanf("%d", &k);

			result = findElement(k, M, hash);
			printf("%d\n", result);
			break;
		case 'd':
			scanf("%d", &k);

			result = removeElement(k, M, hash);
			printf("%d", result);
			break;
		case 'p':
			printHashTable(M, hash);
			printf("\n");
			break;
		case 'e':
			loop = 0;
			break;
		}
	}
	return 0;
}