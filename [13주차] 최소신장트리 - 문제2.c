#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct incidence {     // 인접리스트 구조체
	int edge;
	struct Incidence* next;
}Incidence;

typedef struct vertex {    // 정점 구조체
	int name;
}Vertex;

typedef struct edge {   // 간선 구조체
	int vertex1, vertex2;
	int weight;
}Edge;

typedef struct graph {   // 그래프 구조체
	Vertex* Vert;  // 정점 배열
	Edge* Edg;   // 간선 배열
}Graph;

typedef struct heap {    // 힙 구조체
	int key;
	int weight;
}Heap;

typedef struct disjoint {      // 분리집합 구조체
	int size;
	Incidence* head;
}Disjoint;

Graph G;
Disjoint* set;
int n, m;


void Buildgraph();
Disjoint* buildDisjoint();
Heap* buildHeap();
void downHeap(Heap* h, int i, int last);
void swap(Heap* a, Heap* b);
int Find(int findV);
void Union(int v1, int v2);
int delFirst(int v1);
void addFirst(int v2, int idx);
void KruskalMST();
int removeMin(Heap* h, int i);


void Buildgraph() {     // 그래프 만들기
	int i, v1, v2, w;

	scanf("%d %d", &n, &m);      // n는 정점개수, m은 간선개수 (n,m은 전역변수)

	G.Vert = (Vertex*)malloc((n + 1) * sizeof(Vertex));   // 그래프의 정점배열 크기 할당 (편의를 위해 idx 1부터 시작)
	G.Edg = (Edge*)malloc(m * sizeof(Edge));    // 그래프의 간선배열 크기 할당

	for (i = 1; i <= n; i++) {  // 정점배열에 원소 삽입하기 (편의를 위해 정점배열은 1부터 시작)
		G.Vert[i].name = i;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);

		G.Edg[i].vertex1 = v1;     // 간선배열에 원소 삽입하기 (구조체 형태)
		G.Edg[i].vertex2 = v2;
		G.Edg[i].weight = w;
	}
}

Disjoint* buildDisjoint() {   // 분리집합 형태 만들기
	int i;

	set = (Disjoint*)malloc(n * sizeof(Disjoint));

	for (i = 0; i < n; i++) {   // 집합의 개수 n개: 집합 하나에 정점 하나가 포함되도록 집합을 n개 만든다.
		set[i].head = (Incidence*)malloc(sizeof(Incidence));
		set[i].head->edge = i + 1;
		set[i].head->next = NULL;
		set[i].size = 1;   // 모든 집합의 사이즈를 1로 초기화
	}

	return set;
}


Heap* buildHeap() {    // 힙 생성
	int i, cnt;
	Heap* h;

	h = (Heap*)malloc((m + 1) * sizeof(Heap));      // 힙 h의 크기 할당

	for (i = 1; i <= m; i++) {      // 
		h[i].key = i;    // 편의를 위해 힙의 key는 1부터 시작
		h[i].weight = G.Edg[i - 1].weight;    // 힙의 weight에 간선배열의 weight 값을 차례대로 삽입  
	}

	for (i = m / 2; i >= 1; i--) {
		downHeap(h, i, m);
	}

	return h;
}

void downHeap(Heap* h, int i, int last) {     // 힙의속성 복구
	int left, right;                            // 여기서 힙의속성: 부모의 dist <= 자식의 dist, 완전이진트리
	int min;

	left = 2 * i;     // left는 왼쪽 자식
	right = 2 * i + 1;    // right는 오른쪽 자식

	if (left > last)   // 힙의 최대 크기보다 크면 종료
		return;


	// 두 자식의 weight 값을 비교하여 더 작은 weight값을 가진 자식을 min으로 설정한다.
	min = left;    // left를 최소값으로 
	if (right <= last) {     // right가 최대값보다 작거나 같을 때
		if (h[right].weight < h[left].weight)    // 조건을 만족하면  
			min = right;                    // right를 최소값으로
	}

	if (h[i].weight <= h[min].weight)     // 자기자신의 weight 값이 자식의 weight 값 보다 작거나 같다면 종료(힙의속성 만족) 
		return;

	swap(&h[i], &h[min]);   // 아니면 힙 배열에서 위치를 맞바꾼다
	downHeap(h, min, last);     // 재귀
}

void swap(Heap* a, Heap* b) {    // 힙 배열에서 두 원소의 위치 맞바꾸기
	Heap temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int Find(int findV) {   // 정점v가 들어있는 집합을 찾아서 집합 인덱스 반환 // 2 4
	int i;
	Incidence* p;

	for (i = 0; i < n; i++) {

		p = set[i].head;     // 각 집합의 헤드를 가리키는 p
		while (p != NULL) {    // 집합에 포함된 정점 탐색
			if (G.Vert[p->edge].name == findV)    // 집합에 정점v가 포함되어있으면, 집합의 인덱스 반환
				return i;

			p = p->next;   // 집합 내부 순회
		}
	}
	return -1;
}

void Union(int v1, int v2) {    // 두 집합 결합 (분리집합 리스트 갱신)
	int i, temp;

	if (set[v1].size < set[v2].size) {   // v1의 집합의 크기 > v2집합의 크기가 되도록 설정하여, 원소가 적은 집합을 원소가 많은 집합으로 이동
		temp = v2;
		v2 = v1;
		v1 = temp;
	}

	while (1) {   // v2의 집합의 원소가 빌 때까지 반복
		i = delFirst(v2);    // v2 집합 리스트의 맨 앞의 노드(정점)을 i에 저장

		if (i == -1)    // v2 집합의 리스트가 비게되면 종료
			break;

		addFirst(v1, i);    // 정점i를 v1 집합에 포함시킨다
	}
	set[v2].head = NULL;    // v2집합 해제
}

int delFirst(int v2) {     // v2 집합 리스트의 맨 앞의 노드(정점)를 삭제 후 반환하는 함수
	int temp;

	if (set[v2].head == NULL)    // 리스트가 비어있으면 -1 반환
		return -1;
	temp = set[v2].head->edge;
	set[v2].head = set[v2].head->next;     // 첫 노드 삭제 후 두번째 노드를 헤드에 연결시킨다
	set[v2].size--;   // 집합 v2의 크기 1 감소

	return temp;    // 삭제된 노드(정점) 반환
}

void addFirst(int v1, int idx) {   // v1집합 리스트의 맨 앞 노드에 삽입 노드(정점idx) 삽입 
	Incidence* newNode;

	newNode = (Incidence*)malloc(sizeof(Incidence));    // 노드 newNode 생성 및 할당

	newNode->edge = idx;    // newNode의 edge에 idx값 저장
	newNode->next = set[v1].head;     // newNode의 next에 v1집합 리스트의 헤드 노드를 연결
	set[v1].head = newNode;    // v1집합 리스트의 헤드 노드를 newNode로 연결
	set[v1].size++;  // 집합 v1의 크기 1 증가
}

void KruskalMST() {
	int v1, v2, u, i, cnt;
	int sumWeight = 0;
	Heap* heap;

	heap = buildHeap();
	set = buildDisjoint();

	i = m;
	while (i > 0) {
		u = removeMin(heap, i);    // 힙의 루트노드를 삭제 후 키 값 반환

		v1 = Find(G.Edg[u - 1].vertex1);     // 큐(힙)에서 반환된 간선의 정점1을 Find함수에 넣는다 (집합의 인덱스 반환)
		v2 = Find(G.Edg[u - 1].vertex2);      // 큐(힙)에서 반환된 간선의 정점2를 Find함수에 넣는다 (집합의 인덱스 반환)

		if (v1 != v2) {   // v1과 v2의 집합의 인덱스가 다르면 (서로 다른 집합이면)
			sumWeight += G.Edg[u - 1].weight;    // 총 무게에 간선 무게를 더한 후
			printf(" %d", G.Edg[u - 1].weight);
			Union(v1, v2);       // 두 집합을 결합시킨다
		}
		i--;
	}

	printf("\n%d", sumWeight);
}

int removeMin(Heap* h, int i) {   // i는 힙 배열의 마지막 원소의 인덱스
	Heap temp;
	int root = 1;

	temp = h[root];    // 힙 배열의 첫번째 원소 (root이며, 최소 weight값을 가짐)를 저장
	swap(&h[root], &h[i]);      // 첫번째 원소와 마지막 원소의 위치를 바꾼다

	i--;     // 힙의 마지막 원소 (최소 weight값을 가짐)를 삭제한다
	downHeap(h, root, i);       // 힙속성 복구를 위해 downHeap 실행

	return temp.key;      // 삭제 된 원소의 key값 리턴
}

int main() {

	Buildgraph();

	KruskalMST();

	return 0;
}