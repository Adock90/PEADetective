#ifndef SECTIONPARSE_H
#define SECTIONPARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>


typedef struct
{
	BYTE* Location;
	DWORD Size;
	DWORD ImportDir;
} PEOffsets;

void GetFirstSectionHeader(PIMAGE_NT_HEADERS NTHeaders, PEOffsets* Result);

DWORD GetSectionImportDirectoryOffset(PIMAGE_NT_HEADERS NTHeaders);

PIMAGE_SECTION_HEADER OutputSectionHeaders(PIMAGE_NT_HEADERS NTHeaders, PEOffsets ImportDirVar);

BYTE* GetImportTableOffset(BYTE* MappedFile, PIMAGE_SECTION_HEADER ImportSection, DWORD ImportDirRVA);

PIMAGE_IMPORT_DESCRIPTOR GetImportDescriptor(BYTE* Offset);

void OutputDLLImports(DWORD RawOffset, IMAGE_IMPORT_DESCRIPTOR* ImportDescriptor, PIMAGE_SECTION_HEADER ImportSection);

#endif