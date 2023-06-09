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
	if ((w->lchild == NULL) && (w->rchild == NULL))    // 해당 노드가 자식이 없으면(외부노드이면)
		return 1;	// 1 리턴
	else
		return 0;	// 0 리턴
}

int isInternal(Node* w) {
	if ((w->lchild != NULL) || (w->rchild != NULL))     // 해당 노드가 자식이 하나 이상 있으면(내부노드이면)
		return 1;	// 1 리턴
	else
		return 0;   // 자식이 없으면(외부노드이면) 0 리턴
}

int findElement(Node* root, int k) {	// 루트에서 출발, 하향경로, 키 값 k를 가지는 노드의 원소 반환 
	Node* w;
	int NoSuchKey = -1;

	w = treeSearch(root, k);	// 트리에서 키 값 k를 갖는 노드를 반환해서 노드 w에 저장

	if (isExternal(w))	   // 노드 w가 외부노드이면(자식이 없으면) 
		return NoSuchKey;     // 특별값 반환
	else
		return w->key;		// 내부노드이면 키 값 반환
}

Node* treeSearch(Node* v, int k) {		// 트리에서 키 값 k를 갖는 노드 반환
	if (isExternal(v))	// 노드 v가 외부노드이면 
		return v;	// 노드 v 반환
	if (k == v->key)	// 노드 v가 키 값 k를 갖는 내부노드이면
		return v;	// 노드 v 반환
	else if (k < v->key)	// 키 값 k가 노드v의  키 값보다 작으면 
		return treeSearch(v->lchild, k);	// 노드v의 왼쪽 자식을 인수로 재귀
	else  //		// 키 값 k가 노드v의  키 값보다 크면
		return treeSearch(v->rchild, k);	// 노드v의  자식을 인수로 재귀
}

void insertItem(Node* root, int k) {	// 트리에 원소 k 삽입
	Node* w;   // 새 노드 정의

	w = treeSearch(root, k);	// w를 k를 원소로 하는 노드로 설정


	if (isInternal(w))    // w가 내부노드이면 종료(높이 변함x)
		return;
	else {		// w가 외부노드이면,
		w->key = k;		/// 노드에 9, 31 66 삽입 됨
		w = expandExternal(w);	// w의 외부노드 생성
		searchAndFixAfterInsertion(w);	  // 삽입 후 개조가 필요하면 개조 수행
		return;
	}
}

Node* expandExternal(Node* w) {		// 외부노드 w를 내부노드로 변경(외부노드 확장)
	Node* l, * r;

	l = getNode();       // 노드l 생성
	r = getNode();       // 노드r 생성

	w->lchild = l;		 // w의 자식을 외부노드 l,r로 설정 
	w->rchild = r;
	w->height = 1;		 // w의 높이는 1

	l->parent = w;		 // l의 부모는 w 
	l->height = 0;

	r->parent = w;       // r의 부모도 w
	r->height = 0;

	return w;
}

int maxAorB(int a, int b) {		// 두 수를 비교해서 큰 수를 반환
	if (a >= b)
		return a;
	else
		return b;
}

int updateHeight(Node* z) {		// 높이 업데이트 여부를 판단하여, 업데이트가 필요하면 수행 후 1 반환
	int h;
	Node* left, * right;	// 새로운 노드  left, right 정의

	left = z->lchild;	 // left와 right는 각각 노드 w의 자식이다
	right = z->rchild;

	h = maxAorB(left->height, right->height) + 1;  //노드 left와 right의 높이를 비교하여 큰 높이를 h에 저장

	if (h != z->height) {
		z->height = h;
		return 1;	// 업데이트 했음
	}
	else
		return 0;	// 업데이트 안했음
}

int isBalanced(Node* z) {	// 해당 노드의 높이균형 검사. 균형이 맞으면 1, 안맞으면 0 반환
	Node* left, * right;
	int result = 0;

	left = z->lchild;	// 해당 노드의 자식노드를 새 노드 left 와 right로 지정
	right = z->rchild;

	if (left->height >= right->height)			// left와 right의 높이를 비교하고, 두 높이의 차를 result에 저장
		result = left->height - right->height;
	else
		result = right->height - left->height;

	if (result < 2)   // left와 right의 높이균형이
		return 1;   // 맞으면 1 반환

	else
		return 0;   // 안맞으면 0 반환
}

void searchAndFixAfterInsertion(Node* w) {   // 노드 삽입 후 높이 균형이 안맞으면 노드개조
	Node* x, * y, * z;	  // 새로운 노드들 생성

	w->lchild->height = 0;		// w는 내부노드이고, 자식들은 외부노드이다
	w->rchild->height = 0;
	w->height = 1;

	if (w->parent == NULL)	   // 만약 w가 루트이면
		return;			// 함수 종료
	z = w->parent;		 // w의 부모가 있다면, z를 w의 부모로 설정

	while (updateHeight(z) == 1 && isBalanced(z) == 1) {     // w의 부모인 z가 높이 업데이트를 수행했고 높이 균형이 맞는 상태이면 수행
		if (z->parent == NULL)		// 만약 z가 트리의 루트이면
			return;		// 함수 종료

		z = z->parent;		// z는 위로  한 층 올라감
	}

	if (isBalanced(z) == 1)		// 노드 z의 높이 균형이 맞으면
		return;		// 함수 종료

	if (z->lchild->height > z->rchild->height)    // y를 z의 두 자식 중 높이가 큰 자식으로 설정
		y = z->lchild;
	else
		y = z->rchild;

	if (y->lchild->height > y->rchild->height)		// x를 y의 두 자식 중 높이가 큰 자식으로 설정
		x = y->lchild;
	else
		x = y->rchild;

	restructure(x, y, z);		// 세 노드의 개조 수행

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

	if (z->parent == NULL) {	// z가 루트인 경우
		root = b;			// 트리의 루트를 b로 설정
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

	return b;   // 개조된 세 노드중 루트를 반환
}

void preorderTraversal(Node* pt) {		// 전회순회로 출력
	if (isExternal(pt))
		return;

	printf(" %d", pt->key);

	preorderTraversal(pt->lchild);
	preorderTraversal(pt->rchild);
}

int main() {
	int key, result, loop = 1;
	char ch;

	root = getNode();   // 전역으로 선언한 노드

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