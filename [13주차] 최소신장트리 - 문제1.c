#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

#define INF 9999;

typedef struct incidence {     // 인접리스트 구조체
	int edge;
	struct Incidence* next;
}Incidence;

typedef struct vertex {    // 정점 구조체
	int name;
	int dist;
	int parent;
	Incidence* head;
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
	int dist;
}Heap;

Graph G;
int n, m;


void addFirst(Incidence* head, int idx);
Heap* buildHeap();
void downHeap(Heap* h, int i, int last);
void swap(Heap* a, Heap* b);
int removeMin(Heap* h, int idx);
int Opposite(int u, int e);
int IsIntheQ(int z, Heap* h, int idx);
void PrimJarnikMST();
void replaceKey(int z, int w, Heap* h, int idx);
void upHeap(Heap* h, int idx);


void Buildgraph() {     // 그래프 만들기
	int i, v1, v2, w;

	scanf("%d %d", &n, &m);      // n는 정점개수, m은 간선개수 (n,m은 전역변수)

	G.Vert = (Vertex*)malloc((n + 1) * sizeof(Vertex));   // 그래프의 정점배열 크기 할당
	G.Edg = (Edge*)malloc(m * sizeof(Edge));    // 그래프의 간선배열 크기 할당

	for (i = 1; i <= n; i++) {  // 정점배열에 원소 삽입하기 (편의를 위해 정점배열은 1부터 시작)
		G.Vert[i].name = i;
		G.Vert[i].dist = 0;   // 거리는 0으로 초기화 

		G.Vert[i].head = (Incidence*)malloc(sizeof(Incidence));  // 정점의 인접리스트 생성
		G.Vert[i].head->next = NULL;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);

		G.Edg[i].vertex1 = v1;     // 간선배열에 '원소' 삽입하기 (구조체 형태)
		G.Edg[i].vertex2 = v2;
		G.Edg[i].weight = w;

		addFirst(G.Vert[v1].head, i);    // 인접리스트의 맨 앞에 '원소'의 인덱스 정보가 있는 노드 삽입
		addFirst(G.Vert[v2].head, i);
	}

}

void addFirst(Incidence* head, int idx) {   // 인접리스트의 맨 앞에 노드에 삽입 
	Incidence* newNode;

	newNode = (Incidence*)malloc(sizeof(Incidence));    // 노드 newNode 생성 및 할당

	newNode->edge = idx;    // newNode의 edge에 인덱스 값 저장
	newNode->next = head->next;     // newNode의 next에 인접리스트의 헤드 뒤의 노드부터 끝까지 연결
	head->next = newNode;    // 인접리스트의 헤드 다음 노드를 newNode로 연결
}

Heap* buildHeap() {    // 힙 생성
	int i;
	Heap* h;

	h = (Heap*)malloc((n + 1) * sizeof(Heap));      // 힙 h의 크기 할당

	for (i = 1; i <= n; i++) {      // 정점배열의 이름, distance 정보를 힙 배열에 복사
		h[i].dist = G.Vert[i].dist;
		h[i].key = G.Vert[i].name;
	}

	for (i = n / 2; i >= 1; i--) {      // i= 2, 1
		downHeap(h, i, n);    // 바뀐 것 없음 (루트의 dist값만 0, 나머지의 dist갑은 INF 이므로)
	}

	return h;
}

void downHeap(Heap* h, int i, int last) {     // 다운힙을 통해 힙의속성 복구
	int left, right;                            // 여기서 힙의속성: 부모의 dist <= 자식의 dist, 완전이진트리
	int min;

	left = 2 * i;     // left는 왼쪽 자식
	right = 2 * i + 1;    // right는 오른쪽 자식

	if (left > last)   // 힙의 최대 크기보다 크면 종료
		return;


	// 두 자식의 dist 값을 비교하여 더 작은 dist값을 가진 자식을 min으로 설정한다.
	min = left;    // left를 최소값으로 
	if (right <= last) {     // right가 최대값보다 작거나 같을 때
		if (h[right].dist < h[left].dist)    // 조건을 만족하면  
			min = right;                    // right를 최소값으로
	}

	if (h[i].dist <= h[min].dist)     // 자기자신의 dist 값이 자식의 dist 값 보다 작거나 같다면 종료(힙의속성 만족) 
		return;

	swap(&h[i], &h[min]);   // 아니면 힙 배열에서 자기자신과 자식의 위치를 맞바꾼다
	downHeap(h, min, last);     // 재귀
}

void swap(Heap* a, Heap* b) {    // 힙 배열에서 두 원소의 위치 맞바꾸기
	Heap temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int removeMin(Heap* h, int i) {   // i는 힙 배열의 마지막 원소의 인덱스 
	Heap temp;
	int root = 1;

	temp = h[root];    // 힙 배열의 첫번째 원소 (root이며, 최소 dist값을 가짐)를 저장
	swap(&h[root], &h[i]);      // 첫번째 원소와 마지막 원소의 위치를 바꾼다

	i--;     // 힙의 마지막 원소 (최소 dist값을 가짐)를 삭제한다
	downHeap(h, root, i);       // 힙속성 복구를 위해 downHeap 실행

	return temp.key;      // 삭제 된 원소의 key값 리턴
}

int Opposite(int u, int e) {      // 정점u의 간선으로 이어진 반대편 정점을 찾아서 리턴
	if (G.Edg[e].vertex1 == u)
		return G.Edg[e].vertex2;
	else
		return G.Edg[e].vertex1;
}

int IsIntheQ(int z, Heap* h, int idx) {   // 큐(힙 배열) 안에 정점 z가 있는지 확인  
	int i;

	for (i = 1; i < idx; i++) {    // 존재하면 1 반환
		if (h[i].key == z)
			return 1;
	}

	return 0;   // 없으면 0 반환
}

void PrimJarnikMST() {   // Prim-Jarnik 알고리즘
	int i, u, z, cnt;
	int sumWeight = 0;    // 총 무게를 0으로 설정  
	Incidence* p;      // 인접리스트의 노드를 가리키는 포인터
	Heap* heap;

	for (i = 1; i <= n; i++) {   // 그래프 G의 모든 정점들에 대하여
		G.Vert[i].dist = INF;     // 거리는 모두 무한대로,
		//G.Vert[i].parent = NULL;     // 부모는 NULL로 설정
	}
	G.Vert[1].dist = 0;    // 출발 정점은 1로 설정

	heap = buildHeap();    // 힙 생성.  초기 힙 배열: [1(0), 2(INF), 3(INF), 4(INF), 5(INF)]

	i = n;
	while (i > 0) {     // 큐가 빌 때까지 반복

		u = removeMin(heap, i);  // 힙 배열의 첫 번째 원소를 제거하고, 제거한 정점을 리턴하여 u에 저장
		printf(" %d", G.Vert[u].name);      // 정점u name출력

		sumWeight += heap[i].dist;      // u의 dist 값을 총 무게에 합산

		p = G.Vert[u].head->next;    // p는 포인터이며, 정점u의 인접리스트(head 다음 노드)를 가리킴
		while (p != NULL) {    // 정점 u의 인접리스트를 처음부터 끝까지 훓는다 (u에 붙어있는 간선들을 모두 훓는다)
			z = Opposite(u, p->edge);    // z는 정점u의 간선으로 이어진 반대편 정점
			if (IsIntheQ(z, heap, i) && G.Vert[z].dist > G.Edg[p->edge].weight) {    // 정점 z가 큐에 들어있으며,  p가 가리키는 간선의 무게보다 큰 경우
				G.Vert[z].dist = G.Edg[p->edge].weight;      // 정점 z의 dist 값 없데이트
				//G.Vert[i].parent = p;
				replaceKey(z, G.Vert[z].dist, heap, i);    // 업데이트 된 z의 dist를 힙 배열에도 반영
			}
			p = p->next;
		}
		i--;
	}
	printf("\n%d", sumWeight);
}

void replaceKey(int z, int w, Heap* h, int last) {    // 힙 배열에서, 바뀐 dist값 업데이트
	int i;

	for (i = 1; i < last; i++) {    // (힙의 사이즈가 1 줄었으므로, last는 포함하지 않는다)
		if (h[i].key == z) {     // 키 값이 z인 원소를 찾아서
			h[i].dist = w;     // dist값 업데이트
			break;
		}
	}

	upHeap(h, i);     // 힙 배열 내의 z의 위치 갱신
}

void upHeap(Heap* h, int idx) {   // 힙순서 속성 복구  
	if (idx == 1)      // z가 루트노드이면 종료
		return;
	if (h[idx].dist >= h[idx / 2].dist)    // 힙 속성 위배가 안되면 종료 (자식 dist 값 >= 부모 dist 값)
		return;

	swap(&h[idx], &h[idx / 2]);     // 힙속성이 위배되면 (자식노드의 dist 값이 더 작은 경우), 부모 노드와 위치 교환

	upHeap(h, idx / 2);      // 재귀하여 힙순서 속성 복구
}

int main() {
	int i;
	Incidence* p;

	Buildgraph();

	PrimJarnikMST();

	return 0;
}