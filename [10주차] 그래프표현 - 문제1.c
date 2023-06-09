#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct incidence {  // ��������Ʈ
	int edge;
	struct Incidence* next;

}Incidence;

typedef struct vertex {  // ����
	Incidence* incidence;
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

int edgesize = 0;  // �����迭�� ũ�� �������� 

Incidence* getIncidence(int edge);
void InsertEdge(Graph* gp, int v1, int v2, int w);
void InserIncidence(Graph* gp, int v1, int v2, Incidence* incidence);
Graph makeGraph();
void PrintNodeWeight(Graph* gp, int a);
void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize);


Incidence* getIncidence(int data) {    // ��������Ʈ ����
	Incidence* node = (Incidence*)malloc(sizeof(Incidence));

	node->edge = data;
	node->next = NULL;

	return node;
}

void InsertEdge(Graph* gp, int v1, int v2, int w) {   // // ���� �߰�
	int i, nameA, nameB, nameicd;
	Incidence* incidence1, * incidence2, * p, * pnext;

	for (i = 0; i < edgesize; i++) {     // ���� �迭���� �� �ڸ� ã��
		if (gp->Edg[i].weight == 0) {     // �� �ڸ��� ã������ ����
			break;
		}
	}

	if (i == edgesize) {    // �� �ڸ��� ������ 
		edgesize++;              // edgesize 1 ����
	}

	gp->Edg[i].vertex1 = v1;    // �����迭���� �ش�Ǵ� �ε����� v1, v2, ����ġ ���� �Է�	
	gp->Edg[i].vertex2 = v2;
	gp->Edg[i].weight = w;

	incidence1 = getIncidence(i);    // ��������Ʈ ����
	incidence2 = getIncidence(i);    // ��������Ʈ ����2  


	//////// �� ���(���������̸� �� ���)�� ��������Ʈ�� ����ȣ�� ������������ �����ϱ�

	p = gp->Vert[v1].incidence;   // p�� v1�� ��������Ʈ�� head�� ���� 

	if (p->next == NULL) {     // ��������Ʈ�� ���������
		p->next = incidence1;   // ��� ���� ��忡 ��� �߰�
	}
	else {     // ��������Ʈ�� ������������� ����ȣ�� ���������� �ǵ��� ��������Ʈ�� �����Ѵ� 
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

				break;   // ���ԿϷ� ����
			}
			p = p->next;

			if (p->next == NULL) {      // ����Ʈ�� ������ ������ (����Ʈ�� ������ ����ȣ�� ���� ũ��)
				pnext->next = incidence1;     // ����Ʈ�� �������� ����
				break;
			}
		}
	}

	if (v1 == v2) {       // ���� ���������̸� ����
		free(incidence2);

		return;
	}
	else {   // ���������� �ƴϸ�

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

	}
}

Graph makeGraph() {  // ����, ����, ��������Ʈ ����   

	int i;
	Graph gp;

	for (i = 1; i <= 6; i++) {
		gp.Vert[i].name = i;       // ���� �� �Է�

		Incidence* head = (Incidence*)malloc(sizeof(Incidence));   // ��������Ʈ�� �����Ͽ� �迭�� Incidece�� ����
		head->edge = NULL;
		head->next = NULL;

		gp.Vert[i].incidence = head;    // ��带 �����迭�� i���ҿ� ����
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
	Incidence* p;

	if (a < 1 || a > 6) {
		printf("-1\n");
		return;
	}

	p = gp->Vert[a].incidence;   // p�� a���� ������ ��带 ����Ŵ
	if (p == NULL)
		return;

	while (p->next != NULL) {
		p = p->next;

		if (gp->Edg[p->edge].vertex1 == a) {    // temp�� ����a�� �������� ����� �ݴ��� ����ȣ
			temp = gp->Edg[p->edge].vertex2;
		}
		else {
			temp = gp->Edg[p->edge].vertex1;
		}

		printf(" %d %d", temp, gp->Edg[p->edge].weight);
	}
	printf("\n");
}

void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize) {  // ����ġ ���� ���  + ���� �߰� ���  +  ���� ���� ��� + �׷����� a Ȥ�� b�� �������� ������ '-1' ���
	Incidence* p, * temp, * pnext;
	int j, flag = 0;    // 

	if ((a < 1 || a > 6) || (b < 1 || b > 6)) {   // �׷����� ����a Ȥ�� b�� �������� ���� ���
		printf("-1");
		return;
	}


	// (a,b) �Ǵ� (b,a) ���� ���� ���� Ȯ��  // 
	flag = 0;
	for (j = 0; j < *edgesize; j++) {   // �����迭 ���� ��ȸ
		if (gp->Edg[j].vertex1 == a && gp->Edg[j].vertex2 == b) {   // ���� ����
			flag = 1;
			break;
		}
		else if (gp->Edg[j].vertex1 == b && gp->Edg[j].vertex2 == a) {   // ���� ����
			flag = 1;
			break;
		}
	}

	if (flag == 1 && w != 0) {   // ������ �����ϰ� w != 0 �̸�
		gp->Edg[j].weight = w;    // ����ġ ������Ʈ

		return;   // ������Ʈ �Ϸ�
	}

	if (flag == 1 && w == 0) {   // ������ �����ϰ� w = 0�̸�  ���� �����ϱ�     
		p = gp->Vert[a].incidence;
		while (p->next != NULL) {		// ��������Ʈ ����
			pnext = p->next;
			if (pnext->edge == j) {    // p�� ���� ����� edge���� j�� ���   
				temp = p->next;
				p->next = temp->next;
				free(temp);
				break;
			}
			p = pnext;
		}

		p = gp->Vert[b].incidence;
		while (p->next != NULL) {
			pnext = p->next;
			pnext = p->next;
			if (pnext->edge == j) {
				temp = p->next;
				p->next = temp->next;
				free(temp);
				break;
			}
			p = pnext;
		}

		edgesize--;
		gp->Edg[j].vertex1 = NULL;
		gp->Edg[j].vertex2 = NULL;
		gp->Edg[j].weight = 0;
	}

	if (flag == 0) {  // ������ �������� ���� ���, ����ġ w�� ���ο� ����(a,b) ����
		InsertEdge(gp, a, b, w);
		return;    // ���� �Ϸ�
	}

}

int main() {

	int loop = 1;
	int a, b, w;
	char order;
	Graph gp;

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