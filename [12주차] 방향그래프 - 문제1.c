#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int element;
	struct Node* next;
}Node;

typedef struct vertex {
	char name;		// 정점의 이름
	int indegree;		// 진입차수(진입간선 개수)
	Node* inEdges;		// 진입부착간선리스트
	Node* outEdges;		// 진출부착간선리스트

}Vertex;

typedef struct edge {
	int origin;   // 출발 정점
	int destination;   // 도착 정점
}Edge;

typedef struct graph {
	Vertex* vertices;
	Edge* edges;
}Graph;

typedef struct Queue {   // 순차큐
	int* queue;    // n크기의 배열을 참조하게 될 포인터
	int front;    // 저장된 원소 중에서 첫 번째 원소
	int rear;    // 저장된 원소 중에서 마지막 원소
}Queue;


Graph G;   // 전역변수 G 선언
int n;    // 정점 수 
int m;    // 간선 수
int* in;    // in[i]: 정점 i의 진입차수
int* topOrder;    // 정점들의 위상순서 배열 (크기는 n+1),   topOder[0] = 1(DAG), 0(non-DAG 그래프에 싸이클 있음) 
Queue Q;    // 정점들의 대기열 (최대 크기 n)


Node* getNode();
void BuildGraph();
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char vName, int i);
void addFirst(Node* H, int i);
int index(char vName);
void topologicalSort();
void createQueue();
void enqueue(i);
int QisEmpty();
int dequeue();


Node* getNode() {    // 리스트 할당 함수
	Node* node = (Node*)malloc(sizeof(Node));

	node->element = NULL;
	node->next = NULL;
	return node;
}

void BuildGraph() {    // 그래프 만들기
	char vName, uName, wName;
	int i;

	scanf("%d", &n);
	getchar();

	G.vertices = (Vertex*)malloc(n * sizeof(Vertex));    // n크기의 정점배열 구조로 할당
	topOrder = (int*)malloc((n + 1) * sizeof(int));    // 크기 n+1인 위상순서 배열 할당

	for (i = 0; i < n; i++) {   // 정점이름 n개 입력 
		scanf("%c", &vName);
		getchar();
		insertVertex(vName, i);
	}

	scanf("%d", &m);
	G.edges = (Edge*)malloc(m * sizeof(Edge));

	for (i = 0; i < m; i++) {
		getchar();
		scanf("%c %c", &uName, &wName);

		insertDirectedEdge(uName, wName, i);  // i는 간선 삽입 순서
	}
}

void insertVertex(char vName, int i) {   // 그래프에 정점 삽입.  정점의 구조: name, 진입차수, 진입간선리스트, 진출간선리스트
	G.vertices[i].name = vName;     // i는 정점 삽입 순서
	G.vertices[i].indegree = 0;

	G.vertices[i].outEdges = getNode();   // getNode 함수로 '진출'부착간선리스트 할당 + 리스트 초기화
	G.vertices[i].inEdges = getNode();   // getNode 함수로 '진입'부착간선리스트 할당 + 리스트 초기화
}

void insertDirectedEdge(char uName, char wName, int i) {    // 그래프에 방향간선 삽입
	int u, w;

	u = index(uName);
	w = index(wName);

	G.edges[i].origin = u;     // u는 간선의 출발정점
	G.edges[i].destination = w;    // w는 간선의 도착정점

	addFirst(G.vertices[u].outEdges, i);     // 정점u의 '진출'간선리스트의 헤드, 간선 삽입순서 i
	addFirst(G.vertices[w].inEdges, i);    // // 정점w의 '진입'간선리스트의 헤드, 간선 삽입순서 i

	G.vertices[w].indegree++;     // 정점 w의 진입차수 1 증가
}

int index(char vName) {   // 해당 정점의 인덱스 반환
	int i;

	for (i = 0; i < n; i++) {
		if (G.vertices[i].name == vName)
			return i;
	}
}

void addFirst(Node* H, int i) {    // 새로 입력되는 간선에 대한 노드를 '리스트의 맨 앞(헤드노드 다음)'에 삽입
	Node* temp;

	temp = getNode();  // 새 노드 생성

	temp->element = i;   // ( i는 간선 삽입 순서)
	temp->next = H->next;
	H->next = temp;
}

void topologicalSort() {   // 위상정렬
	int i, t, u, e, w;
	Node* temp;

	createQueue();    // 큐 초기화

	in = (int*)malloc(n * sizeof(int));  // in에 배열 크기 할당 (in[i]: 정점 i의 진입차수)

	for (i = 0; i < n; i++) {    // 최초로 진입간선의 개수가 0인 정점을 찾을 때, 정점번호 순으로 조사해야 함
		in[i] = G.vertices[i].indegree;   // i번째 삽입된 정점의 차수를 배열 in의 i번째 인덱스에 저장
		if (in[i] == 0)     // 초기에 진입차수가 0인 정점들은
			enqueue(i);   // Q에 삽입, (큐 포화상태 검사 필요x)
	}

	t = 1;   // t는 위상순위

	while (!QisEmpty()) {   // 큐가 공백이 아닐 때
		u = dequeue();   // 삭제된 원소값을 u에 저장 (값은 정점이 그래프에 삽입된 순서 )
		topOrder[t] = u;     // 위상순위 정점 저장

		t++;   // 위상순위 매길 번호 1 증가

		temp = G.vertices[u].outEdges->next;   // u의 진출간선의 맨 앞(헤드 다음노드)을 temp로 지정
		while (temp != NULL) {   // u의 모든 '진출'간선 e에 대해 반복
			e = temp->element;
			w = G.edges[e].destination;     // w는 u의 진출간선 e의 반대편 정점

			in[w] = in[w] - 1;   // 정점 w의 진입차수 1 감소
			if (in[w] == 0)
				enqueue(w);   // w의 진입차수가 0이면 큐에 삽입

			temp = temp->next;
		}
	}

	if (t <= n)   // DAG이기 위해서는 t = n+1 이여야만 한다.  t <= n은 non-DAG인 경우이다. (위상순서 안가짐, 그래프에 싸이클이 존재)
		topOrder[0] = 0;     // topOder의 비어있는 공간인 0번째 인덱스에 0 저장
	else
		topOrder[0] = 1;   // DAG인 경우 1 저장(위상순서 가짐, 그래프에 사이클x)
}

void createQueue() {   // 큐 초기화
	Q.queue = (int*)malloc(n * sizeof(int));  // 큐에 배열크기 할당
	Q.front = -1;    // front와 rear의 초기 위치는 -1
	Q.rear = -1;
}

void enqueue(i) {
	if (Q.rear == -1 && Q.front == -1) {
		Q.front += 1;
		Q.rear += 1;
		Q.queue[Q.rear] = i;   // 큐의 rear 위치에 i 삽입
	}
	else {
		Q.rear += 1;
		Q.queue[Q.rear] = i;
	}
}

int QisEmpty() {
	if (Q.front == -1 && Q.rear == -1)
		return 1;
	else
		return 0;
}

int dequeue() {   // 큐가 공백이 아닌 상태
	int d;

	d = Q.queue[Q.front];    // 큐에서 삭제할 원소를 d에 저장 
	Q.front += 1;				// front 위치를 한 칸 뒤로

	if (Q.rear < Q.front) {    // 삭제해서 큐가 공백이 되는 경우 front와 rear 위치 초기화
		Q.front = -1;
		Q.rear = -1;
	}

	return d;     // 삭제된 원소 값 반환
}


int main() {
	int i;

	BuildGraph();

	topologicalSort();

	if (topOrder[0] == 0)    // non-DAG, 위상순서 없음
		printf("0");
	else {    // DAG, 위상순서 있음
		for (i = 1; i <= n; i++) {
			printf("%c ", G.vertices[topOrder[i]].name);   	 // 위상순서 출력
		}
	}

	return 0;
}