#ifndef UNICODE
#define UNICODE
#endif


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


void GetFirstSectionHeader(PIMAGE_NT_HEADERS NTHeaders, PEOffsets* Result)
{
	Result->Location = (BYTE*)IMAGE_FIRST_SECTION(NTHeaders);
	Result->Size = sizeof(IMAGE_SECTION_HEADER);
}

DWORD GetSectionImportDirectoryOffset(PIMAGE_NT_HEADERS NTHeaders, int Output)
{
	if (Output == 1)
	{
		printf("\n[           SECTION HEADERS           ]\n");
		printf("Section Import Directory Offset: %x\n", NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	}
	
	return NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
}

PIMAGE_SECTION_HEADER OutputSectionHeaders(PIMAGE_NT_HEADERS NTHeaders, PEOffsets ImportDirVar, int Output)
{
	PIMAGE_SECTION_HEADER ImportSection = NULL;
	PIMAGE_SECTION_HEADER FirstSection = IMAGE_FIRST_SECTION(NTHeaders);
	PIMAGE_SECTION_HEADER header = NULL;

	if (Output == 1)
	{
		printf("\n[           SECTION HEADERS           ]\n");
	}

	for (int i = 0; i < NTHeaders->FileHeader.NumberOfSections; i++)
	{
		header = &FirstSection[i];
		if (Output == 1)
		{
			printf("\t Name: %0.8s\n", header->Name);
			printf("\t Virtual Size: %x\n", header->Misc.VirtualSize);
			printf("\t Virtual Address: %x\n", header->VirtualAddress);
			printf("\t Size of Raw Data: %x\n", header->SizeOfRawData);
			printf("\t Pointer to Raw Data: %x\n", header->PointerToRawData);
			printf("\t Pointer to Relocations: %x\n", header->PointerToRelocations);
			printf("\t Number of Line Numbers: %x\n", header->NumberOfLinenumbers);
			printf("\t Pointer to Line Numbers: %x\n", header->PointerToLinenumbers);
			printf("\t Number of Relocations: %x\n", header->NumberOfRelocations);
			printf("\t Characteristics: %x\n", header->Characteristics);
			printf("\n");
		}
		if (ImportDirVar.ImportDir >= header->VirtualAddress && ImportDirVar.ImportDir < header->VirtualAddress + header->Misc.VirtualSize)
		{
			ImportSection = header;
		}

		ImportDirVar.Location += ImportDirVar.Size;
	}

	if (!ImportSection)
	{
		printf("[PEADetective] No Imports found: %08x", ImportDirVar.ImportDir);
	}
	return ImportSection;

}

BYTE* GetImportTableOffset(BYTE* MappedFile, PIMAGE_SECTION_HEADER ImportSection, DWORD ImportDirRVA)
{
	
	DWORD SectRVA = ImportSection->VirtualAddress;
	DWORD SectRaw = ImportSection->PointerToRawData;
	DWORD RVADelta = ImportDirRVA - SectRVA;
	DWORD ImportOffset = SectRaw + RVADelta;
	BYTE* RawOffset = MappedFile + ImportOffset;
	return RawOffset;
}

PIMAGE_IMPORT_DESCRIPTOR GetImportDescriptor(BYTE* Offset)
{
	return (PIMAGE_IMPORT_DESCRIPTOR)Offset;
}

void OutputDLLImports(BYTE* MappedFile, PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor, PIMAGE_SECTION_HEADER ImportSection, PIMAGE_NT_HEADERS NT)
{
	printf("\n[             DLL IMPORTS             ]\n");

	while (ImportDescriptor->Name != 0)
	{
		printf("\tName: %s\n", (MappedFile + ImportSection->PointerToRawData + (ImportDescriptor->Name - ImportSection->VirtualAddress)));
		++ImportDescriptor;
	}
}
