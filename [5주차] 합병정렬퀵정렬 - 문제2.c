#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void swap(int* a, int* b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
int findPivot(int* L, int l, int r) {
	int pivot[3];
	int i, j, temp;

	for (i = 0; i < 3; i++)
		pivot[i] = (rand() % (r - l + 1)) + l;

	for (i = 0; i < 3; i++) {
		for (j = i; j < 3; j++) {
			if (L[pivot[i]] > L[pivot[j]]) {
				temp = pivot[i];
				pivot[i] = pivot[j];
				pivot[j] = temp;
			}

		}
	}

	return pivot[1];
}
int inPlacePartition(int* L, int l, int r, int k) {
	int p, i, j;

	p = L[k]; // ÇÇ¹þ °ª
	swap(&L[k], &L[r]);

	i = l;
	j = r - 1;

	while (i <= j) {
		while (i <= j && L[i] <= p) {
			i++;
		}
		while (i <= j && L[j] >= p) {
			j--;
		}
		if (i < j)
			swap(&L[i], &L[j]);
	}
	swap(&L[i], &L[r]);

	return i;
}
void inPlaceQuickSort(int* L, int l, int r) {
	int k, a, b;

	if (l >= r)
		return;

	k = findPivot(L, l, r);
	a = inPlacePartition(L, l, r, k);

	inPlaceQuickSort(L, l, a - 1);
	inPlaceQuickSort(L, a + 1, r);
}

int main() {
	int n, i;
	int* L;

	scanf("%d", &n);

	L = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
		scanf("%d", &L[i]);

	srand(time(NULL));
	inPlaceQuickSort(L, 0, n - 1);

	for (i = 0; i < n; i++)
		printf(" %d", L[i]);

	free(L);
	return 0;
}