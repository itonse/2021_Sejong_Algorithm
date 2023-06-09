#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

#define INF 30000;

typedef struct incidence {     // ��������Ʈ ����ü
	int edge;
	struct Incidence* next;
}Incidence;

typedef struct vertex {    // ���� ����ü
	int name;
	int dist;
	Incidence* head;
}Vertex;

typedef struct edge {   // ���� ����ü
	int vertex1, vertex2;
	int weight;
}Edge;

typedef struct graph {   // �׷��� ����ü
	Vertex* Vert;  // ���� �迭
	Edge* Edg;   // ���� �迭
}Graph;

typedef struct heap {    // �� ����ü
	int key;
	int dist;
}Heap;

Graph G;
int n, m, s;


void addFirst(Incidence* head, int idx);
Heap* buildHeap();
void downHeap(Heap* h, int i, int last);
void swap(Heap* a, Heap* b);
int removeMin(Heap* h, int idx);
int Opposite(int u, int e);
int IsIntheQ(int z, Heap* h, int idx);
void replaceKey(int z, int w, Heap* h, int idx);
void upHeap(Heap* h, int idx);
void DijkstraShortestPaths();


void Buildgraph() {     // �׷��� �����
	int i, v1, v2, w;

	G.Vert = (Vertex*)malloc((n + 1) * sizeof(Vertex));   // �׷����� �����迭 ũ�� �Ҵ�
	G.Edg = (Edge*)malloc(m * sizeof(Edge));    // �׷����� �����迭 ũ�� �Ҵ�

	for (i = 1; i <= n; i++) {  // �����迭�� ���� �����ϱ� (���Ǹ� ���� �����迭�� 1���� ����)
		G.Vert[i].name = i;
		G.Vert[i].dist = 0;   // �Ÿ��� 0���� �ʱ�ȭ 

		G.Vert[i].head = (Incidence*)malloc(sizeof(Incidence));  // ������ ��������Ʈ ����
		G.Vert[i].head->next = NULL;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);

		G.Edg[i].vertex1 = v1;     // �����迭�� '����' �����ϱ� (����ü ����)
		G.Edg[i].vertex2 = v2;
		G.Edg[i].weight = w;

		addFirst(G.Vert[v1].head, i);    // ��������Ʈ�� �� �տ� '����'�� �ε��� ������ �ִ� ��� ����
		addFirst(G.Vert[v2].head, i);
	}

}

void addFirst(Incidence* head, int idx) {   // ��������Ʈ�� �� �տ� ��忡 ���� 
	Incidence* newNode;

	newNode = (Incidence*)malloc(sizeof(Incidence));    // ��� newNode ���� �� �Ҵ�

	newNode->edge = idx;    // newNode�� edge�� �ε��� �� ����
	newNode->next = head->next;     // newNode�� next�� ��������Ʈ�� ��� ���� ������ ������ ����
	head->next = newNode;    // ��������Ʈ�� ��� ���� ��带 newNode�� ����
}

Heap* buildHeap() {    // �� ����
	int i;
	Heap* h;

	h = (Heap*)malloc((n + 1) * sizeof(Heap));      // �� h�� ũ�� �Ҵ�

	for (i = 1; i <= n; i++) {      // �����迭�� �̸�, distance ������ �� �迭�� ����
		h[i].dist = G.Vert[i].dist;
		h[i].key = G.Vert[i].name;
	}

	for (i = n / 2; i >= 1; i--) {      // i= 2, 1
		downHeap(h, i, n);
	}

	return h;
}

void downHeap(Heap* h, int i, int last) {     // �ٿ����� ���� ���ǼӼ� ����
	int left, right;                            // ���⼭ ���ǼӼ�: �θ��� dist <= �ڽ��� dist, ��������Ʈ��
	int min;

	left = 2 * i;     // left�� ���� �ڽ�
	right = 2 * i + 1;    // right�� ������ �ڽ�

	if (left > last)   // ���� �ִ� ũ�⺸�� ũ�� ����
		return;


	// �� �ڽ��� dist ���� ���Ͽ� �� ���� dist���� ���� �ڽ��� min���� �����Ѵ�.
	min = left;    // left�� �ּҰ����� 
	if (right <= last) {     // right�� �ִ밪���� �۰ų� ���� ��
		if (h[right].dist < h[left].dist)    // ������ �����ϸ�  
			min = right;                    // right�� �ּҰ�����
	}

	if (h[i].dist <= h[min].dist)     // �ڱ��ڽ��� dist ���� �ڽ��� dist �� ���� �۰ų� ���ٸ� ����(���ǼӼ� ����) 
		return;

	swap(&h[i], &h[min]);   // �ƴϸ� �� �迭���� �ڱ��ڽŰ� �ڽ��� ��ġ�� �¹ٲ۴�
	downHeap(h, min, last);     // ���
}

void swap(Heap* a, Heap* b) {    // �� �迭���� �� ������ ��ġ �¹ٲٱ�
	Heap temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int removeMin(Heap* h, int i) {   // i�� �� �迭�� ������ ������ �ε��� (�ʱ� i=5)
	Heap temp;
	int root = 1;

	temp = h[root];    // �� �迭�� ù��° ���� (root�̸�, �ּ� dist���� ����)�� ����
	swap(&h[root], &h[i]);      // ù��° ���ҿ� ������ ������ ��ġ�� �ٲ۴�

	i--;     // ���� ������ ���� (�ּ� dist���� ����)�� �����Ѵ�
	downHeap(h, root, i);       // ���Ӽ� ������ ���� downHeap ����

	return temp.key;      // ���� �� ������ key�� ����
}

int Opposite(int u, int e) {      // ����u�� �������� �̾��� �ݴ��� ������ ã�Ƽ� ����
	if (G.Edg[e].vertex1 == u)
		return G.Edg[e].vertex2;
	else
		return G.Edg[e].vertex1;
}

int IsIntheQ(int z, Heap* h, int idx) {   // ť(�� �迭) �ȿ� ���� z�� �ִ��� Ȯ��  (�ʱ� z=2, idx=5)
	int i;

	for (i = 1; i < idx; i++) {    // �����ϸ� 1 ��ȯ
		if (h[i].key == z)
			return 1;
	}

	return 0;   // ������ 0 ��ȯ
}

void DijkstraShortestPaths() {   // Dijkstra �˰���
	int i, u, z;
	Heap* heap;
	Incidence* p;

	for (i = 1; i <= n; i++) {   // �׷��� G�� ��� �����鿡 ���Ͽ�
		G.Vert[i].dist = INF;     // �Ÿ��� ��� ���Ѵ��,
	}
	G.Vert[s].dist = 0;   // ��� ������ 1�� ����

	heap = buildHeap();    // �� ����

	i = n;
	while (i > 0) {     // ť�� �� ������ �ݺ�
		u = removeMin(heap, i);  // �� �迭�� ù ��° ���Ҹ� �����ϰ�, ������ ������ �����Ͽ� u�� ����

		p = G.Vert[u].head->next;    // p�� �������̸�, ����u�� ��������Ʈ(head ���� ���)�� ����Ŵ
		while (p != NULL) {    // ���� u�� ��������Ʈ�� ó������ ������ �f�´� (u�� �پ��ִ� �������� ��� �f�´�)
			z = Opposite(u, p->edge);    // z�� ����u�� �������� �̾��� �ݴ��� ����
			if (IsIntheQ(z, heap, i)) {    // ���� z�� ť�� ����ִٸ�
				if (G.Vert[u].dist + G.Edg[p->edge].weight < G.Vert[z].dist) {   // �ٸ� ������ ���� z�� �����ϴ°� ���� u�� ���� z�� �����ϴ� ���� �Ÿ��� �� ª����
					G.Vert[z].dist = G.Vert[u].dist + G.Edg[p->edge].weight;   // d(z)�� ����

					replaceKey(z, G.Vert[u].dist + G.Edg[p->edge].weight, heap, i);    // ������Ʈ �� z�� dist�� �� �迭���� �ݿ�
				}
			}
			p = p->next;
		}
		i--;
	}
}

void replaceKey(int z, int w, Heap* h, int last) {    // �� �迭����, �ٲ� dist�� ������Ʈ
	int i;

	for (i = 1; i < last; i++) {    // (���� ����� 1 �پ����Ƿ�, last�� �������� �ʴ´�)
		if (h[i].key == z) {     // Ű ���� z�� ���Ҹ� ã�Ƽ�
			h[i].dist = w;     // dist�� ������Ʈ
			break;
		}
	}

	upHeap(h, i);     // �� �迭 ���� z�� ��ġ ����
}

void upHeap(Heap* h, int idx) {   // ������ �Ӽ� ����   (�ʱ� idx=2)
	if (idx == 1)      // z�� ��Ʈ����̸� ����
		return;
	if (h[idx].dist >= h[idx / 2].dist)    // �� �Ӽ� ���谡 �ȵǸ� ���� (�ڽ� dist �� >= �θ� dist ��)
		return;

	swap(&h[idx], &h[idx / 2]);     // ���Ӽ��� ����Ǹ� (�ڽĳ���� dist ���� �� ���� ���), �θ� ���� ��ġ ��ȯ

	upHeap(h, idx / 2);      // ����Ͽ� ������ �Ӽ� ����
}

int main() {
	int i;

	scanf("%d %d %d", &n, &m, &s);      // n�� ��������, m�� �������� (n,m�� ��������)

	Buildgraph();

	DijkstraShortestPaths();

	for (i = 1; i <= n; i++) {
		if (G.Vert[i].dist > 0 && G.Vert[i].dist < 30000)
			printf(" %d %d\n", G.Vert[i].name, G.Vert[i].dist);
	}

	return 0;
}