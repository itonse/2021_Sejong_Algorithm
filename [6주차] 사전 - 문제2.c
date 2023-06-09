#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int n;
int* arr;

int findElement(int k) {
	int l = 0, r = n - 1, mid, x;

	x = n;
	while (l <= r) {
		mid = (l + r) / 2;

		if (arr[mid] == k) {
			x = mid;
			break;
		}
		else if (k < arr[mid]) {
			if ((arr[mid - 1] < k && mid > 0) || l == mid) {
				x = mid;
				break;
			}
			r = mid - 1;
		}
		else {  // arr[mid] < k
			l = mid + 1;
		}
	}
	return x;
}
int main() {
	int k, x, i;

	scanf("%d %d", &n, &k);

	arr = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
		scanf("%d", arr + i);

	x = findElement(k);
	printf(" %d", x);

	return 0;
}