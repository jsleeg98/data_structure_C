#include "stackADT.h"
#include <stdio.h>

int main()
{
	Stack s1 = create();
	Stack s2 = create();

	push(s1, 10);
	printf("%d", pop(s1));
}

