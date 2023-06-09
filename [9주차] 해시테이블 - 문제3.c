#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

int hx(int x, int M) {
	return x % M;
}

int hx2(int x, int q) {
	return (q - (x % q));
}

void initBucketArray(int* A, int M) {
	int i;

	for (i = 0; i < M; i++)
		A[i] = 0;
}

int insertItem(int* A, int x, int M, int q) {
	int addr, i = 0;
	int tmp;

	addr = hx(x, M);
	tmp = addr;

	while (A[addr] != 0) {
		i++;
		printf("C");
		addr = hx(tmp + i * hx2(x, q), M);
	}
	A[addr] = x;

	return addr;
}

int findElement(int* A, int x, int M) {
	int exist = 0, i;

	for (i = 0; i < M; i++) {
		if (A[i] == x) {
			exist = 1;
			break;
		}
	}

	if (exist == 1)
		return i;
	else
		return -1;
}

void printHashtable(int* A, int M) {
	int i;

	for (i = 0; i < M; i++)
		printf(" %d", A[i]);
	printf("\n");
}

int main() {
	int M, n, q, x, addr, result;
	int* A;
	char order = ' ';

	scanf("%d %d %d", &M, &n, &q);   // n < M
	getchar();

	A = (int*)malloc(M * sizeof(int));

	initBucketArray(A, M);

	while (order != 'e') {
		scanf("%c", &order);
		switch (order) {
		case 'i':
			scanf("%d", &x);  // 6자리 or 8자리
			addr = insertItem(A, x, M, q);
			printf("%d\n", addr);
			break;

		case 's':
			scanf("%d", &x);
			result = findElement(A, x, M);
			if (result == -1)
				printf("%d\n", result);
			else {
				printf("%d %d\n", result, x);
			}
			break;

		case 'p':
		case 'e':
			printHashtable(A, M);
		}
	}

	return 0;
}