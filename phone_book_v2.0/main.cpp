#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define CAPACITY 100
#define BUFFER_SIZE 20

char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0;

void add();
void find();
void status();
void remove();
char* make_copy(char* buf);
void save();
void load();
int search(char* name);

int main() {
	char command[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0) {
			add();
		}
		else if (strcmp(command, "find") == 0) {
			find();
		}
		else if (strcmp(command, "delete") == 0) {
			remove();
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else if (strcmp(command, "read") == 0) {
			load();
		}
		else if (strcmp(command, "save") == 0) {
			save();
		}
	}
	return 0;
}

void add() {
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	//���� ���� �߰�
	int i = n - 1;
	// ������ ������ �� �����̰� ���� ��ġ�� �ƴ϶��, ���� �ִ� ���� ��ĭ�� �ڷ� �̷��. 
	while (i >= 0 && strcmp(names[i], buf1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	// strdup�� malloc���� �޸𸮸� �Ҵ��Ͽ� ���� �����ϱ� ������ add �Լ��� ����Ǿ �Ҹ����� �ʴ´�.
	// ���� �ڸ��� ���ο� �����͸� �߰���Ų��.
	names[i+1] = make_copy(buf1);
	numbers[i+1] = make_copy(buf2);
	n++;

	printf("%s was added successfully.\n", buf1);
}

void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		// ������ �̸��� ã�� ������ ��
		printf("No person named '%s' exists.\n", buf);
	}
	else {
		printf("%s\n"), numbers[index];
	}
	

}

void status() {
	for (int i = 0; i < n; i++) {
		printf("%s  %s\n", names[i], numbers[i]);

	}
	printf("Total %d persons.\n", n);
}

void remove() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		printf("No person named '%s' exists.\n", buf);
		return;
	}

	int j = index;
	for (j = index; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", buf);
}

char* make_copy(char* buf) {
	char* p;
	p = (char*)malloc(strlen(buf) + 1);
	if (p != NULL) {
		strcpy(p, buf);
	}
	return p;
}

void load() {
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", fileName);
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = make_copy(buf1);
		numbers[n] = make_copy(buf2);
		n++;
	}
	fclose(fp);
}

void save() {
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp); //as�� ����, ������� �ʴ´�.
	scanf("%s", fileName);

	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}