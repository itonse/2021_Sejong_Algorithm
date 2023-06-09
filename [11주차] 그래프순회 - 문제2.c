#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int name;
	int label;
}Vertex;

typedef struct edge {
	int vertex1;
	int vertex2;
	int label;
}Edge;

typedef struct graph {
	Vertex Vert[101];
	Edge Edg[1000];
}Graph;

int edgesize = 0;     // 간선배열의 크기 
int mtr[101][101];    // 행렬 선언 (2차원배열 형태)

void InsertEdge(Graph* gp, int v1, int v2);
void BFS(Graph* gp, int n, int m, int s);
void BFS1(Graph* gp, int n, int s);


void InsertEdge(Graph* gp, int v1, int v2) {    // 간선 추가
	int i;
	i = edgesize;

	gp->Edg[i].vertex1 = v1;
	gp->Edg[i].vertex2 = v2;

	mtr[v1][v2] = mtr[v2][v1] = i;     // 인접행렬 값 업데이트

	edgesize++;
}

void BFS(Graph* gp, int n, int m, int s) {
	int i;

	for (i = 1; i <= n; i++)
		gp->Vert[i].label = 0;    // 정점들의 라벨에 fresh 값을 넣는다

	for (i = 0; i < m; i++) {
		gp->Edg[i].label = 0;   // 간선배열의 모든 원소들의 라벨에 fresh 값을 넣는다
	}

	BFS1(gp, n, s);
}

void BFS1(Graph* gp, int n, int s) {   // (n = 6  m = 9  s = 1)
	int* list, * list2;
	int i, k, w, cnt, cnt2;

	list = (int*)malloc(n * sizeof(int));    // 리스트 생성

	cnt = 0;
	list[cnt++] = s;     // (list[0] = 1)
	gp->Vert[s].label = 1;   // 정점 s의 라벨을 1로 치환 
	printf("%d\n", s);

	while (cnt > 0) {
		cnt2 = 0;
		list2 = (int*)malloc(n * sizeof(int));  // list2 메모리 생성

		for (i = 0; i < cnt; i++) {   // list의 모든 정점들에 대해서 (i=0만 실행)

			for (k = 1; k <= n; k++) {    // 각 정점들의 모든 부착간선들에 대해서 (k= 2,3,4 실행)

				if (mtr[k][list[i]] != -1) {   // (mtr[2][1], mtr[3][1], mre[4][1]) 

					if (gp->Edg[mtr[k][list[i]]].label == 0) {    // 해당 간선이 fresh 하면

						if (gp->Edg[mtr[k][list[i]]].vertex1 == gp->Vert[list[i]].name)   // 정점의 해당 간선의 반대편에 있는 정점을 w로 설정
							w = gp->Edg[mtr[k][list[i]]].vertex2;
						else
							w = gp->Edg[mtr[k][list[i]]].vertex1;

						if (gp->Vert[w].label == 0) {   // w가 fresh하면
							gp->Edg[mtr[k][list[i]]].label = 1;   // w와의 간선의 라벨값을 1로 변경
							gp->Vert[w].label = 1;    // w의 라벨 값을 1로 변경
							printf("%d\n", w);
							list2[cnt2++] = w;
						}
					}
				}
			}
		}

		free(list);
		list = (int*)malloc(n * sizeof(int));  // list 메모리 삭제 후 다시 만들기

		cnt = cnt2;  // (cnt = 3)

		i = 0;
		while (i < cnt2) {  // list2 원소들을 list에 복사  (i= 0 1 2)
			list[i] = list2[i];
			i++;
		}

		free(list2);
	}

	free(list);
	free(list2);
}

int main() {
	int n, m, s;
	int i, j, v1, v2;
	Graph gp;

	scanf("%d %d %d", &n, &m, &s);

	for (i = 1; i <= n; i++) {   // makeGraph 

		gp.Vert[i].name = i;    // 모든 정점에 이름값 부여
		gp.Vert[i].label = 0;    // 정점들의 라벨에 fresh 값을 넣는다

		gp.Edg[i].label = 0;   // 간선배열의 모든 원소들의 라벨에 fresh 값을 넣는다

		for (j = 1; j <= n; j++)   // 행렬의 원소들을 -1로 초기화
			mtr[i][j] = -1;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);

		InsertEdge(&gp, v1, v2);
	}

	BFS(&gp, n, m, s);

	return 0;
}