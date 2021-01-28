#include <stdio.h>
#include <stdlib.h>
#include "queueADT_circular.h"

#define INIT_CAPACITY 100

struct node {
	Item data;
	struct node* next;
};

struct queue_type {
	Item* contents;
	int front;
	int rear;
	int size;
	int capacity;
};

void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

int get_size(Queue q)
{
	return q->size;
}

Queue create()
{
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q = NULL) {
		terminate("Error in create: queue could not be created");
	}
	q->contents = (Item*)malloc(INIT_CAPACITY * sizeof(Item));
	if (q->contents = NULL) {
		free(q);
		terminate("Error in create: queue could not be created.");
	}
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = INIT_CAPACITY;
	return q;
}

void destroy(Queue q)
{
	free(q->contents);
	free(q);
}

void make_empty(Queue q) {
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty(Queue q)
{
	return q->front == 0;
}

bool is_full(Queue q)
{
	return q->size == q->capacity;
}

void enqueue(Queue q, Item i)
{
	if (is_full(q))
		reallocate(q);

	q->rear = (q->rear + 1) % q->capacity; // 끝에 도달하면 0으로 설정하는 것
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q)
{
	if (is_empty(q))
		terminate("Error in dequeue: queue is empty.");
	Item result = q->contents[q->front];
	q->front = (q->front + 1) % q->capacity; //끝에 도달하면 0으로 설정
	q->size--;
	return result;
}

Item peek(Queue q)
{
	if (is_empty(q))
		terminate("Error in peek: queue is empty.");
	return q->contents[q->front];
}

void reallocate(Queue q)
{
	Item* tmp = (Item*)malloc(2 * q->capacity * sizeof(Item));
	if (tmp == NULL) {
		terminate("Error in create; queue could not be expanded.");
	}

	int j = q->front;
	// 순환처리되 공간을 두배로 할 때는 다시 맨 앞부터 저장해야한다.
	for (int i = 0; i < q->size; i++) {
		tmp[i] = q->contents[j]; 
		j = (j + 1) % q->capacity; // j는 순환 처리
	}
	free(q->contents);

	q->front = 0; // 맨 앞이 맨 처음
	q->rear = q->size - 1; // 맨 뒤가 맨뒤
	q->contents = tmp;
	q->capacity *= 2; // 공간 2배
}