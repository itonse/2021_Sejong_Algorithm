#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

void insertionSort(int a[], int size) {
	int i, j, k, temp;

	for (i = 1; i < size; i++) {
		j = i;
		temp = a[i];
		while ((j >= 1) && (a[j - 1] > temp)) {
			a[j] = a[j - 1];
			j = j - 1;
		}
		a[j] = temp;
	}

	for (k = 0; k < size; k++) {
		printf(" %d", a[k]);
	}
}

void main(void) {
	int n, i;
	int* list;

	scanf("%d", &n);

	list = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}

	insertionSort(list, n);
}

