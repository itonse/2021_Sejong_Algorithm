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
	while (isInternal(w->lchild))  // w의 왼쪽 자식이 외부노드가 아니면
		w = w->lchild;

	return w;
}

Node* reduceExternal(Node* z) {
	Node* w, * zs, * g;

	w = z->parent;
	zs = sibling(z);

	if (w->parent == NULL) {	// w가 루트이면
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

	if (!isExternal(z))	  // 외부노드가 아니면
		z = w->rchild;

	if (isExternal(z))     // 외부노드이면
		zs = reduceExternal(z);
	else {
		y = inOrderSucc(w);
		z = y->lchild;
		w->key = y->key;
		zs = reduceExternal(z);
	}

	return e; // 삭제한 노드의 키값 반환
}

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
		w->key = k;		/// 키 값 삽입 완료
		w = expandExternal(w);	// w의 외부노드 생성
		return;
	}
}

Node* expandExternal(Node* w) {		// 외부노드 w를 내부노드로 변경(외부노드 확장)
	Node* l, * r;

	l = getNode();       // 노드l 생성
	r = getNode();       // 노드r 생성

	w->lchild = l;		 // w의 자식을 외부노드 l,r로 설정 
	w->rchild = r;
	w->height = 1;		 // w의 높이를 1로 업데이트

	l->parent = w;		 // l의 부모는 w 
	l->height = 0;		 // 외부노드 높이 초기화

	r->parent = w;       // r의 부모도 w
	r->height = 0;		 // 외부노드 높이 초기화

	return w;
}

void preorderTraversal(Node* pt) {		// 전회순회로 출력
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

	root = getNode();   // 전역으로 선언한 노드

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