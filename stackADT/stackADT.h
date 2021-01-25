#ifndef STACKADT_H
#define STACKADT_H

typedef int Item; //������ ����ϴ� stack�̶� ���� item���� ����
// ���߿� ������ Ÿ���� �ٲ�� ���⸸ �����ϸ� �ȴ�. �ڵ��� ���뿡 ����
// ex) typedef float Item

typedef struct stack_type* Stack;
// stack_type* Ÿ���� Stack���� ���� ����

Stack create();
void destory(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
bool is_full(Stack s);
Item pop(Stack s);
Item peek(Stack s);
void reallocate(Stack s);

#endif