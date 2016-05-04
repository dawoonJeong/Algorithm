#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
	int key;
	struct TreeNode *left, *right;
}TreeNode;

void insert_node(TreeNode **root, int key){
	TreeNode *p, *t; // p는 부모노드, t는 현재노드
	TreeNode *n;	// n은 새로운 노드

	t = *root;
	p = NULL;

	//탐색을 먼저 수행
	while (t != NULL){	//자식노드가 NULL이 될 때까지(leaf노드까지)
		if (key == t->key) return;	// BST의 특징: 키값 중복 허용 x 입력 키가 이미 존재한다는 의미임.
		p = t;	//자식노드를 부모노드로 하고
		//자식노드를 전진
		if (key < t->key)
			t = t->left;
		else
			t = t->right;
	}

	// 삽입할 노드 생성
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL)return;

	//데이터 복사
	n->key = key;
	n->left = n->right = NULL;

	//부모노드와 링크 연결
	if (p != NULL)
		if (key < p->key)
			p->left = n;
		else
			p->right = n;
	else
		*root = n;	
}
//삭제 함수
void delete_node(TreeNode **root, int key){	// 1) 해당 key를 갖는 노드를 찾고 2)삭제.
	TreeNode *p, *child, *succ, *succ_p, *t;

	//key를 갖는 노드 t를 탐색, p는 t의 부모노드
	p = NULL;
	t = *root;
	//key를 갖는 노드 t를 탐색
	while (t != NULL && t->key != key){
		p = t;//자식노드를 부모가
		t = (key < t->key) ? t->left : t->right;
	}
	//탐색이 종료된 시점에 t가 NULL이면 트리 안에 key가 없음
	if (t == NULL){
		printf("key is not in the tree");
		return;
	}

	//첫번째 경우: 단말노드인 경우
	if ((t->left == NULL) && (t->right == NULL)){
		if (p != NULL){
			//부모노드의 자식필드를 NULL로 만든다.
			if (p->left == t)//삭제하려는 게 왼쪽 노드면
				p->left = NULL;
			else
				p->right = NULL;
		}
		else
			*root = NULL;	// 만약 부모노드가 NULL이면 삭제되는 노드가 루트.
	}
	// 두번째 경우: 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)){
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL){
			if (p->left == t)
				p->left = child; // 부모를 자식과 연결
			else
				p->right = child;
		}
		else
			*root = child;
	}
	//세번째 경우: 두개의 자식을 갖는 경우
	else{
		//오른쪽 서브트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->right;
		//후계자를 찾아서 계속 왼쪽으로 이동한다. : 서브 트리 내에서 가장 작은 값(=후계자.succ)을 찾기위함
		while (succ->left != NULL){
			succ_p = succ;
			succ = succ->left;
		}
		//후계자의 부모와 자식을 연결
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//후계자가 가진 키값을 현재 노드에 복사
		t->key = succ->key;
		//원래의 후속자 삭제
		t = succ;
	}
	free(t);
}

 //탐색
TreeNode *search(TreeNode *node, int key){
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

void preorder(TreeNode *root){
	if (root){
		preorder(root->left);
		printf("%d ", root->key);		
		preorder(root->right);
	}
}

int get_height(TreeNode *root){
	int height = 0;
	if (root != NULL){
		height = 1 + ((get_height(root->left) > get_height(root->right)) ? get_height(root->left) : get_height(root->right));
	}
	return height;
}

int get_count(TreeNode *t){	// total
	int count = 0;
	if (t != NULL){
		count = 1 + get_count(t->left) + get_count(t->right);
	}
	return count;
}

int get_max(TreeNode *t){	// 이진트리에서 노드값들 중 최대값 반환
	int max;
	if (t == NULL)
		return 0;
	max = t->key;
	max = (t->key > get_max(t->left)) ? max : get_max(t->left);
	max = (t->key > get_max(t->right)) ? max : get_max(t->right);
	return max;
}
int get_min(TreeNode *t){	// 이진트리에서 노드값들 중 최소값을 반환
	int min;
	if (t == NULL)
		return 100;
	min = t->key;
	min = (t->key < get_min(t->left)) ? min : get_min(t->left);
	min = (t->key < get_min(t->right)) ? min : get_min(t->right);
	return min;
}

void main(){
	char menu;
	int data;
	TreeNode *root=NULL;
	while (1){
		fflush(stdin);
		printf("Enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), m(ax), n(min), q(uit):");
		scanf("%c", &menu);
		switch (menu){
		case 'i':
			printf("삽입할 key값 입력:");
			scanf("%d", &data);
			insert_node(&root, data);
			break;
		case 'd':
			printf("삭제할 key값 입력:");
			scanf("%d", &data);
			delete_node(&root, data);
			break;
		case 's':
			printf("탐색할 key값 입력:");
			scanf("%d", &data);
			printf("%s\n", (search(root, data) == NULL) ? "없음":"있음");
			break;
		case 'p':
			preorder(root);
			printf("\n");
			break;
		case 'h':
			printf("트리의 높이는 %d\n", get_height(root));
			break;
		case 'c':
			printf("노드의 개수는 %d\n", get_count(root));
			break;
		case 'm':
			printf("가장 큰 값은 %d\n", get_max(root));
			break;
		case 'n':
			printf("가장 작은 값은 %d\n", get_min(root));
			break;
		case 'q':

			return;
		}
	}


}
