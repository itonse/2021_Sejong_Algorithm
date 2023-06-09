#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

int mtr[7][7];

typedef struct vertex {  // 정점
	int name;
}Vertex;

typedef struct edge {  // 간선
	int weight;   // 가중치
	int vertex1;
	int vertex2;
}Edge;

typedef struct graph {    // 그래프 구조
	Vertex Vert[7];
	Edge Edg[21];
}Graph;

int edgesize = 0;  // 간선의 크기 전역변수 


void InsertEdge(Graph* gp, int v1, int v2, int w);
Graph makeGraph();
void PrintNodeWeight(Graph* gp, int a);
void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize);



void InsertEdge(Graph* gp, int v1, int v2, int w) {   // // 간선 추가    //		1 2 1
	int i, nameA, nameB;


	for (i = 0; i < edgesize; i++) {     // 간선 배열에서 빈 자리 찾기
		if (gp->Edg[i].weight == 0) {     // 빈 자리를 찾았으면 종료 (빈 자리는 간선삭제 연산으로 인해 배열의 중간자리 일 수도 있다.)
			break;
		}
	}

	if (i == edgesize) {
		edgesize++;
	}

	gp->Edg[i].vertex1 = v1;    // 간선배열에서 해당되는 인덱스에  v1, v2, 가중치 정보 입력
	gp->Edg[i].vertex2 = v2;
	gp->Edg[i].weight = w;

	// 인접행렬에 간선배열의 인덱스 입력하기  (중요!!)
	mtr[v1][v2] = i;
	if (v1 != v2)
		mtr[v2][v1] = i;
}

Graph makeGraph() {  // 정점, 간선, 인접리스트 생성   

	int i;
	Graph gp;

	for (i = 1; i <= 6; i++) {
		gp.Vert[i].name = i;       // 정점 값 입력
	}

	for (i = 0; i < 21; i++)
		gp.Edg[i].weight = 0;      // 가능한 모든 간선의 가중치의 값을 0으로 초기화

	//addEdge(Graph * gp, int v1, int v2, int w)
	InsertEdge(&gp, 1, 2, 1);
	InsertEdge(&gp, 1, 3, 1);
	InsertEdge(&gp, 1, 4, 1);
	InsertEdge(&gp, 1, 6, 2);
	InsertEdge(&gp, 2, 3, 1);
	InsertEdge(&gp, 3, 5, 4);
	InsertEdge(&gp, 5, 5, 4);
	InsertEdge(&gp, 5, 6, 3);

	return gp;
}

void PrintNodeWeight(Graph* gp, int a) {
	int temp, cnt = 0;
	int i, j;

	if (a < 1 || a > 6) {
		printf("-1\n");
		return;
	}

	for (i = 1; i <= 6; i++) {   // 기준 정점 a
		if (mtr[i][a] != -1) {
			if (gp->Edg[mtr[i][a]].vertex1 == a)    // a와 간선으로 이어진 반대편 노드이름을 temp로
				temp = gp->Edg[mtr[i][a]].vertex2;
			else
				temp = gp->Edg[mtr[i][a]].vertex1;

			printf(" %d %d", temp, gp->Edg[mtr[i][a]].weight);      // temp와 해당 간선의 가중치 출력
		}
	}
	printf("\n");
}

void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize) {  // 가중치 변경 기능   + 간선 추가 기능  +  간선 삭제 기능 + 그래프에 a 혹은 b가 존재하지 않으면 '-1' 출력
	int i, j, flag = 0;

	if ((a < 1 || a > 6) || (b < 1 || b > 6)) {   // 그래프에 정점a 혹은 b가 존재하지 않을 경우
		printf("-1");
		return;
	}

	// (a,b) 또는 (b,a) 간선 존재 여부 확인  
	flag = 0;
	for (j = 0; j < *edgesize; j++) {
		if (gp->Edg[j].vertex1 == a && gp->Edg[j].vertex2 == b) {   // 간선 존재
			flag = 1;
			break;
		}
		else if (gp->Edg[j].vertex1 == b && gp->Edg[j].vertex2 == a) {   // 간선 존재
			flag = 1;
			break;
		}
	}

	if (flag == 1 && w != 0) {   // 간선이 존재하면 가중치가 0이 아니면
		gp->Edg[j].weight = w;    // 가중치 업데이트

		return;   // 업데이트 완료
	}

	if (flag == 0 && w != 0) {  // 간선이 존재하지 않고 w != 0이면, 가중치 w인 새로운 간선(a,b) 생성
		InsertEdge(gp, a, b, w);
		return;    // 생성 완료
	}

	if (flag == 1 && w == 0) {   // 간선이 존재하고 w = 0이면  간선 삭제하기     
		mtr[a][b] = mtr[b][a] = -1;     // 인접행렬에 값 초기화

		edgesize--;
		gp->Edg[j].vertex1 = NULL;     // 간선배열의 j 위치를 초기화
		gp->Edg[j].vertex2 = NULL;
		gp->Edg[j].weight = 0;
	}

}

int main() {

	int loop = 1;
	int a, b, w, i, j;
	char order;
	Graph gp;

	for (i = 1; i <= 6; i++) {
		for (j = 1; j <= 6; j++) {
			mtr[i][j] = -1;
		}
	}

	gp = makeGraph();   // 그래프 제작 완료

	while (loop) {
		scanf("%c", &order);

		switch (order) {
		case 'a':   // 노드번호를 가지는 노드와 인접한 노드와 그 노드까지의 간선 가중치를 모두 인쇄(노드번호의 오름차순)
			scanf("%d", &a);
			getchar();

			PrintNodeWeight(&gp, a);
			break;

		case 'm':
			scanf("%d %d %d", &a, &b, &w);  //간선(a, b)의 가중치를 w로 변경
			getchar();

			UpdateEdge(&gp, a, b, w, &edgesize);
			break;

		case 'q':
			loop = 0;
			break;
		}
	}
	return 0;
}