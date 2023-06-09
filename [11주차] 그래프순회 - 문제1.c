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


void InsertEdge(Graph* gp, int v1, int v2) {    // 간선 추가
	Incidence* incidence1, * incidence2, * p, * pnext;
	int i, nameA, nameB, nameicd;
	i = edgesize;

	gp->Edg[i].vertex1 = v1;
	gp->Edg[i].vertex2 = v2;

	incidence1 = getIncidence(i);
	incidence2 = getIncidence(i);

	//////// 두 노드를 인접리스트에 정점 값의 오름차순으로 삽입하기

	p = gp->Vert[v1].incidence;   // p를 v1의 인접리스트의 head로 지정 

	if (p->next == NULL) {
		p->next = incidence1;
	}
	else {
		nameA = v1;  // 1

		if (nameA == gp->Edg[incidence1->edge].vertex1)    // nameA는 기준 노드의 값
			nameicd = gp->Edg[incidence1->edge].vertex2;    // nameicd는 nameA의 노드와 간선으로 이어질 노드의 값
		else
			nameicd = gp->Edg[incidence1->edge].vertex1;

		while (p->next != NULL) {   // p를 v1의 인접리스트의 끝으로 이동하는 방향
			pnext = p->next;
			if (gp->Edg[pnext->edge].vertex1 == nameA)    // nameB는 기준 노드와 간선으로 이어진 노드의 값
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


	p = gp->Vert[v2].incidence;   // p를 v2의 인접리스트 head로 지정

	if (p->next == NULL) {
		p->next = incidence2;
	}
	else {
		nameA = v2;

		if (nameA == gp->Edg[incidence2->edge].vertex1)
			nameicd = gp->Edg[incidence2->edge].vertex2;
		else
			nameicd = gp->Edg[incidence2->edge].vertex1;

		while (p->next != NULL) {   // p를 v2의 인접리스트의 끝으로 이동하는 방향

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
		gp->Vert[i].label = 0;    // 정점들의 라벨에 fresh 값을 넣는다

	for (i = 0; i < m; i++) {
		gp->Edg[i].label = 0;   // 간선배열의 모든 원소들의 라벨에 fresh 값을 넣는다
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

		if (gp->Edg[p->edge].vertex1 == v)   // 정점 w 설정하기
			w = gp->Edg[p->edge].vertex2;
		else
			w = gp->Edg[p->edge].vertex1;

		if (gp->Vert[w].label == 0) {    // 정점 v에 붙어있는 정점 w가 fresh하면
			gp->Edg[p->edge].label = 1;   // 정점 v와 정점w를 잇는 간선의 라벨값을 1로 치환
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

		gp.Vert[i].name = i;    // 모든 정점에 이름값 부여
		gp.Vert[i].label = 0;    // 정점들의 라벨에 fresh 값을 넣는다

		Incidence* head = (Incidence*)malloc(sizeof(Incidence));  //모든 정점들의 incidence에 리스트의 head 부착하기
		head->edge = NULL;
		head->next = NULL;
		gp.Vert[i].incidence = head;

		gp.Edg[i].label = 0;   // 간선배열의 모든 원소들의 라벨에 fresh 값을 넣는다
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);

		InsertEdge(&gp, v1, v2);
	}

	DFS(&gp, n, m, s);

	return 0;
}