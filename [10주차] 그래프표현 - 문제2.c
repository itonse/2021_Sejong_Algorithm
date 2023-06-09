#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

int mtr[7][7];

typedef struct vertex {  // ����
	int name;
}Vertex;

typedef struct edge {  // ����
	int weight;   // ����ġ
	int vertex1;
	int vertex2;
}Edge;

typedef struct graph {    // �׷��� ����
	Vertex Vert[7];
	Edge Edg[21];
}Graph;

int edgesize = 0;  // ������ ũ�� �������� 


void InsertEdge(Graph* gp, int v1, int v2, int w);
Graph makeGraph();
void PrintNodeWeight(Graph* gp, int a);
void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize);



void InsertEdge(Graph* gp, int v1, int v2, int w) {   // // ���� �߰�    //		1 2 1
	int i, nameA, nameB;


	for (i = 0; i < edgesize; i++) {     // ���� �迭���� �� �ڸ� ã��
		if (gp->Edg[i].weight == 0) {     // �� �ڸ��� ã������ ���� (�� �ڸ��� �������� �������� ���� �迭�� �߰��ڸ� �� ���� �ִ�.)
			break;
		}
	}

	if (i == edgesize) {
		edgesize++;
	}

	gp->Edg[i].vertex1 = v1;    // �����迭���� �ش�Ǵ� �ε�����  v1, v2, ����ġ ���� �Է�
	gp->Edg[i].vertex2 = v2;
	gp->Edg[i].weight = w;

	// ������Ŀ� �����迭�� �ε��� �Է��ϱ�  (�߿�!!)
	mtr[v1][v2] = i;
	if (v1 != v2)
		mtr[v2][v1] = i;
}

Graph makeGraph() {  // ����, ����, ��������Ʈ ����   

	int i;
	Graph gp;

	for (i = 1; i <= 6; i++) {
		gp.Vert[i].name = i;       // ���� �� �Է�
	}

	for (i = 0; i < 21; i++)
		gp.Edg[i].weight = 0;      // ������ ��� ������ ����ġ�� ���� 0���� �ʱ�ȭ

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

	for (i = 1; i <= 6; i++) {   // ���� ���� a
		if (mtr[i][a] != -1) {
			if (gp->Edg[mtr[i][a]].vertex1 == a)    // a�� �������� �̾��� �ݴ��� ����̸��� temp��
				temp = gp->Edg[mtr[i][a]].vertex2;
			else
				temp = gp->Edg[mtr[i][a]].vertex1;

			printf(" %d %d", temp, gp->Edg[mtr[i][a]].weight);      // temp�� �ش� ������ ����ġ ���
		}
	}
	printf("\n");
}

void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize) {  // ����ġ ���� ���   + ���� �߰� ���  +  ���� ���� ��� + �׷����� a Ȥ�� b�� �������� ������ '-1' ���
	int i, j, flag = 0;

	if ((a < 1 || a > 6) || (b < 1 || b > 6)) {   // �׷����� ����a Ȥ�� b�� �������� ���� ���
		printf("-1");
		return;
	}

	// (a,b) �Ǵ� (b,a) ���� ���� ���� Ȯ��  
	flag = 0;
	for (j = 0; j < *edgesize; j++) {
		if (gp->Edg[j].vertex1 == a && gp->Edg[j].vertex2 == b) {   // ���� ����
			flag = 1;
			break;
		}
		else if (gp->Edg[j].vertex1 == b && gp->Edg[j].vertex2 == a) {   // ���� ����
			flag = 1;
			break;
		}
	}

	if (flag == 1 && w != 0) {   // ������ �����ϸ� ����ġ�� 0�� �ƴϸ�
		gp->Edg[j].weight = w;    // ����ġ ������Ʈ

		return;   // ������Ʈ �Ϸ�
	}

	if (flag == 0 && w != 0) {  // ������ �������� �ʰ� w != 0�̸�, ����ġ w�� ���ο� ����(a,b) ����
		InsertEdge(gp, a, b, w);
		return;    // ���� �Ϸ�
	}

	if (flag == 1 && w == 0) {   // ������ �����ϰ� w = 0�̸�  ���� �����ϱ�     
		mtr[a][b] = mtr[b][a] = -1;     // ������Ŀ� �� �ʱ�ȭ

		edgesize--;
		gp->Edg[j].vertex1 = NULL;     // �����迭�� j ��ġ�� �ʱ�ȭ
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

	gp = makeGraph();   // �׷��� ���� �Ϸ�

	while (loop) {
		scanf("%c", &order);

		switch (order) {
		case 'a':   // ����ȣ�� ������ ���� ������ ���� �� �������� ���� ����ġ�� ��� �μ�(����ȣ�� ��������)
			scanf("%d", &a);
			getchar();

			PrintNodeWeight(&gp, a);
			break;

		case 'm':
			scanf("%d %d %d", &a, &b, &w);  //����(a, b)�� ����ġ�� w�� ����
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