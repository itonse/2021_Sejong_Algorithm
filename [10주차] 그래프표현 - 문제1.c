#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct incidence {  // 인접리스트
	int edge;
	struct Incidence* next;

}Incidence;

typedef struct vertex {  // 정점
	Incidence* incidence;
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

int edgesize = 0;  // 간선배열의 크기 전역변수 

Incidence* getIncidence(int edge);
void InsertEdge(Graph* gp, int v1, int v2, int w);
void InserIncidence(Graph* gp, int v1, int v2, Incidence* incidence);
Graph makeGraph();
void PrintNodeWeight(Graph* gp, int a);
void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize);


Incidence* getIncidence(int data) {    // 인접리스트 생성
	Incidence* node = (Incidence*)malloc(sizeof(Incidence));

	node->edge = data;
	node->next = NULL;

	return node;
}

void InsertEdge(Graph* gp, int v1, int v2, int w) {   // // 간선 추가
	int i, nameA, nameB, nameicd;
	Incidence* incidence1, * incidence2, * p, * pnext;

	for (i = 0; i < edgesize; i++) {     // 간선 배열에서 빈 자리 찾기
		if (gp->Edg[i].weight == 0) {     // 빈 자리를 찾았으면 종료
			break;
		}
	}

	if (i == edgesize) {    // 빈 자리가 없으면 
		edgesize++;              // edgesize 1 증가
	}

	gp->Edg[i].vertex1 = v1;    // 간선배열에서 해당되는 인덱스에 v1, v2, 가중치 정보 입력	
	gp->Edg[i].vertex2 = v2;
	gp->Edg[i].weight = w;

	incidence1 = getIncidence(i);    // 인접리스트 생성
	incidence2 = getIncidence(i);    // 인접리스트 생성2  


	//////// 두 노드(루프간선이면 한 노드)를 인접리스트에 노드번호의 오름차순으로 삽입하기

	p = gp->Vert[v1].incidence;   // p를 v1의 인접리스트의 head로 지정 

	if (p->next == NULL) {     // 인접리스트가 비어있으면
		p->next = incidence1;   // 헤드 다음 노드에 노드 추가
	}
	else {     // 인접리스트가 비어있지않으면 노드번호가 오름차순이 되도록 인접리스트를 정렬한다 
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

				break;   // 삽입완료 종료
			}
			p = p->next;

			if (p->next == NULL) {      // 리스트의 끝까지 갔으면 (리스트의 부착된 노드번호들 보다 크면)
				pnext->next = incidence1;     // 리스트의 마지막에 삽입
				break;
			}
		}
	}

	if (v1 == v2) {       // 만약 루프간선이면 리턴
		free(incidence2);

		return;
	}
	else {   // 루프간선이 아니면

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

	}
}

Graph makeGraph() {  // 정점, 간선, 인접리스트 생성   

	int i;
	Graph gp;

	for (i = 1; i <= 6; i++) {
		gp.Vert[i].name = i;       // 정점 값 입력

		Incidence* head = (Incidence*)malloc(sizeof(Incidence));   // 인접리스트를 생성하여 배열의 Incidece에 연결
		head->edge = NULL;
		head->next = NULL;

		gp.Vert[i].incidence = head;    // 노드를 정점배열의 i원소에 부착
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
	Incidence* p;

	if (a < 1 || a > 6) {
		printf("-1\n");
		return;
	}

	p = gp->Vert[a].incidence;   // p는 a값을 가지는 노드를 가리킴
	if (p == NULL)
		return;

	while (p->next != NULL) {
		p = p->next;

		if (gp->Edg[p->edge].vertex1 == a) {    // temp는 정점a와 간선으로 연결된 반대편 노드번호
			temp = gp->Edg[p->edge].vertex2;
		}
		else {
			temp = gp->Edg[p->edge].vertex1;
		}

		printf(" %d %d", temp, gp->Edg[p->edge].weight);
	}
	printf("\n");
}

void UpdateEdge(Graph* gp, int a, int b, int w, int* edgesize) {  // 가중치 변경 기능  + 간선 추가 기능  +  간선 삭제 기능 + 그래프에 a 혹은 b가 존재하지 않으면 '-1' 출력
	Incidence* p, * temp, * pnext;
	int j, flag = 0;    // 

	if ((a < 1 || a > 6) || (b < 1 || b > 6)) {   // 그래프에 정점a 혹은 b가 존재하지 않을 경우
		printf("-1");
		return;
	}


	// (a,b) 또는 (b,a) 간선 존재 여부 확인  // 
	flag = 0;
	for (j = 0; j < *edgesize; j++) {   // 간선배열 원소 순회
		if (gp->Edg[j].vertex1 == a && gp->Edg[j].vertex2 == b) {   // 간선 존재
			flag = 1;
			break;
		}
		else if (gp->Edg[j].vertex1 == b && gp->Edg[j].vertex2 == a) {   // 간선 존재
			flag = 1;
			break;
		}
	}

	if (flag == 1 && w != 0) {   // 간선이 존재하고 w != 0 이면
		gp->Edg[j].weight = w;    // 가중치 업데이트

		return;   // 업데이트 완료
	}

	if (flag == 1 && w == 0) {   // 간선이 존재하고 w = 0이면  간선 삭제하기     
		p = gp->Vert[a].incidence;
		while (p->next != NULL) {		// 인접리스트 개조
			pnext = p->next;
			if (pnext->edge == j) {    // p의 다음 노드의 edge값이 j일 경우   
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

	if (flag == 0) {  // 간선이 존재하지 않을 경우, 가중치 w인 새로운 간선(a,b) 생성
		InsertEdge(gp, a, b, w);
		return;    // 생성 완료
	}

}

int main() {

	int loop = 1;
	int a, b, w;
	char order;
	Graph gp;

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