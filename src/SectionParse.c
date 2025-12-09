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

BYTE* RVATOPTR(DWORD RVA, PIMAGE_SECTION_HEADER Section, WORD SectionCount, BYTE* BASE)
{
	for (WORD i = 0; i < SectionCount; i++)
	{
		DWORD VirtualAddress = Section[i].VirtualAddress;
		DWORD Size = Section[i].Misc.VirtualSize;

		if (RVA >= VirtualAddress && RVA < VirtualAddress + Size)
		{
			DWORD delta = RVA - VirtualAddress;
			return BASE + Section[i].PointerToRawData + delta;
		}
	}

	return NULL;
}

void GetFirstSectionHeader(PIMAGE_NT_HEADERS NTHeaders, PEOffsets* Result)
{
	Result->Location = (BYTE*)IMAGE_FIRST_SECTION(NTHeaders);
	Result->Size = sizeof(IMAGE_SECTION_HEADER);
}

DWORD GetSectionImportDirectoryOffset(PIMAGE_NT_HEADERS NTHeaders)
{
	printf("%x\n", NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	return NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
}

PIMAGE_SECTION_HEADER OutputSectionHeaders(PIMAGE_NT_HEADERS NTHeaders, PEOffsets ImportDirVar)
{
	PIMAGE_SECTION_HEADER ImportSection = NULL;
	PIMAGE_SECTION_HEADER FirstSection = IMAGE_FIRST_SECTION(NTHeaders);
	PIMAGE_SECTION_HEADER header = NULL;
	//IMAGE_FIRST_SECTION(NTHeaders);

	printf("\n[           SECTION HEADERS           ]\n");

	for (int i = 0; i < NTHeaders->FileHeader.NumberOfSections; i++)
	{
		header = &FirstSection[i];
		printf("[PEADetective] Name: %0.8s\n", header->Name);
		printf("[PEADetective] Virtual Size: %x\n", header->Misc.VirtualSize);
		printf("[PEADetective] Virtual Address: %x\n", header->VirtualAddress);
		printf("[PEADetective] Size of Raw Data: %x\n", header->SizeOfRawData);
		printf("[PEADetective] Pointer to Raw Data: %x\n", header->PointerToRawData);
		printf("[PEADetective] Pointer to Relocations: %x\n", header->PointerToRelocations);
		printf("[PEADetective] Number of Line Numbers: %x\n", header->NumberOfLinenumbers);
		printf("[PEADetective] Pointer to Line Numbers: %x\n", header->PointerToLinenumbers);
		printf("[PEADetective] Number of Relocations: %x\n", header->NumberOfRelocations);
		printf("[PEADetective] Characteristics: %x\n", header->Characteristics);
		printf("\n");

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
	if (!ImportSection)
	{
		printf("[PEADetective] Import Section is NULL");
		return NULL;
	}
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

void OutputDLLImports(BYTE* MappedFile, IMAGE_IMPORT_DESCRIPTOR* ImportDescriptor, PIMAGE_SECTION_HEADER ImportSection)
{

}

#endif