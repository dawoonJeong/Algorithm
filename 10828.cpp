#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Node{
	int data;
	struct Node *next;
}Node;

typedef struct Stack{
	Node *top;
	int size;
}Stack;

//13500원씩 
Node *createNode(int data){
	Node *n;
	n = (Node*)malloc(sizeof(Node));
	n->data = data;
	n->next = NULL;
	return n;
}
Stack *initStack(){
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->top = NULL;
	s->size = 0;
	return s;
}
int isEmptyStack(Stack *s){
	return (s->size == 0);
}

void push(Stack *s, Node *n){
	if (isEmptyStack(s)){
		s->top = n;
		s->size++;
	}
	else{
		n->next = s->top;
		s->top = n;
		s->size++;
	}
}

int pop(Stack *s){
	int result;
	if (!isEmptyStack(s)){
		result = s->top->data;
		s->top = s->top->next;
		s->size--;
	}
	else{
		result = -1;	// stack에 주어지는 값은 1<=100,000이므로. 비어있을 경우 0을 리턴.
	}
	return result;
}
int top(Stack *s){
	int result;
	if (!isEmptyStack(s)){
		result = s->top->data;
	}
	else
		result = -1;
	return result;
}

int main(){
	char input[30];
	int N;	// 명령의 수
	int data = 0;
	Stack *s = initStack();
	scanf("%d", &N);
	while (N > 0){
		scanf("%s", input);
		if (strcmp(input, "push")==0){
			scanf("%d", &data);
			push(s, createNode(data));
		}
		else if (strcmp(input, "top")==0){
			
			printf("%d\n", top(s));
		}
		else if (strcmp(input, "size") == 0){
			printf("%d\n", s->size);
		}
		else if (strcmp(input, "pop") == 0){
			printf("%d\n", pop(s));
		}
		else if (strcmp(input, "empty") == 0){
			printf("%d\n", isEmptyStack(s));
		}
		else{
			printf("wrong input, try again\n");
			N++;
		}
		N--;
	}

	free(s);
	return 0;
}