#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int n;
int* arr;

int findElement(int k, int l, int r) {
	int mid;

	mid = (l + r) / 2;

	if (r == mid && arr[r] < k)  // k가 배열들의 모든 원소값보다 큰 경우
		return mid;
	if (l > r)  // 역전이 일어난 경우
		return -1;

	if (arr[mid] == k)  // arr[mid] 값과 k가 일치하는 경우
		return mid;
	else if (k < arr[mid] && arr[mid - 1] < k && mid > 0)  // 값이 배열 범위 내에 있지만, 일치하는 원소가 없을때 
		return mid - 1;
	else if (arr[mid] > k)
		return findElement(k, l, mid - 1); // l, r 값을 다시 설정해서 재귀
	else
		return findElement(k, mid + 1, r); // l, r 값을 다시 설정해서 재귀
}

int main() {
	int k, x, i;

	scanf("%d %d", &n, &k);

	arr = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
		scanf("%d", arr + i);

	x = findElement(k, 0, n - 1);
	printf(" %d", x);

	return 0;
}