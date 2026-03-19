#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define ARGS_TO_CHOOSE_FROM 6
#define ARR_MAX_SIZE 1024

typedef struct
{
	char* Filename;
	char* FetchArray[ARGS_TO_CHOOSE_FROM];
	int ArgumentViolation;
} ArgData;

LPCSTR CharStarToLPCSTR(char* string)
{
	LPCSTR result = string;
	return string;
}

int VerifyFileExistance(char* filename)
{
	FILE* fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		return 1;
	}
	else
	{
		fclose(fptr);
		return 0;
	}
}

ArgData ParseArgs(int argc, char* argv[])
{
	char *ArgList[ARGS_TO_CHOOSE_FROM] = {"--h", "--file", "--DOS", "--NT", "--SECTION", "--DLL"};
	ArgData ArgumentContent = { 0 };
	for (int i = 1; i < argc; i++)
	{
		if (VerifyFileExistance(argv[i]) == 0)
		{
			ArgumentContent.Filename = argv[i];
		}
		else if (strcmp(argv[i], "--all") == 0)
		{
			for (int o = 2; o < ARGS_TO_CHOOSE_FROM; o++)
			{
				ArgumentContent.FetchArray[o] = ArgList[o];
			}
			if (i == argc - 1)
				break;
		}
		else
		{
			for (int j = 0; j < ARGS_TO_CHOOSE_FROM; j++)
			{
				if (strcmp(ArgList[j], argv[i]) == 0)
				{
					ArgumentContent.FetchArray[j] = argv[i];
					break;
					
				}
				else if (strcmp(ArgList[j], argv[i]) != 0 && j == ARGS_TO_CHOOSE_FROM - 1 || strlen(ArgumentContent.Filename) == 0)
				{
					ArgumentContent.ArgumentViolation = 1;
				}
			}
		}
	}
	return ArgumentContent;
}


int IsStrInArr(char* Str, char* arr[])
{
	for (size_t i = 0; i < ARGS_TO_CHOOSE_FROM; i++)
	{
		if (arr[i] == NULL)
		{
			continue;
		}
		else if (strcmp(arr[i], Str) == 0)
		{
			return 0;
		}
	}
	return 1;
}

int IsArrEmpty(char* arr[])
{
	for (int i = 0; i < sizeof(arr); i++)
	{
		if (arr[i] != NULL)
		{
			return 1;
		}
	}
	return 0;
}