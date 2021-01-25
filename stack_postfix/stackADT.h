#ifndef STACKADT_H
#define STACKADT_H

typedef int Item; //정수를 사용하는 stack이라서 별명 item으로 관리
// 나중에 데이터 타입이 바뀌면 여기만 수정하면 된다. 코드의 재사용에 유리
// ex) typedef float Item

typedef struct stack_type* Stack;
// stack_type* 타입을 Stack으로 별명 설정

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