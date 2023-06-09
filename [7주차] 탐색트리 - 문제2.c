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
Node* treeSearch(Node* ts, int k);
Node* expandExternal(Node* w);
int findElement(Node* root, int k);
int maxAorB(int a, int b);
int updateHeight(Node* w);
int isBalanced(Node* w);
Node* restructure(Node* x, Node* y, Node* z);
void searchAndFixAfterInsertion(Node* w);
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
		w->key = k;		/// ��忡 9, 31 66 ���� ��
		w = expandExternal(w);	// w�� �ܺγ�� ����
		searchAndFixAfterInsertion(w);	  // ���� �� ������ �ʿ��ϸ� ���� ����
		return;
	}
}

Node* expandExternal(Node* w) {		// �ܺγ�� w�� ���γ��� ����(�ܺγ�� Ȯ��)
	Node* l, * r;

	l = getNode();       // ���l ����
	r = getNode();       // ���r ����

	w->lchild = l;		 // w�� �ڽ��� �ܺγ�� l,r�� ���� 
	w->rchild = r;
	w->height = 1;		 // w�� ���̴� 1

	l->parent = w;		 // l�� �θ�� w 
	l->height = 0;

	r->parent = w;       // r�� �θ� w
	r->height = 0;

	return w;
}

int maxAorB(int a, int b) {		// �� ���� ���ؼ� ū ���� ��ȯ
	if (a >= b)
		return a;
	else
		return b;
}

int updateHeight(Node* z) {		// ���� ������Ʈ ���θ� �Ǵ��Ͽ�, ������Ʈ�� �ʿ��ϸ� ���� �� 1 ��ȯ
	int h;
	Node* left, * right;	// ���ο� ���  left, right ����

	left = z->lchild;	 // left�� right�� ���� ��� w�� �ڽ��̴�
	right = z->rchild;

	h = maxAorB(left->height, right->height) + 1;  //��� left�� right�� ���̸� ���Ͽ� ū ���̸� h�� ����

	if (h != z->height) {
		z->height = h;
		return 1;	// ������Ʈ ����
	}
	else
		return 0;	// ������Ʈ ������
}

int isBalanced(Node* z) {	// �ش� ����� ���̱��� �˻�. ������ ������ 1, �ȸ����� 0 ��ȯ
	Node* left, * right;
	int result = 0;

	left = z->lchild;	// �ش� ����� �ڽĳ�带 �� ��� left �� right�� ����
	right = z->rchild;

	if (left->height >= right->height)			// left�� right�� ���̸� ���ϰ�, �� ������ ���� result�� ����
		result = left->height - right->height;
	else
		result = right->height - left->height;

	if (result < 2)   // left�� right�� ���̱�����
		return 1;   // ������ 1 ��ȯ

	else
		return 0;   // �ȸ����� 0 ��ȯ
}

void searchAndFixAfterInsertion(Node* w) {   // ��� ���� �� ���� ������ �ȸ����� ��尳��
	Node* x, * y, * z;	  // ���ο� ���� ����

	w->lchild->height = 0;		// w�� ���γ���̰�, �ڽĵ��� �ܺγ���̴�
	w->rchild->height = 0;
	w->height = 1;

	if (w->parent == NULL)	   // ���� w�� ��Ʈ�̸�
		return;			// �Լ� ����
	z = w->parent;		 // w�� �θ� �ִٸ�, z�� w�� �θ�� ����

	while (updateHeight(z) == 1 && isBalanced(z) == 1) {     // w�� �θ��� z�� ���� ������Ʈ�� �����߰� ���� ������ �´� �����̸� ����
		if (z->parent == NULL)		// ���� z�� Ʈ���� ��Ʈ�̸�
			return;		// �Լ� ����

		z = z->parent;		// z�� ����  �� �� �ö�
	}

	if (isBalanced(z) == 1)		// ��� z�� ���� ������ ������
		return;		// �Լ� ����

	if (z->lchild->height > z->rchild->height)    // y�� z�� �� �ڽ� �� ���̰� ū �ڽ����� ����
		y = z->lchild;
	else
		y = z->rchild;

	if (y->lchild->height > y->rchild->height)		// x�� y�� �� �ڽ� �� ���̰� ū �ڽ����� ����
		x = y->lchild;
	else
		x = y->rchild;

	restructure(x, y, z);		// �� ����� ���� ����

	return;
}

Node* restructure(Node* x, Node* y, Node* z) {
	Node* a, * b, * c, * T0, * T1, * T2, * T3;

	if (z->key < y->key && y->key < x->key) {		// z < y < x
		a = z, b = y, c = x;
		T0 = a->lchild, T1 = b->lchild, T2 = c->lchild, T3 = c->rchild;
	}
	else if (x->key < y->key && y->key < z->key)     // x < y < z
	{
		a = x, b = y, c = z;
		T0 = a->lchild, T1 = a->rchild, T2 = b->rchild, T3 = c->rchild;
	}
	else if (z->key < x->key && x->key < y->key)      // z < x < y
	{
		a = z, b = x, c = y;
		T0 = a->lchild, T1 = b->lchild, T2 = b->rchild, T3 = c->rchild;
	}
	else      // y < x < z
	{
		a = y, b = x, c = z;
		T0 = a->lchild, T1 = b->lchild, T2 = b->rchild, T3 = c->rchild;
	}

	if (z->parent == NULL) {	// z�� ��Ʈ�� ���
		root = b;			// Ʈ���� ��Ʈ�� b�� ����
		b->parent = NULL;
	}
	else if (z->parent->lchild == z) {
		z->parent->lchild = b;
		b->parent = z->parent;
	}
	else {	 // z->parent->rchild == z
		z->parent->rchild = b;
		b->parent = z->parent;
	}

	a->lchild = T0;
	T0->parent = a;
	a->rchild = T1;
	T1->parent = a;
	updateHeight(a);

	c->lchild = T2;
	T2->parent = c;
	c->rchild = T3;
	T3->parent = c;
	updateHeight(c);

	b->lchild = a;
	a->parent = b;
	b->rchild = c;
	c->parent = b;
	updateHeight(b);

	return b;   // ������ �� ����� ��Ʈ�� ��ȯ
}

void preorderTraversal(Node* pt) {		// ��ȸ��ȸ�� ���
	if (isExternal(pt))
		return;

	printf(" %d", pt->key);

	preorderTraversal(pt->lchild);
	preorderTraversal(pt->rchild);
}

int main() {
	int key, result, loop = 1;
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