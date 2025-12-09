#ifndef UNICODE
#define UNICODE
#endif

#ifndef NTPARSE_H
#define NTPARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#include "DOSParse.h"

PIMAGE_NT_HEADERS GetNTHeaders(LPVOID MappedFile);

void OutputNTHeaders(PIMAGE_NT_HEADERS NTHeaders);

#endif