#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100] = { 0 };
int n;

void buildHeap(i);
void downHeap(int i);
void printHeap();



void buildHeap(i) {
	for (i = n / 2; i >= 1; i--) {
		downHeap(i);
	}
}

void downHeap(int i) {
	int big, temp;

	if ((2 * i > n) && (2 * i + 1 > n))
		return;

	big = 2 * i;

	if (H[i * 2 + 1] > H[i * 2]) {
		big = i * 2 + 1;
	}

	if (H[i] >= H[big])
		return;

	temp = H[i];
	H[i] = H[big];
	H[big] = temp;

	downHeap(big);
}

void printHeap() {
	int i;

	i = 1;
	while (i <= n) {
		printf(" %d", H[i]);
		i++;
	}
	printf("\n");
}

int main() {
	int i;

	scanf("%d", &n);

	for (i = 1; i <= n; i++)
		scanf("%d", &H[i]);

	buildHeap();
	printHeap();

	return 0;
}

