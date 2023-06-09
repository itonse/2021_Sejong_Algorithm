#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

#define INF 30000;

typedef struct vertex {    // 정점 구조체
	int name;
	int dist;
}Vertex;

typedef struct edge {   // 간선 구조체
	int outEdge, inEdge;
	int weight;
}Edge;

typedef struct graph {   // 그래프 구조체
	Vertex* Vert;  // 정점 배열
	Edge* Edg;   // 간선 배열
}Graph;

Graph G;
int n, m, s;

void BellmanFordShorestPaths();
int MinDistance(int x, int y);

void Buildgraph() {     // 그래프 만들기
	int i, inEdge, outEdge, w;

	G.Vert = (Vertex*)malloc((n + 1) * sizeof(Vertex));   // 그래프의 정점배열 크기 할당
	G.Edg = (Edge*)malloc(m * sizeof(Edge));    // 그래프의 간선배열 크기 할당

	for (i = 1; i <= n; i++) {  // 정점배열에 정점 이름 삽입하기 (편의를 위해 1부터 시작)
		G.Vert[i].name = i;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &outEdge, &inEdge, &w);

		G.Edg[i].outEdge = outEdge;     // 간선배열에 간선 하나씩 삽입하기 (구조체 형태)
		G.Edg[i].inEdge = inEdge;
		G.Edg[i].weight = w;
	}
}

int MinDistance(int x, int y) {    // 최소거리를 찾아서 반환
	if (x > y)
		return y;
	else
		return x;
}

void BellmanFordShorestPaths() {    // Bellman-Ford 알고리즘
	int i, j, u, z, cnt;


	for (i = 1; i <= n; i++)
		G.Vert[i].dist = INF;    // 초기에 모든 정점의 dist값을 INF로 지정

	G.Vert[s].dist = 0;     // 출발정점의 dist 값을 0으로 지정

	for (i = 1; i <= n - 1; i++) {     // n-1번 반복 (출발정점과 도착정점 사이에 간선이 최대 n-1개 있을 수 있기 때문)
		for (j = 0; j < m; j++) {
			u = G.Edg[j].outEdge;    // 간선배열의 인덱스가 j 인 원소의 outEdge (origin)를 u에 저장
			z = G.Edg[j].inEdge;     //           "                   inEdge (destination)를 z에 저장

			if (G.Vert[u].dist != 30000)     // u의 dist값이 INF 이면 건너뛰기
				G.Vert[z].dist = MinDistance(G.Vert[z].dist, (G.Vert[u].dist + G.Edg[j].weight));   // 비교하여 최단거리를 d(z)에 저장
		}
	}
}

int main() {
	int i;

	scanf("%d %d %d", &n, &m, &s);      // n는 정점개수, m은 간선개수 (n,m은 전역변수)

	Buildgraph();

	BellmanFordShorestPaths();

	for (i = 1; i <= n; i++) {
		if (G.Vert[i].name != s && G.Vert[i].dist != 30000)     // 출발정점과 dist값이 무한이 아닌 정점들만 출력
			printf("%d %d\n", G.Vert[i].name, G.Vert[i].dist);
	}

	return 0;
}