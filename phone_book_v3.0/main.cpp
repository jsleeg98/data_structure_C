#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define INIT_CAPACITY 3
#define BUFFER_SIZE 20

char ** names;
char ** numbers;

int capacity = INIT_CAPACITY;
int n = 0;

char delim[] = " ";

void add(char* name, char* number);
void find(char* name);
void status();
void remove(char* name);
char* make_copy(char* buf);
void save(char* fileName);
void load(char* fileName);
int search(char* name);
void init_directory();
void process_command();
void reallocate();

int main() {
	init_directory();
	process_command();

	return 0;
}

// �ʱ� �迭 ũ�� �Ҵ� �Լ�
void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

//fget, getline�� ����� ���� ������ �������� ��°��� ��� �˰� Ȱ���ϱ� ������ ������ 
//���� �Լ��� ���� ����Ѵ�.
int read_line(char str[], int limit) {
	int ch, i = 0;

	//getchar()�� ������ ��ȯ�Ѵ�.
	while ((ch = getchar()) != '\n') {
		if (i < limit - 1) {
			str[i++] = ch;
		}
	}
	//���ڿ��� �������� Null char�� �������Ѵ�.
	str[i] = '\0';
	// ���� ���ڼ��� ��ȯ
	return i;
}

void process_command() {
	char command_line[BUFFER_SIZE];
	char* command, * argument1, * argument2;

	while (1) {
		printf("$ ");
		if (read_line(command_line, BUFFER_SIZE) <= 0) {
			continue;
		}
		command = strtok(command_line, delim);
		if (command == NULL) {
			continue;
		}
		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argument1);
		}
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);
			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			add(argument1, argument2);
			printf("%s was added succefully.\n", argument1);
		}
		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			find(argument1);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			remove(argument1);
		}
		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || strcmp("as", argument1) != 0 || argument2 == NULL) {
				printf("Invalid command format.\n");
				continue;
			}
			save(argument2);
		}
		else if(strcmp(command, "exit") == 0) {
			break;
		}
	}
}






void add(char *name, char * number) {
	// �迭�� ũ�⸦ �Ѿ ���
	if (n >= capacity) {
		reallocate();
	}

	//���� ���� �߰�
	int i = n - 1;
	// ������ ������ �� �����̰� ���� ��ġ�� �ƴ϶��, ���� �ִ� ���� ��ĭ�� �ڷ� �̷��. 
	while (i >= 0 && strcmp(names[i], name) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	// strdup�� malloc���� �޸𸮸� �Ҵ��Ͽ� ���� �����ϱ� ������ add �Լ��� ����Ǿ �Ҹ����� �ʴ´�.
	// ���� �ڸ��� ���ο� �����͸� �߰���Ų��.
	names[i + 1] = make_copy(name);
	numbers[i + 1] = make_copy(number);
	n++;

	// printf("%s was added successfully.\n", name);
}

void find(char * name) {
	int index = search(name);
	if (index == -1) {
		// ������ �̸��� ã�� ������ ��
		printf("No person named '%s' exists.\n", name);
	}
	else {
		printf("%s\n", numbers[index]);
	}


}

void status() {
	for (int i = 0; i < n; i++) {
		printf("%s  %s\n", names[i], numbers[i]);

	}
	printf("Total %d persons.\n", n);
}

void remove(char *name) {


	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}

	int j = index;
	for (j = index; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", name);
}

char* make_copy(char* buf) {
	char* p;
	p = (char*)malloc(strlen(buf) + 1);
	if (p != NULL) {
		strcpy(p, buf);
	}
	return p;
}

void load(char *fileName) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp);
}

void save(char *fileName) {
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

void reallocate() {
	capacity *= 2;
	//�� �� ū �迭�� ����
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	for (int i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}
	//���� �迭 ������
	free(names);
	free(numbers);

	//���Ҵ�
	names = tmp1;
	numbers = tmp2;
}