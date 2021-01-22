#pragma warning(disable:4996) //strtok 경고 없애기

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_tools.h"
#include "library.h"


# define BUFFER_LENGTH 200

void handle_add();
void process_command();
void handle_load();
void handle_search();
void handle_play();

int main() {

	initialize();
	handle_load();
	process_command();

}

void handle_load() {

	char buffer[BUFFER_LENGTH];

	printf("Data file name ? ");

	if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0)  //get a line
		return;

	FILE* fp = fopen(buffer, "r");
	if (fp == NULL) {
		printf("No such file exists.\n");
		return;
	}

	load(fp);
	fclose(fp);
}
 

void process_command() {

	char command_line[BUFFER_LENGTH];
	char* command;

	while (1) {  //infinite loop
		printf("$ "); //prompt
		
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) { //get a line
			continue;
		}

		command = strtok(command_line, " ");
		if (strcmp(command, "add") == 0) {
			handle_add();
		}
		else if(strcmp(command, "search") == 0) {
			handle_search();
		}
		/*
		else if (strcmp(command, "remove") == 0) {
			handle_remove();
		}*/
		else if (strcmp(command, "status") == 0) {
			status();
		}
		
		else if (strcmp(command, "play") == 0) {
			handle_play();
		}
		/*
		else if (strcmp(command, "save") == 0) {
			handle_save();
		}
		*/
		/*
		else if (strcmp(command, "exit") == 0) {
			handle_exit();
		}
		*/
	}
}

void handle_play() {
	char* id_str = strtok(NULL, " ");
	int index = atoi(id_str);
	play(index);
}

void handle_search() {
	char name[BUFFER_LENGTH], title[BUFFER_LENGTH];

	printf("	Artist: ");
	if (read_line(stdin, name, BUFFER_LENGTH) <= 0) {
		printf("	Artist name required\n");
		return;
	}
	printf("	Title: ");
	int title_len = read_line(stdin, title, BUFFER_LENGTH);
	if (title_len <= 0) {
		search_song(name);
	}
	else {
		search_song(name, title);
	}
}

void handle_add() {
	char buffer[BUFFER_LENGTH];
	char* artist = NULL, * title = NULL, * path = NULL;

	printf("	Artist: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		artist = _strdup(buffer);
	}
	printf("	Title: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		title = _strdup(buffer);
	}
	printf("	Path: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		path = _strdup(buffer);
	}

	printf("%s %s %s\n", artist, title, path);


	//add to the music library//
	add_song(artist, title, path);


}
