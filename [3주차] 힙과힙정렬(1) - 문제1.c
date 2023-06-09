#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100] = { 0 };
#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100] = { 0 };
int n = 0;

void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

void insertItem(int key) {
	n++;
	H[n] = key;
	upHeap(n);
}

int removeMax() {
	int key;

	key = H[1];
	H[1] = H[n];
	n--;

	downHeap(1);

	return key;
}

void upHeap(int i) {
	int temp;

	if (i == 1) return;
	else if (H[i] <= H[i / 2]) return;
	else {
		temp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = temp;
	}

	upHeap(i / 2);
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
	int i = 1;

	while (i <= n) {
		printf(" %d", H[i]);
		i++;
	}
	printf("\n");
}

int main() {
	char ch;
	int key;

	while (1) {
		scanf("%c", &ch);

		if (ch == 'q')
			break;
		else if (ch == 'i') {
			scanf("%d", &key);

			insertItem(key);
			printf("0\n");
		}
		else if (ch == 'd') {
			printf("%d\n", removeMax());
		}
		else if (ch == 'p') {
			printHeap();
		}
	}

	return 0;
}

