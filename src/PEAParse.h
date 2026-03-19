#ifndef UNICODE
#define UNICODE
#endif

#ifndef PEAPARSE_H
#define PEAPARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

HANDLE FileOpen(char* Filename);

HANDLE FileMemoryMap(HANDLE FileHandle);

LPVOID ViewMemoryMap(HANDLE FileMappedHandle, HANDLE OriginalFileHandle);

int ValidateFileSize(HANDLE FileOBJ);

void PEACleanup(LPVOID MappedFile, HANDLE MemMap, HANDLE FileObj);

#endif