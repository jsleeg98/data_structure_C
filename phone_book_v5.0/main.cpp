#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct person {
	char* name;
	char* number;
	char* email;
	char* group;

} Person;

Person** directory;
int capacity;
int n;

void add(char* name, char* number, char* email, char* group);
void find(char* name);
void status();
void remove(char* name);
char* make_copy(char* buf);
void save(char* fileName);
int search(char* name);
int read_line(FILE* fp, char str[], int limit);
int compose_name(char str[], int limit);
void handle_add(char* name);
void print_person(Person* p);
void init();
void reallocate();
void release_person(Person* p);

void init() {
	directory = (Person**)malloc(INIT_CAPACITY * sizeof(Person*));
	capacity = INIT_CAPACITY;
	n = 0;
} 


void load(char* fileName) {
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;
	char* token;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	
	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0) {
			break;
		}
		name = strtok(buffer, "#");
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0) {
			number = NULL;
		}
		else {
			number = make_copy(token);
		}
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0) {
			email = NULL;
		}
		else {
			email = make_copy(token);
		}
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0) {
			group = NULL;
		}
		else {
			group = make_copy(token);
		}
		add(make_copy(name), number, email, group);
	}
	
	fclose(fp);
}


void add(char* name, char* number, char* email, char* group) {
	if (n >= capacity) {
		reallocate();
	}

	//정렬 과정 추가
	int i = n - 1;
	// 사전식 순서가 더 뒤쪽이고 시작 위치가 아니라면, 원래 있던 것을 한칸씩 뒤로 미룬다. 
	while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
		directory[i + 1] = directory[i]; //포인터 주소가 복사
		i--;
	}

	// v5.0의 특징
	directory[i + 1] = (Person*)malloc(sizeof(Person)); //포인터에 저장할 구조체 공간을 할당한다.

	//strdup 사용하지 않는다., make_copy 사용하지 않는다.
	// 멈춘 자리에 새로운 데이터를 추가시킨다.
	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;

	n++;
}

void reallocate() {
	capacity *= 2;
	Person** tmp = (Person**)malloc(capacity * sizeof(Person*));

	//복사되는 데이터의 양의 줄었다. 주소값만을 활용하기 때문
	for (int i = 0; i < n; i++) {
		tmp[i] = directory[i];
	}

	//해당하는 주소의 데이터 공간을 반환해준다.
	free(directory); // garbage 방지
	directory = tmp;
}

void remove(char* name) {
	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}

	Person* p = directory[index];
	for (int j = index; j < n - 1; j++) {
		directory[j] = directory[j + 1];
	}
	n--;
	release_person(p);
	printf("'%s' was deleted successfully.\n", name);
}

void release_person(Person* p) {
	free(p->name);
	//make_copy 할당 공간 반환
	if (p->number != NULL) free(p->number);
	if (p->email != NULL) free(p->email);
	if (p->group != NULL) free(p->group);
	free(p);
}

//fget, getline을 사용할 수도 있지만 디테일한 출력값을 모두 알고 활용하기 귀찮기 때문에 
//보통 함수를 만들어서 사용한다.
// stdin FILE 포인터는 키보드로 부터의 입력을 의미한다.
int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;

	//getchar()는 정수를 반환한다.
	//EOF은 파일의 끝을 판단
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i < n) {
			str[i++] = ch;
		}
	}
	//문자열의 마지막은 Null char로 끝나야한다.
	str[i] = '\0';
	// 읽은 문자수를 반환
	return i;
}

int compose_name(char str[], int limit) {
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " ");
	if (ptr == NULL) { //사람이름이 없는 경우
		return 0;
	}
	strcpy(str, ptr);
	length += strlen(ptr);

	while ((ptr = strtok(NULL, " ")) != NULL) {
		if (length + strlen(ptr) + 1 < limit) {
			str[length++] = ' ';
			str[length] = '\0'; // \0 추가
			strcat(str, ptr); //두 문자열이 \0로 끝나야 제대로 수행
			length += strlen(ptr);
		}
	}
	return length;
}

void status() {
	for (int i = 0; i < n; i++) {
		print_person(directory[i]);
	}
	printf("Total %d persons.\n", n);
}

void save(char* fileName) {
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[i]->name);
		if (directory[i]->number != NULL) fprintf(fp, "%s#", directory[i]->number);
		if (directory[i]->email != NULL)fprintf(fp, "%s#", directory[i]->email);
		if (directory[i]->group != NULL)fprintf(fp, "%s#", directory[i]->group);
	}
	fclose(fp);
}

char* make_copy(char* buf) {
	char* p;
	p = (char*)malloc(strlen(buf) + 1);
	if (p != NULL) {
		strcpy(p, buf);
	}
	return p;
}

void print_person(Person *p) {
	printf("%s:\n", p->name);
	printf("	Phone : %s\n", p->number);
	printf("	Email : %s\n", p->email);
	printf("	Group : %s\n", p->group);
}

void find(char* name) {
	int index = search(name);
	if (index == -1) {
		// 동일한 이름을 찾지 못했을 때
		printf("No person named '%s' exists.\n", name);
	}
	else {
		print_person(directory[index]);
	}
}


int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, directory[i]->name) == 0) {
			return i;
		}
	}
	return -1;
}

void handle_add(char* name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " ";
	printf("	phone : ");
	read_line(stdin, number, BUFFER_LENGTH);
	printf("	Email : ");
	read_line(stdin, email, BUFFER_LENGTH);
	printf("	Group : ");
	read_line(stdin, group, BUFFER_LENGTH);
	
	


	add(name, (char*)(strlen(number) > 0 ? make_copy(number) : NULL),
		(char*)(strlen(email) > 0 ? make_copy(email) : NULL),
		(char*)(strlen(group) > 0 ? make_copy(group) : NULL));
}



////////////////



int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument;
	char name_str[BUFFER_LENGTH];

	init();

	while (1) {
		printf("$ ");
		//키보드로부터 읽기 때문에 stdin 이다.
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) {
			continue;
		}
		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument);
		}
		else if (strcmp(command, "add") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			handle_add(name_str);
		}

		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			remove(name_str);
		}
		else if (strcmp(command, "save") == 0) {
			argument = strtok(NULL, " ");
			if (strcmp(argument, "as") != 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
	}
	return 0;
}