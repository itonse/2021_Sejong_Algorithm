#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

int hx(int x, int M) {
	return x % M;
}

void initBucketArray(int* A, int M) {
	int i;

	for (i = 0; i < M; i++)
		A[i] = 0;
}

int insertItem(int* A, int x, int M) {
	int addr;

	addr = hx(x, M);

	while (A[addr] != 0) {
		printf("C");
		addr = hx(addr + 1, M);
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

int main() {
	int M, n, x, addr, result;
	int* A;
	char order = ' ';

	scanf("%d %d", &M, &n);   // n < M
	getchar();

	A = (int*)malloc(M * sizeof(int));

	initBucketArray(A, M);

	while (order != 'e') {
		scanf("%c", &order);
		switch (order) {
		case 'i':
			scanf("%d", &x);  // 6자리 or 8자리
			addr = insertItem(A, x, M);
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
		}
	}

	return 0;
}