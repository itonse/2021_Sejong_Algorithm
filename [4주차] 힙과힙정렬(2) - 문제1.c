#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100] = { 0 };   // ��� ���Ҹ� 0���� �ʱ�ȭ
int n, n2;

void printArray();
void downHeap(int i) {  // �ִ��� ����
	int temp, big;

	if (i * 2 > n) return;  // �ڽĳ�尡 ������ ����

	big = i * 2;    // �ڽĳ�尡 �ִ� ���
	if (i * 2 + 1 <= n && H[i * 2] < H[i * 2 + 1])  //
		big = i * 2 + 1;

	if (H[i] > H[big])    // �θ����� H[i]�� ���� �ڽĺ��� ũ�� ����
		return;

	temp = H[i];
	H[i] = H[big];
	H[big] = temp;

	downHeap(big);    // ū �ڽ� big�� �ε����� �����Ͽ� ����Լ� ȣ��
}
void buildHeap() {
	int i;

	for (i = n / 2; i >= 1; i--)
		downHeap(i);
}
void inPlaceHeapSort() {  // �������� ����
	int i, temp;

	buildHeap();  // �� ����

	for (i = n; i >= 1; i--) {
		temp = H[1];
		H[1] = H[i];
		H[i] = temp;

		n--; // 
		downHeap(1);
	}
	n = n2;
}
void printArray() {
	int i;

	for (i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}
void main() {
	int i;

	scanf("%d", &n);
	n2 = n;    // n2�� n�� ����(n2�� �� ���� �� �� ���)

	for (i = 1; i <= n; i++)
		scanf("%d", &H[i]);

	inPlaceHeapSort();
	printArray();

	return;
}