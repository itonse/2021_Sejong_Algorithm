#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

void SelectionSort(int a[], int size) {
	int i, j, k, max, temp;

	for (i = size - 1; i >= 0; i--) {
		max = i;
		for (j = i - 1; j >= 0; j--) {
			if (a[j] > a[max]) {
				max = j;
			}
		}

		temp = a[i];
		a[i] = a[max];
		a[max] = temp;
	}

	for (i = 0; i < size; i++)
		printf(" %d", a[i]);
}

void main(void) {
	int n, i;
	int* list;

	scanf("%d", &n);

	list = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}

	SelectionSort(list, n);
}

