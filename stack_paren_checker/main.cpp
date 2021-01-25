#include <stdio.h>
#include <string.h>
#include "stack.h"

#define MAX_LENGTH 100

char OPEN[] = "([{";
char CLOSE[] = ")]}";

int is_balanced(char* expr);
int is_open(char ch);
int is_close(char ch);

int main()
{
	char expr[MAX_LENGTH];
	scanf("%s", expr);
	if (is_balanced(expr)) {
		printf("%s: balanced.\n", expr);
	}
	else {
		printf("%s: unbalanced.\n", expr);
	}

}

int is_balanced(char* expr) {
	int balanced = 1;
	int index = 0;
	while (balanced && index < strlen(expr)) { // balanced가 0이면 빠져나온다.
		char ch = expr[index];
		if (is_open(ch) > -1) {
			push(ch);
		}
		else if (is_close(ch) > -1) {
			if (is_empty()) { // 스택이 비었는지 확인
				balanced = 0;
				break;
			}
			char top_ch = pop(); // 스텍이 비어있지 않다면 pop한다.
			if (is_open(top_ch) != is_close(ch)) { // 괄호 유형이 같은지 확인한다.
				balanced = 0; // 다르면 0
			}
		}
		index++;
	}
	return(balanced == 1 && is_empty() == 1); // 스택이 비어있는지도 확인해야한다.
}

int is_close(char ch) {
	for (int i = 0; i < strlen(CLOSE); i++) {
		if (CLOSE[i] == ch) {
			return i;
		}
	}
	return -1;
}

int is_open(char ch) {
	for (int i = 0; i < strlen(OPEN); i++) {
		if (OPEN[i] == ch) {
			return i;
		}
	}
	return -1;
}