#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct incidence {     // ��������Ʈ ����ü
	int edge;
	struct Incidence* next;
}Incidence;

typedef struct vertex {    // ���� ����ü
	int name;
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
	int weight;
}Heap;

typedef struct disjoint {      // �и����� ����ü
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


void Buildgraph() {     // �׷��� �����
	int i, v1, v2, w;

	scanf("%d %d", &n, &m);      // n�� ��������, m�� �������� (n,m�� ��������)

	G.Vert = (Vertex*)malloc((n + 1) * sizeof(Vertex));   // �׷����� �����迭 ũ�� �Ҵ� (���Ǹ� ���� idx 1���� ����)
	G.Edg = (Edge*)malloc(m * sizeof(Edge));    // �׷����� �����迭 ũ�� �Ҵ�

	for (i = 1; i <= n; i++) {  // �����迭�� ���� �����ϱ� (���Ǹ� ���� �����迭�� 1���� ����)
		G.Vert[i].name = i;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);

		G.Edg[i].vertex1 = v1;     // �����迭�� ���� �����ϱ� (����ü ����)
		G.Edg[i].vertex2 = v2;
		G.Edg[i].weight = w;
	}
}

Disjoint* buildDisjoint() {   // �и����� ���� �����
	int i;

	set = (Disjoint*)malloc(n * sizeof(Disjoint));

	for (i = 0; i < n; i++) {   // ������ ���� n��: ���� �ϳ��� ���� �ϳ��� ���Եǵ��� ������ n�� �����.
		set[i].head = (Incidence*)malloc(sizeof(Incidence));
		set[i].head->edge = i + 1;
		set[i].head->next = NULL;
		set[i].size = 1;   // ��� ������ ����� 1�� �ʱ�ȭ
	}

	return set;
}


Heap* buildHeap() {    // �� ����
	int i, cnt;
	Heap* h;

	h = (Heap*)malloc((m + 1) * sizeof(Heap));      // �� h�� ũ�� �Ҵ�

	for (i = 1; i <= m; i++) {      // 
		h[i].key = i;    // ���Ǹ� ���� ���� key�� 1���� ����
		h[i].weight = G.Edg[i - 1].weight;    // ���� weight�� �����迭�� weight ���� ���ʴ�� ����  
	}

	for (i = m / 2; i >= 1; i--) {
		downHeap(h, i, m);
	}

	return h;
}

void downHeap(Heap* h, int i, int last) {     // ���ǼӼ� ����
	int left, right;                            // ���⼭ ���ǼӼ�: �θ��� dist <= �ڽ��� dist, ��������Ʈ��
	int min;

	left = 2 * i;     // left�� ���� �ڽ�
	right = 2 * i + 1;    // right�� ������ �ڽ�

	if (left > last)   // ���� �ִ� ũ�⺸�� ũ�� ����
		return;


	// �� �ڽ��� weight ���� ���Ͽ� �� ���� weight���� ���� �ڽ��� min���� �����Ѵ�.
	min = left;    // left�� �ּҰ����� 
	if (right <= last) {     // right�� �ִ밪���� �۰ų� ���� ��
		if (h[right].weight < h[left].weight)    // ������ �����ϸ�  
			min = right;                    // right�� �ּҰ�����
	}

	if (h[i].weight <= h[min].weight)     // �ڱ��ڽ��� weight ���� �ڽ��� weight �� ���� �۰ų� ���ٸ� ����(���ǼӼ� ����) 
		return;

	swap(&h[i], &h[min]);   // �ƴϸ� �� �迭���� ��ġ�� �¹ٲ۴�
	downHeap(h, min, last);     // ���
}

void swap(Heap* a, Heap* b) {    // �� �迭���� �� ������ ��ġ �¹ٲٱ�
	Heap temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int Find(int findV) {   // ����v�� ����ִ� ������ ã�Ƽ� ���� �ε��� ��ȯ // 2 4
	int i;
	Incidence* p;

	for (i = 0; i < n; i++) {

		p = set[i].head;     // �� ������ ��带 ����Ű�� p
		while (p != NULL) {    // ���տ� ���Ե� ���� Ž��
			if (G.Vert[p->edge].name == findV)    // ���տ� ����v�� ���ԵǾ�������, ������ �ε��� ��ȯ
				return i;

			p = p->next;   // ���� ���� ��ȸ
		}
	}
	return -1;
}

void Union(int v1, int v2) {    // �� ���� ���� (�и����� ����Ʈ ����)
	int i, temp;

	if (set[v1].size < set[v2].size) {   // v1�� ������ ũ�� > v2������ ũ�Ⱑ �ǵ��� �����Ͽ�, ���Ұ� ���� ������ ���Ұ� ���� �������� �̵�
		temp = v2;
		v2 = v1;
		v1 = temp;
	}

	while (1) {   // v2�� ������ ���Ұ� �� ������ �ݺ�
		i = delFirst(v2);    // v2 ���� ����Ʈ�� �� ���� ���(����)�� i�� ����

		if (i == -1)    // v2 ������ ����Ʈ�� ��ԵǸ� ����
			break;

		addFirst(v1, i);    // ����i�� v1 ���տ� ���Խ�Ų��
	}
	set[v2].head = NULL;    // v2���� ����
}

int delFirst(int v2) {     // v2 ���� ����Ʈ�� �� ���� ���(����)�� ���� �� ��ȯ�ϴ� �Լ�
	int temp;

	if (set[v2].head == NULL)    // ����Ʈ�� ��������� -1 ��ȯ
		return -1;
	temp = set[v2].head->edge;
	set[v2].head = set[v2].head->next;     // ù ��� ���� �� �ι�° ��带 ��忡 �����Ų��
	set[v2].size--;   // ���� v2�� ũ�� 1 ����

	return temp;    // ������ ���(����) ��ȯ
}

void addFirst(int v1, int idx) {   // v1���� ����Ʈ�� �� �� ��忡 ���� ���(����idx) ���� 
	Incidence* newNode;

	newNode = (Incidence*)malloc(sizeof(Incidence));    // ��� newNode ���� �� �Ҵ�

	newNode->edge = idx;    // newNode�� edge�� idx�� ����
	newNode->next = set[v1].head;     // newNode�� next�� v1���� ����Ʈ�� ��� ��带 ����
	set[v1].head = newNode;    // v1���� ����Ʈ�� ��� ��带 newNode�� ����
	set[v1].size++;  // ���� v1�� ũ�� 1 ����
}

void KruskalMST() {
	int v1, v2, u, i, cnt;
	int sumWeight = 0;
	Heap* heap;

	heap = buildHeap();
	set = buildDisjoint();

	i = m;
	while (i > 0) {
		u = removeMin(heap, i);    // ���� ��Ʈ��带 ���� �� Ű �� ��ȯ

		v1 = Find(G.Edg[u - 1].vertex1);     // ť(��)���� ��ȯ�� ������ ����1�� Find�Լ��� �ִ´� (������ �ε��� ��ȯ)
		v2 = Find(G.Edg[u - 1].vertex2);      // ť(��)���� ��ȯ�� ������ ����2�� Find�Լ��� �ִ´� (������ �ε��� ��ȯ)

		if (v1 != v2) {   // v1�� v2�� ������ �ε����� �ٸ��� (���� �ٸ� �����̸�)
			sumWeight += G.Edg[u - 1].weight;    // �� ���Կ� ���� ���Ը� ���� ��
			printf(" %d", G.Edg[u - 1].weight);
			Union(v1, v2);       // �� ������ ���ս�Ų��
		}
		i--;
	}

	printf("\n%d", sumWeight);
}

int removeMin(Heap* h, int i) {   // i�� �� �迭�� ������ ������ �ε���
	Heap temp;
	int root = 1;

	temp = h[root];    // �� �迭�� ù��° ���� (root�̸�, �ּ� weight���� ����)�� ����
	swap(&h[root], &h[i]);      // ù��° ���ҿ� ������ ������ ��ġ�� �ٲ۴�

	i--;     // ���� ������ ���� (�ּ� weight���� ����)�� �����Ѵ�
	downHeap(h, root, i);       // ���Ӽ� ������ ���� downHeap ����

	return temp.key;      // ���� �� ������ key�� ����
}

int main() {

	Buildgraph();

	KruskalMST();

	return 0;
}