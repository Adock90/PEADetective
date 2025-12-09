#ifndef UNICODE
#define UNICODE
#endif

#ifndef PEAPARSE_H
#define PEAPARSE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

HANDLE FileOpen(char* Filename)
{
	printf("%s\n", Filename);
	HANDLE TargetFile = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (TargetFile == INVALID_HANDLE_VALUE)
	{
		printf("%s was unable to be opened. Check if file exists\n", Filename);
		printf("Error Code: %d\n", GetLastError());
		CloseHandle(TargetFile);
		exit(1);
	}
	return TargetFile;
}

HANDLE FileMemoryMap(HANDLE FileHandle)
{
	HANDLE MemMappedFileHandle = CreateFileMapping(FileHandle, NULL, PAGE_READONLY, 0, 0, NULL);
	if (MemMappedFileHandle == 0)
	{
		printf("Mapping to Virtual Memory Failed\n Error Code: %d\n", GetLastError());
		CloseHandle(FileHandle);
		exit(1);
	}
	else
	{
		return MemMappedFileHandle;
	}
}

LPVOID ViewMemoryMap(HANDLE FileMappedHandle, HANDLE OriginalFileHandle)
{
	LPVOID ViewMappedFile = MapViewOfFile(FileMappedHandle, FILE_MAP_READ, 0, 0, 0);
	if (ViewMappedFile == 0)
	{
		printf("View of Mapped File failed\n Error Code: %d\n", GetLastError());
		CloseHandle(FileMappedHandle);
		CloseHandle(OriginalFileHandle);
		exit(1);
	}
	else
	{
		return ViewMappedFile;
	}
}

bool ValidateFileSize(HANDLE FileOBJ)
{
	DWORD FileSize = GetFileSize(FileOBJ, NULL);
	if (FileSize < 97)
	{
		printf("[PEADetective] File Is too small to be a compatable EXE\n");
		return false;
	}
	else
	{
		return true;
	}
}

void PEACleanup(LPVOID MappedFile, HANDLE MemMap, HANDLE FileObj)
{
	UnmapViewOfFile(MappedFile);
	CloseHandle(MemMap);
	CloseHandle(FileObj);
}

#endif