#ifndef UNICODE
#define UNICODE
#endif

#ifndef DOSPARSE_H
#define DOSPARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

PIMAGE_DOS_HEADER GetDOSHeader(LPVOID MappedFile);

bool VerifyMagicHeader(PIMAGE_DOS_HEADER DOSHeader);

void OutputDOSHeader(PIMAGE_DOS_HEADER DOSHeader);

#endif