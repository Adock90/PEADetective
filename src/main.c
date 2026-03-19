#include <stdio.h>
#include <Windows.h>

#include "PEAUtil.h"
#include "PEAParse.h"
#include "DOSParse.h"
#include "NTParse.h"
#include "SectionParse.h"


void Help()
{
	printf(
		"PEADetective 1.0\n"
		"PEADetective.exe [FilePath]:\n"
		"\n\t[FilePath]: The location of the Executable File (endswith '.exe', '.scr', '.dll', '.sys')\n"
		"\t\tcan be envoked with --file\n"
		"\n\t--h: Provides Help. (You Are here)"
		"\n\t--DOS: Outputs DOS Headers\n"
		"\n\t--NT: Outputs NT Headers\n"
		"\n\t--SECTION: Outputs Section Headers\n"
		"\n\t--DLL: Outputs DLL Files Imported\n"
		"\n\t--all: Outputs Everything\n"
	);
}

int main(int argc, char* argv[])
{
	if (argc > 6)
	{
		printf("[PEADetective] Too many args\n");
		Help();
		return EXIT_FAILURE;
	}
	else if (argc < 2)
	{
		printf("[PEADetective] Too little args\n");
		Help();
		return EXIT_FAILURE;
	}
	
	ArgData ArgumentData = ParseArgs(argc, argv);
	if (ArgumentData.ArgumentViolation == 1)
	{
		printf("[PEADetective] Argument Violation Detected\n");
		Help();
		return EXIT_FAILURE;
	}

	int OutputSectionHeadersArgs;
	PEOffsets ResultStore = { 0 };
	PEOffsets FirstHeader;
	char* File = ArgumentData.Filename;
	printf("[EXECUTABLE FILE: %s]\n", File);
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
	if (DOS == 0)
	{
		printf("[PEADetective] Failed to get DOS Header\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}

	if (IsStrInArr("--DOS", ArgumentData.FetchArray) == 0 || IsArrEmpty(ArgumentData.FetchArray) == 0)
	{
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
	}

	PIMAGE_NT_HEADERS NT = GetNTHeaders(ViewMemoryMappedFile);
	if (NT == )
	{
		printf("[PEADetective] Failed to match NT Header\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}
	else
	{
		if (IsStrInArr("--NT", ArgumentData.FetchArray) == 0 || IsArrEmpty(ArgumentData.FetchArray) == 0)
		{
			OutputNTHeaders(NT);
		}
	}

	GetFirstSectionHeader(NT, &ResultStore);

	if (IsStrInArr("--SECTION", ArgumentData.FetchArray) == 0 || IsArrEmpty(ArgumentData.FetchArray) == 0)
	{
		OutputSectionHeadersArgs = 1;
	}
	else
	{
		OutputSectionHeadersArgs = 0;
	}

	
	DWORD ImportDirTable = GetSectionImportDirectoryOffset(NT, OutputSectionHeadersArgs);
	if (ImportDirTable == NULL)
	{
		printf("[PEADetective] Failed to get Import Directory Offset\n");
		PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);
		return EXIT_FAILURE;
	}

	FirstHeader.ImportDir = ImportDirTable;

	

	PIMAGE_SECTION_HEADER ImportSection = OutputSectionHeaders(NT, FirstHeader, OutputSectionHeadersArgs);
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

	if (IsStrInArr("--DLL", ArgumentData.FetchArray) == 0 || IsArrEmpty(ArgumentData.FetchArray) == 0)
	{
		OutputDLLImports((BYTE*)ViewMemoryMappedFile, ImportDesc, ImportSection, TableOffset);
	}
	PEACleanup(ViewMemoryMappedFile, MemoryMapFile, MasterFile);

	return 0;
}
