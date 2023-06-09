#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

#define INF 30000;

typedef struct vertex {    // ���� ����ü
	int name;
	int dist;
}Vertex;

typedef struct edge {   // ���� ����ü
	int outEdge, inEdge;
	int weight;
}Edge;

typedef struct graph {   // �׷��� ����ü
	Vertex* Vert;  // ���� �迭
	Edge* Edg;   // ���� �迭
}Graph;

Graph G;
int n, m, s;

void BellmanFordShorestPaths();
int MinDistance(int x, int y);

void Buildgraph() {     // �׷��� �����
	int i, inEdge, outEdge, w;

	G.Vert = (Vertex*)malloc((n + 1) * sizeof(Vertex));   // �׷����� �����迭 ũ�� �Ҵ�
	G.Edg = (Edge*)malloc(m * sizeof(Edge));    // �׷����� �����迭 ũ�� �Ҵ�

	for (i = 1; i <= n; i++) {  // �����迭�� ���� �̸� �����ϱ� (���Ǹ� ���� 1���� ����)
		G.Vert[i].name = i;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &outEdge, &inEdge, &w);

		G.Edg[i].outEdge = outEdge;     // �����迭�� ���� �ϳ��� �����ϱ� (����ü ����)
		G.Edg[i].inEdge = inEdge;
		G.Edg[i].weight = w;
	}
}

int MinDistance(int x, int y) {    // �ּҰŸ��� ã�Ƽ� ��ȯ
	if (x > y)
		return y;
	else
		return x;
}

void BellmanFordShorestPaths() {    // Bellman-Ford �˰���
	int i, j, u, z, cnt;


	for (i = 1; i <= n; i++)
		G.Vert[i].dist = INF;    // �ʱ⿡ ��� ������ dist���� INF�� ����

	G.Vert[s].dist = 0;     // ��������� dist ���� 0���� ����

	for (i = 1; i <= n - 1; i++) {     // n-1�� �ݺ� (��������� �������� ���̿� ������ �ִ� n-1�� ���� �� �ֱ� ����)
		for (j = 0; j < m; j++) {
			u = G.Edg[j].outEdge;    // �����迭�� �ε����� j �� ������ outEdge (origin)�� u�� ����
			z = G.Edg[j].inEdge;     //           "                   inEdge (destination)�� z�� ����

			if (G.Vert[u].dist != 30000)     // u�� dist���� INF �̸� �ǳʶٱ�
				G.Vert[z].dist = MinDistance(G.Vert[z].dist, (G.Vert[u].dist + G.Edg[j].weight));   // ���Ͽ� �ִܰŸ��� d(z)�� ����
		}
	}
}

int main() {
	int i;

	scanf("%d %d %d", &n, &m, &s);      // n�� ��������, m�� �������� (n,m�� ��������)

	Buildgraph();

	BellmanFordShorestPaths();

	for (i = 1; i <= n; i++) {
		if (G.Vert[i].name != s && G.Vert[i].dist != 30000)     // ��������� dist���� ������ �ƴ� �����鸸 ���
			printf("%d %d\n", G.Vert[i].name, G.Vert[i].dist);
	}

	return 0;
}