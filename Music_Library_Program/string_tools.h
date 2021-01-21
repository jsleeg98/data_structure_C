// #pragma once //헤더파일의 중복 include 방지 - ifndef - endif 방식 대신 사용가능

#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H
#include <stdio.h>


int read_line(FILE* fp, char str[], int n);

#endif