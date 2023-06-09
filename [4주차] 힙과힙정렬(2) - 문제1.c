#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int H[100] = { 0 };   // 모든 원소를 0으로 초기화
int n, n2;

void printArray();
void downHeap(int i) {  // 최대힙 생성
	int temp, big;

	if (i * 2 > n) return;  // 자식노드가 없으면 종료

	big = i * 2;    // 자식노드가 있는 경우
	if (i * 2 + 1 <= n && H[i * 2] < H[i * 2 + 1])  //
		big = i * 2 + 1;

	if (H[i] > H[big])    // 부모노드인 H[i]의 값이 자식보다 크면 종료
		return;

	temp = H[i];
	H[i] = H[big];
	H[big] = temp;

	downHeap(big);    // 큰 자식 big의 인덱스를 대입하여 재귀함수 호출
}
void buildHeap() {
	int i;

	for (i = n / 2; i >= 1; i--)
		downHeap(i);
}
void inPlaceHeapSort() {  // 오름차순 정렬
	int i, temp;

	buildHeap();  // 힙 생성

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
	n2 = n;    // n2에 n값 저장(n2는 힙 정렬 할 때 사용)

	for (i = 1; i <= n; i++)
		scanf("%d", &H[i]);

	inPlaceHeapSort();
	printArray();

	return;
}