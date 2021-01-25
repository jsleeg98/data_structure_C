#include "stack.h"
#define MAX_CAPACITY 100

char stack[MAX_CAPACITY];
int top = -1; // 아무것도 없는 상태 -1로 초기화

struct node {
	char* data;
	struct node* next;
};
typedef struct node Node;

Node* top = NULL;

void push(char ch) {
	if (is_full()) {
		return;
	}
	top++;
	stack[top] = ch;
}

char pop() {
	char tmp = stack[top];
	top--;
	return tmp;
}

char peek() {
	return stack[top];
}

int is_empty() {
	return top == -1;
}

int is_full() {
	return top == MAX_CAPACITY - 1;
}


