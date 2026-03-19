#ifndef UNICODE
#define UNICODE
#endif

#ifndef PEAUTIL_H
#define PEAUTIL_H

#define ARGS_TO_CHOOSE_FROM 6
#define ARR_MAX_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct
{
	char* Filename;
	char* FetchArray[ARGS_TO_CHOOSE_FROM];
	int ArgumentViolation;
} ArgData;

LPCSTR CharStarToLPCSTR(char* string);

ArgData ParseArgs(int argc, char* argv[]);

int IsStrInArr(char* Str, char* arr[]);

int IsArrEmpty(char* arr[]);

#endif