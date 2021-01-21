#include  "string_tools.h"


int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i < n - 1) {
			str[i++] = ch;
		}
	}

	str[i] = '\0';
	return i; //읽은 글자의 개수 반환

}