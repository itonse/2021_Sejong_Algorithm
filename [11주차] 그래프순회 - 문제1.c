#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	struct Incidence* incidence;
	int name;
	int label;
}Vertex;

typedef struct incidence {
	int edge;
	struct incidence* next;
}Incidence;

typedef struct edge {
	int vertex1;
	int vertex2;
	int label;
}Edge;

typedef struct graph {
	Vertex Vert[101];
	Edge Edg[1000];
}Graph;

Incidence* getIncidence(int data) {
	Incidence* node = (Incidence*)malloc(sizeof(Incidence));

	node->edge = data;
	node->next = NULL;

	return node;
}

int edgesize = 0;

void InsertEdge(Graph* gp, int v1, int v2);
void DFS(Graph* gp, int n, int m, int s);
void rDFS(Graph* gp, int v);


void InsertEdge(Graph* gp, int v1, int v2) {    // ���� �߰�
	Incidence* incidence1, * incidence2, * p, * pnext;
	int i, nameA, nameB, nameicd;
	i = edgesize;

	gp->Edg[i].vertex1 = v1;
	gp->Edg[i].vertex2 = v2;

	incidence1 = getIncidence(i);
	incidence2 = getIncidence(i);

	//////// �� ��带 ��������Ʈ�� ���� ���� ������������ �����ϱ�

	p = gp->Vert[v1].incidence;   // p�� v1�� ��������Ʈ�� head�� ���� 

	if (p->next == NULL) {
		p->next = incidence1;
	}
	else {
		nameA = v1;  // 1

		if (nameA == gp->Edg[incidence1->edge].vertex1)    // nameA�� ���� ����� ��
			nameicd = gp->Edg[incidence1->edge].vertex2;    // nameicd�� nameA�� ���� �������� �̾��� ����� ��
		else
			nameicd = gp->Edg[incidence1->edge].vertex1;

		while (p->next != NULL) {   // p�� v1�� ��������Ʈ�� ������ �̵��ϴ� ����
			pnext = p->next;
			if (gp->Edg[pnext->edge].vertex1 == nameA)    // nameB�� ���� ���� �������� �̾��� ����� ��
				nameB = gp->Edg[pnext->edge].vertex2;   // nameA = , nameB = , nameicd = 
			else
				nameB = gp->Edg[pnext->edge].vertex1;

			if (nameicd <= nameB) {
				incidence1->next = pnext;
				p->next = incidence1;

				break;
			}
			p = p->next;

			if (p->next == NULL) {
				pnext->next = incidence1;
				break;
			}
		}
	}


	p = gp->Vert[v2].incidence;   // p�� v2�� ��������Ʈ head�� ����

	if (p->next == NULL) {
		p->next = incidence2;
	}
	else {
		nameA = v2;

		if (nameA == gp->Edg[incidence2->edge].vertex1)
			nameicd = gp->Edg[incidence2->edge].vertex2;
		else
			nameicd = gp->Edg[incidence2->edge].vertex1;

		while (p->next != NULL) {   // p�� v2�� ��������Ʈ�� ������ �̵��ϴ� ����

			pnext = p->next;
			if (gp->Edg[pnext->edge].vertex1 == nameA)
				nameB = gp->Edg[pnext->edge].vertex2;
			else
				nameB = gp->Edg[pnext->edge].vertex1;

			if (nameicd <= nameB) {
				incidence2->next = pnext;
				p->next = incidence2;
				break;
			}

			p = p->next;

			if (p->next == NULL) {
				pnext->next = incidence2;
				break;
			}
		}
	}

	edgesize++;
}

void DFS(Graph* gp, int n, int m, int s) {
	int i;

	for (i = 1; i <= n; i++)
		gp->Vert[i].label = 0;    // �������� �󺧿� fresh ���� �ִ´�

	for (i = 0; i < m; i++) {
		gp->Edg[i].label = 0;   // �����迭�� ��� ���ҵ��� �󺧿� fresh ���� �ִ´�
	}
	printf("%d\n", gp->Vert[s].name);

	rDFS(gp, s);
}

void rDFS(Graph* gp, int v) {
	Incidence* p;
	int w;

	gp->Vert[v].label = 1;

	p = gp->Vert[v].incidence;

	while (p->next != NULL) {
		p = p->next;

		if (gp->Edg[p->edge].vertex1 == v)   // ���� w �����ϱ�
			w = gp->Edg[p->edge].vertex2;
		else
			w = gp->Edg[p->edge].vertex1;

		if (gp->Vert[w].label == 0) {    // ���� v�� �پ��ִ� ���� w�� fresh�ϸ�
			gp->Edg[p->edge].label = 1;   // ���� v�� ����w�� �մ� ������ �󺧰��� 1�� ġȯ
			printf("%d\n", gp->Vert[w].name);
			rDFS(gp, w);
		}
	}
}

int main() {
	int n, m, s;
	int i, v1, v2;
	Graph gp;

	scanf("%d %d %d", &n, &m, &s);

	for (i = 1; i <= n; i++) {   // makeGraph 

		gp.Vert[i].name = i;    // ��� ������ �̸��� �ο�
		gp.Vert[i].label = 0;    // �������� �󺧿� fresh ���� �ִ´�

		Incidence* head = (Incidence*)malloc(sizeof(Incidence));  //��� �������� incidence�� ����Ʈ�� head �����ϱ�
		head->edge = NULL;
		head->next = NULL;
		gp.Vert[i].incidence = head;

		gp.Edg[i].label = 0;   // �����迭�� ��� ���ҵ��� �󺧿� fresh ���� �ִ´�
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);

		InsertEdge(&gp, v1, v2);
	}

	DFS(&gp, n, m, s);

	return 0;
}