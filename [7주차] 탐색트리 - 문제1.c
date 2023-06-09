#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	int height;
	struct node* parent;
	struct node* lchild;
	struct node* rchild;
}Node;

int isExternal(Node* w);
int isInternal(Node* w);
Node* sibling(Node* w);
Node* inOrderSucc(Node* w);
Node* reduceExternal(Node* z);
int removeElement(Node* w, int k);
Node* treeSearch(Node* v, int k);
Node* expandExternal(Node* w);
int findElement(Node* root, int k);
void insertItem(Node* root, int k);
void preorderTraversal(Node* pt);

Node* getNode() {
	Node* node = (Node*)malloc(sizeof(Node));

	node->parent = NULL;
	node->lchild = NULL;
	node->rchild = NULL;

	return node;
}

Node* root = NULL;

Node* sibling(Node* w) {
	if (w->parent == NULL)
		return NULL;
	if (w->parent->lchild == w)
		return w->parent->rchild;
	else
		return w->parent->lchild;

}

Node* inOrderSucc(Node* w) {
	w = w->rchild;

	if (isExternal(w))
		return NULL;
	while (isInternal(w->lchild))  // w�� ���� �ڽ��� �ܺγ�尡 �ƴϸ�
		w = w->lchild;

	return w;
}

Node* reduceExternal(Node* z) {
	Node* w, * zs, * g;

	w = z->parent;
	zs = sibling(z);

	if (w->parent == NULL) {	// w�� ��Ʈ�̸�
		root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lchild)
			g->lchild = zs;
		else  // w == g->rchild
			g->rchild = zs;
	}

	free(z);
	free(w);

	return zs;
}

int removeElement(Node* root, int k) {
	Node* w, * y, * z, * zs;
	int e, NoSuchKey = -1;

	w = treeSearch(root, k);
	if (isExternal(w))
		return NoSuchKey;

	e = w->key;
	z = w->lchild;

	if (!isExternal(z))	  // �ܺγ�尡 �ƴϸ�
		z = w->rchild;

	if (isExternal(z))     // �ܺγ���̸�
		zs = reduceExternal(z);
	else {
		y = inOrderSucc(w);
		z = y->lchild;
		w->key = y->key;
		zs = reduceExternal(z);
	}

	return e; // ������ ����� Ű�� ��ȯ
}

int isExternal(Node* w) {
	if ((w->lchild == NULL) && (w->rchild == NULL))    // �ش� ��尡 �ڽ��� ������(�ܺγ���̸�)
		return 1;	// 1 ����
	else
		return 0;	// 0 ����
}

int isInternal(Node* w) {
	if ((w->lchild != NULL) || (w->rchild != NULL))     // �ش� ��尡 �ڽ��� �ϳ� �̻� ������(���γ���̸�)
		return 1;	// 1 ����
	else
		return 0;   // �ڽ��� ������(�ܺγ���̸�) 0 ����
}

int findElement(Node* root, int k) {	// ��Ʈ���� ���, ������, Ű �� k�� ������ ����� ���� ��ȯ 
	Node* w;
	int NoSuchKey = -1;

	w = treeSearch(root, k);	// Ʈ������ Ű �� k�� ���� ��带 ��ȯ�ؼ� ��� w�� ����

	if (isExternal(w))	   // ��� w�� �ܺγ���̸�(�ڽ��� ������) 
		return NoSuchKey;     // Ư���� ��ȯ
	else
		return w->key;		// ���γ���̸� Ű �� ��ȯ
}

Node* treeSearch(Node* v, int k) {		// Ʈ������ Ű �� k�� ���� ��� ��ȯ
	if (isExternal(v))	// ��� v�� �ܺγ���̸� 
		return v;	// ��� v ��ȯ
	if (k == v->key)	// ��� v�� Ű �� k�� ���� ���γ���̸�
		return v;	// ��� v ��ȯ
	else if (k < v->key)	// Ű �� k�� ���v��  Ű ������ ������ 
		return treeSearch(v->lchild, k);	// ���v�� ���� �ڽ��� �μ��� ���
	else  //		// Ű �� k�� ���v��  Ű ������ ũ��
		return treeSearch(v->rchild, k);	// ���v��  �ڽ��� �μ��� ���
}

void insertItem(Node* root, int k) {	// Ʈ���� ���� k ����
	Node* w;   // �� ��� ����

	w = treeSearch(root, k);	// w�� k�� ���ҷ� �ϴ� ���� ����


	if (isInternal(w))    // w�� ���γ���̸� ����(���� ����x)
		return;
	else {		// w�� �ܺγ���̸�,
		w->key = k;		/// Ű �� ���� �Ϸ�
		w = expandExternal(w);	// w�� �ܺγ�� ����
		return;
	}
}

Node* expandExternal(Node* w) {		// �ܺγ�� w�� ���γ��� ����(�ܺγ�� Ȯ��)
	Node* l, * r;

	l = getNode();       // ���l ����
	r = getNode();       // ���r ����

	w->lchild = l;		 // w�� �ڽ��� �ܺγ�� l,r�� ���� 
	w->rchild = r;
	w->height = 1;		 // w�� ���̸� 1�� ������Ʈ

	l->parent = w;		 // l�� �θ�� w 
	l->height = 0;		 // �ܺγ�� ���� �ʱ�ȭ

	r->parent = w;       // r�� �θ� w
	r->height = 0;		 // �ܺγ�� ���� �ʱ�ȭ

	return w;
}

void preorderTraversal(Node* pt) {		// ��ȸ��ȸ�� ���
	if (isExternal(pt)) {
		return;
	}

	printf(" %d", pt->key);

	preorderTraversal(pt->lchild);
	preorderTraversal(pt->rchild);
}

int main() {
	int key, key2, result, loop = 1;
	char ch;

	root = getNode();   // �������� ������ ���

	while (loop) {
		scanf("%c", &ch);

		switch (ch) {
		case 'i':
			scanf("%d", &key);
			getchar();
			insertItem(root, key);
			break;

		case 'd':
			scanf("%d", &key);
			getchar();

			key2 = removeElement(root, key);

			if (key2 == -1)
				printf("X\n");
			else
				printf("%d\n", key2);
			break;

		case 's':
			scanf("%d", &key);
			getchar();

			result = findElement(root, key);

			if (result == -1)   // NoSuchKey
				printf("X\n");
			else
				printf("%d\n", result);
			break;

		case 'p':
			preorderTraversal(root);
			printf("\n");
			break;

		case 'q':
			loop = 0;
			break;
		}
	}

	return 0;
}