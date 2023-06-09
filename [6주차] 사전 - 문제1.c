#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int n;
int* arr;

int findElement(int k, int l, int r) {
	int mid;

	mid = (l + r) / 2;

	if (r == mid && arr[r] < k)  // k�� �迭���� ��� ���Ұ����� ū ���
		return mid;
	if (l > r)  // ������ �Ͼ ���
		return -1;

	if (arr[mid] == k)  // arr[mid] ���� k�� ��ġ�ϴ� ���
		return mid;
	else if (k < arr[mid] && arr[mid - 1] < k && mid > 0)  // ���� �迭 ���� ���� ������, ��ġ�ϴ� ���Ұ� ������ 
		return mid - 1;
	else if (arr[mid] > k)
		return findElement(k, l, mid - 1); // l, r ���� �ٽ� �����ؼ� ���
	else
		return findElement(k, mid + 1, r); // l, r ���� �ٽ� �����ؼ� ���
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