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

int edgesize = 0;     // �����迭�� ũ�� 
int mtr[101][101];    // ��� ���� (2�����迭 ����)

void InsertEdge(Graph* gp, int v1, int v2);
void BFS(Graph* gp, int n, int m, int s);
void BFS1(Graph* gp, int n, int s);


void InsertEdge(Graph* gp, int v1, int v2) {    // ���� �߰�
	int i;
	i = edgesize;

	gp->Edg[i].vertex1 = v1;
	gp->Edg[i].vertex2 = v2;

	mtr[v1][v2] = mtr[v2][v1] = i;     // ������� �� ������Ʈ

	edgesize++;
}

void BFS(Graph* gp, int n, int m, int s) {
	int i;

	for (i = 1; i <= n; i++)
		gp->Vert[i].label = 0;    // �������� �󺧿� fresh ���� �ִ´�

	for (i = 0; i < m; i++) {
		gp->Edg[i].label = 0;   // �����迭�� ��� ���ҵ��� �󺧿� fresh ���� �ִ´�
	}

	BFS1(gp, n, s);
}

void BFS1(Graph* gp, int n, int s) {   // (n = 6  m = 9  s = 1)
	int* list, * list2;
	int i, k, w, cnt, cnt2;

	list = (int*)malloc(n * sizeof(int));    // ����Ʈ ����

	cnt = 0;
	list[cnt++] = s;     // (list[0] = 1)
	gp->Vert[s].label = 1;   // ���� s�� ���� 1�� ġȯ 
	printf("%d\n", s);

	while (cnt > 0) {
		cnt2 = 0;
		list2 = (int*)malloc(n * sizeof(int));  // list2 �޸� ����

		for (i = 0; i < cnt; i++) {   // list�� ��� �����鿡 ���ؼ� (i=0�� ����)

			for (k = 1; k <= n; k++) {    // �� �������� ��� ���������鿡 ���ؼ� (k= 2,3,4 ����)

				if (mtr[k][list[i]] != -1) {   // (mtr[2][1], mtr[3][1], mre[4][1]) 

					if (gp->Edg[mtr[k][list[i]]].label == 0) {    // �ش� ������ fresh �ϸ�

						if (gp->Edg[mtr[k][list[i]]].vertex1 == gp->Vert[list[i]].name)   // ������ �ش� ������ �ݴ��� �ִ� ������ w�� ����
							w = gp->Edg[mtr[k][list[i]]].vertex2;
						else
							w = gp->Edg[mtr[k][list[i]]].vertex1;

						if (gp->Vert[w].label == 0) {   // w�� fresh�ϸ�
							gp->Edg[mtr[k][list[i]]].label = 1;   // w���� ������ �󺧰��� 1�� ����
							gp->Vert[w].label = 1;    // w�� �� ���� 1�� ����
							printf("%d\n", w);
							list2[cnt2++] = w;
						}
					}
				}
			}
		}

		free(list);
		list = (int*)malloc(n * sizeof(int));  // list �޸� ���� �� �ٽ� �����

		cnt = cnt2;  // (cnt = 3)

		i = 0;
		while (i < cnt2) {  // list2 ���ҵ��� list�� ����  (i= 0 1 2)
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

		gp.Vert[i].name = i;    // ��� ������ �̸��� �ο�
		gp.Vert[i].label = 0;    // �������� �󺧿� fresh ���� �ִ´�

		gp.Edg[i].label = 0;   // �����迭�� ��� ���ҵ��� �󺧿� fresh ���� �ִ´�

		for (j = 1; j <= n; j++)   // ����� ���ҵ��� -1�� �ʱ�ȭ
			mtr[i][j] = -1;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);

		InsertEdge(&gp, v1, v2);
	}

	BFS(&gp, n, m, s);

	return 0;
}