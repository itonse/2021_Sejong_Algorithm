#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int element;
	struct Node* next;
}Node;

typedef struct vertex {
	char name;		// ������ �̸�
	int indegree;		// ��������(���԰��� ����)
	Node* inEdges;		// ���Ժ�����������Ʈ
	Node* outEdges;		// ���������������Ʈ

}Vertex;

typedef struct edge {
	int origin;   // ��� ����
	int destination;   // ���� ����
}Edge;

typedef struct graph {
	Vertex* vertices;
	Edge* edges;
}Graph;

typedef struct Queue {   // ����ť
	int* queue;    // nũ���� �迭�� �����ϰ� �� ������
	int front;    // ����� ���� �߿��� ù ��° ����
	int rear;    // ����� ���� �߿��� ������ ����
}Queue;


Graph G;   // �������� G ����
int n;    // ���� �� 
int m;    // ���� ��
int* in;    // in[i]: ���� i�� ��������
int* topOrder;    // �������� ������� �迭 (ũ��� n+1),   topOder[0] = 1(DAG), 0(non-DAG �׷����� ����Ŭ ����) 
Queue Q;    // �������� ��⿭ (�ִ� ũ�� n)


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


Node* getNode() {    // ����Ʈ �Ҵ� �Լ�
	Node* node = (Node*)malloc(sizeof(Node));

	node->element = NULL;
	node->next = NULL;
	return node;
}

void BuildGraph() {    // �׷��� �����
	char vName, uName, wName;
	int i;

	scanf("%d", &n);
	getchar();

	G.vertices = (Vertex*)malloc(n * sizeof(Vertex));    // nũ���� �����迭 ������ �Ҵ�
	topOrder = (int*)malloc((n + 1) * sizeof(int));    // ũ�� n+1�� ������� �迭 �Ҵ�

	for (i = 0; i < n; i++) {   // �����̸� n�� �Է� 
		scanf("%c", &vName);
		getchar();
		insertVertex(vName, i);
	}

	scanf("%d", &m);
	G.edges = (Edge*)malloc(m * sizeof(Edge));

	for (i = 0; i < m; i++) {
		getchar();
		scanf("%c %c", &uName, &wName);

		insertDirectedEdge(uName, wName, i);  // i�� ���� ���� ����
	}
}

void insertVertex(char vName, int i) {   // �׷����� ���� ����.  ������ ����: name, ��������, ���԰�������Ʈ, ���Ⱓ������Ʈ
	G.vertices[i].name = vName;     // i�� ���� ���� ����
	G.vertices[i].indegree = 0;

	G.vertices[i].outEdges = getNode();   // getNode �Լ��� '����'������������Ʈ �Ҵ� + ����Ʈ �ʱ�ȭ
	G.vertices[i].inEdges = getNode();   // getNode �Լ��� '����'������������Ʈ �Ҵ� + ����Ʈ �ʱ�ȭ
}

void insertDirectedEdge(char uName, char wName, int i) {    // �׷����� ���Ⱓ�� ����
	int u, w;

	u = index(uName);
	w = index(wName);

	G.edges[i].origin = u;     // u�� ������ �������
	G.edges[i].destination = w;    // w�� ������ ��������

	addFirst(G.vertices[u].outEdges, i);     // ����u�� '����'��������Ʈ�� ���, ���� ���Լ��� i
	addFirst(G.vertices[w].inEdges, i);    // // ����w�� '����'��������Ʈ�� ���, ���� ���Լ��� i

	G.vertices[w].indegree++;     // ���� w�� �������� 1 ����
}

int index(char vName) {   // �ش� ������ �ε��� ��ȯ
	int i;

	for (i = 0; i < n; i++) {
		if (G.vertices[i].name == vName)
			return i;
	}
}

void addFirst(Node* H, int i) {    // ���� �ԷµǴ� ������ ���� ��带 '����Ʈ�� �� ��(����� ����)'�� ����
	Node* temp;

	temp = getNode();  // �� ��� ����

	temp->element = i;   // ( i�� ���� ���� ����)
	temp->next = H->next;
	H->next = temp;
}

void topologicalSort() {   // ��������
	int i, t, u, e, w;
	Node* temp;

	createQueue();    // ť �ʱ�ȭ

	in = (int*)malloc(n * sizeof(int));  // in�� �迭 ũ�� �Ҵ� (in[i]: ���� i�� ��������)

	for (i = 0; i < n; i++) {    // ���ʷ� ���԰����� ������ 0�� ������ ã�� ��, ������ȣ ������ �����ؾ� ��
		in[i] = G.vertices[i].indegree;   // i��° ���Ե� ������ ������ �迭 in�� i��° �ε����� ����
		if (in[i] == 0)     // �ʱ⿡ ���������� 0�� ��������
			enqueue(i);   // Q�� ����, (ť ��ȭ���� �˻� �ʿ�x)
	}

	t = 1;   // t�� �������

	while (!QisEmpty()) {   // ť�� ������ �ƴ� ��
		u = dequeue();   // ������ ���Ұ��� u�� ���� (���� ������ �׷����� ���Ե� ���� )
		topOrder[t] = u;     // ������� ���� ����

		t++;   // ������� �ű� ��ȣ 1 ����

		temp = G.vertices[u].outEdges->next;   // u�� ���Ⱓ���� �� ��(��� �������)�� temp�� ����
		while (temp != NULL) {   // u�� ��� '����'���� e�� ���� �ݺ�
			e = temp->element;
			w = G.edges[e].destination;     // w�� u�� ���Ⱓ�� e�� �ݴ��� ����

			in[w] = in[w] - 1;   // ���� w�� �������� 1 ����
			if (in[w] == 0)
				enqueue(w);   // w�� ���������� 0�̸� ť�� ����

			temp = temp->next;
		}
	}

	if (t <= n)   // DAG�̱� ���ؼ��� t = n+1 �̿��߸� �Ѵ�.  t <= n�� non-DAG�� ����̴�. (������� �Ȱ���, �׷����� ����Ŭ�� ����)
		topOrder[0] = 0;     // topOder�� ����ִ� ������ 0��° �ε����� 0 ����
	else
		topOrder[0] = 1;   // DAG�� ��� 1 ����(������� ����, �׷����� ����Ŭx)
}

void createQueue() {   // ť �ʱ�ȭ
	Q.queue = (int*)malloc(n * sizeof(int));  // ť�� �迭ũ�� �Ҵ�
	Q.front = -1;    // front�� rear�� �ʱ� ��ġ�� -1
	Q.rear = -1;
}

void enqueue(i) {
	if (Q.rear == -1 && Q.front == -1) {
		Q.front += 1;
		Q.rear += 1;
		Q.queue[Q.rear] = i;   // ť�� rear ��ġ�� i ����
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

int dequeue() {   // ť�� ������ �ƴ� ����
	int d;

	d = Q.queue[Q.front];    // ť���� ������ ���Ҹ� d�� ���� 
	Q.front += 1;				// front ��ġ�� �� ĭ �ڷ�

	if (Q.rear < Q.front) {    // �����ؼ� ť�� ������ �Ǵ� ��� front�� rear ��ġ �ʱ�ȭ
		Q.front = -1;
		Q.rear = -1;
	}

	return d;     // ������ ���� �� ��ȯ
}


int main() {
	int i;

	BuildGraph();

	topologicalSort();

	if (topOrder[0] == 0)    // non-DAG, ������� ����
		printf("0");
	else {    // DAG, ������� ����
		for (i = 1; i <= n; i++) {
			printf("%c ", G.vertices[topOrder[i]].name);   	 // ������� ���
		}
	}

	return 0;
}