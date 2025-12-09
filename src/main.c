#include <stdio.h>
#include <Windows.h>

#include "PEAUtil.h"
#include "PEAParse.h"
#include "DOSParse.h"
#include "NTParse.h"
#include "SectionParse.h"


int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		printf("[PEADetective] Too many args\n");
		return EXIT_FAILURE;
	}
	else if (argc < 2)
	{
		printf("[PEADetective] Too little args\n");
		return EXIT_FAILURE;
	}

	PEOffsets ResultStore = { 0 };
	PEOffsets FirstHeader;
	char* File = argv[1];
	HANDLE MasterFile = FileOpen(File);
	if (MasterFile == INVALID_HANDLE_VALUE)
	{
		printf("[PEADetective] Invalid FileOpen HANDLE. Check if %s exists on disk.\n", File);
		return EXIT_FAILURE;
	}

	bool CheckFileSize = ValidateFileSize(MasterFile);
	if (!CheckFileSize)
	{
		CloseHandle(MasterFile);
		return EXIT_FAILURE;
	}

	HANDLE MemoryMapFile = FileMemoryMap(MasterFile);
	if (MemoryMapFile == INVALID_HANDLE_VALUE)
	{
		printf("[PEADetective] Failed to Map File to Memory\nError Code: %d\n", GetLastError());
		CloseHandle(MasterFile);
		return EXIT_FAILURE;
	}

	LPVOID ViewMemoryMappedFile = ViewMemoryMap(MemoryMapFile, MasterFile);
	if (ViewMemoryMappedFile == 0)
	{
		printf("View of Mapped File failed\n Error Code: %d\n", GetLastError());
		CloseHandle(MemoryMapFile);
		CloseHandle(MasterFile);
		return EXIT_FAILURE;
	}

	PIMAGE_DOS_HEADER DOS = GetDOSHeader(ViewMemoryMappedFile);
	if (DOS == NULL)
	{
		printf("[PEADetective] Failed to get DOS Header\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}

	if (!VerifyMagicHeader(DOS))
	{
		printf("[PEADetective] Failed to match DOS Magic Header (MZ)\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}
	else
	{
		OutputDOSHeader(DOS);
	}

	PIMAGE_NT_HEADERS NT = GetNTHeaders(ViewMemoryMappedFile);
	if (NT == NULL)
	{
		printf("[PEADetective] Failed to match NT Header\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}
	else
	{
		OutputNTHeaders(NT);
	}

	printf("hh");
	GetFirstSectionHeader(NT, &ResultStore);

	
	DWORD ImportDirTable = GetSectionImportDirectoryOffset(NT);
	if (ImportDirTable == NULL)
	{
		printf("[PEADetective] Failed to get Import Directory Offset\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}

	FirstHeader.ImportDir = ImportDirTable;

	PIMAGE_SECTION_HEADER ImportSection = OutputSectionHeaders(NT, FirstHeader);
	if (!ImportSection)
	{
		printf("[PEADetective] Failed to get Section Headers. Import Section is NULL\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}

	BYTE* TableOffset = GetImportTableOffset((BYTE*)ViewMemoryMappedFile, ImportSection, FirstHeader.ImportDir);
	if (!TableOffset)
	{
		printf("[PEADetective] Failed to get Import Table Offset\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}

	PIMAGE_IMPORT_DESCRIPTOR ImportDesc = GetImportDescriptor(TableOffset);
	if (!ImportDesc)
	{
		printf("[PEADetective] Failed to get Import Descriptor\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}

	OutputDLLImports((BYTE*)ViewMemoryMappedFile, ImportDesc, ImportSection);

	PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);

	return 0;
}