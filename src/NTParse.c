#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#include "DOSParse.h"

bool VerifyNTSignature(PIMAGE_NT_HEADERS NTHeader)
{
	if (NTHeader->Signature == IMAGE_NT_SIGNATURE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

PIMAGE_NT_HEADERS GetNTHeaders(LPVOID MappedFile)
{
	PIMAGE_DOS_HEADER DOS = (PIMAGE_DOS_HEADER)MappedFile;
	if (!VerifyMagicHeader(DOS))
	{
		printf("[PEADetective] DOS Signature Not Matched: (MZ)\n");
		exit(1);
	}
	else
	{
		PIMAGE_NT_HEADERS NTHeader = (PIMAGE_NT_HEADERS)((u_char*)DOS + DOS->e_lfanew);
		if (!VerifyNTSignature(NTHeader))
		{
			printf("[PEADetective] NT Signature Not Matched: (PE)\n");
			exit(1);
		}
		else
		{
			return NTHeader;
		}
	}
}

void OutputNTHeaders(PIMAGE_NT_HEADERS NTHeaders)
{
	printf("[               NT HEADERS               ]\n");
	printf("\t Signature: %x\n", NTHeaders->Signature);
	printf("\n[              FILE HEADER               ]\n");
	printf("\t Machine: %x\n", NTHeaders->FileHeader.Machine);
	printf("\t Number of Sections: %x\n", NTHeaders->FileHeader.NumberOfSections);
	printf("\t Time Stamp: %x\n", NTHeaders->FileHeader.TimeDateStamp);
	printf("\t Pointer to Symbol Table: %x\n", NTHeaders->FileHeader.PointerToSymbolTable);
	printf("\t Number of Symbols: %x\n", NTHeaders->FileHeader.NumberOfSymbols);
	printf("\t Size of Optional Header: %x\n", NTHeaders->FileHeader.SizeOfOptionalHeader);
	printf("\t Characteristics: %x\n", NTHeaders->FileHeader.Characteristics);
	printf("\n[            OPTIONAL HEADER           ]\n");
	printf("\t Magic Header: %x\n", NTHeaders->OptionalHeader.Magic);
	printf("\t Major Linker Version: %x\n", NTHeaders->OptionalHeader.MajorLinkerVersion);
	printf("\t Minor Linker Version: %x\n", NTHeaders->OptionalHeader.MinorLinkerVersion);
	printf("\t Size of Code: %x\n", NTHeaders->OptionalHeader.SizeOfCode);
	printf("\t Size of Initialized Data: %x\n", NTHeaders->OptionalHeader.SizeOfInitializedData);
	printf("\t Size of UnInitalized Data: %x\n", NTHeaders->OptionalHeader.SizeOfUninitializedData);
	printf("\t Address of Entry Point '.text': %x\n", NTHeaders->OptionalHeader.AddressOfEntryPoint);
	printf("\t Base of Code: %x\n", NTHeaders->OptionalHeader.BaseOfCode);
	printf("\t Image Base: %x\n", NTHeaders->OptionalHeader.ImageBase);
	printf("\t Section Alignment: %x\n", NTHeaders->OptionalHeader.SectionAlignment);
	printf("\t File Alignment: %x\n", NTHeaders->OptionalHeader.FileAlignment);
	printf("\t Major Operating System Version: %x\n", NTHeaders->OptionalHeader.MajorOperatingSystemVersion);
	printf("\t Minor Operating System Version: %x\n", NTHeaders->OptionalHeader.MinorOperatingSystemVersion);
	printf("\t Major Image Version: %x\n", NTHeaders->OptionalHeader.MajorImageVersion);
	printf("\t Minor Image Version: %x\n", NTHeaders->OptionalHeader.MinorImageVersion);
	printf("\t Major Subsystem Version: %x\n", NTHeaders->OptionalHeader.MajorSubsystemVersion);
	printf("\t Minor Subsystem Version: %x\n", NTHeaders->OptionalHeader.MinorSubsystemVersion);
	printf("\t Win32 Version Value: %x\n", NTHeaders->OptionalHeader.Win32VersionValue);
	printf("\t Size of Image: %x\n", NTHeaders->OptionalHeader.SizeOfImage);
	printf("\t Size of Headers: %x\n", NTHeaders->OptionalHeader.SizeOfHeaders);
	printf("\t Checksum: %x\n", NTHeaders->OptionalHeader.CheckSum);
	printf("\t Subsystem: %x\n", NTHeaders->OptionalHeader.DllCharacteristics);
	printf("\t DLL Characteristics: %x\n", NTHeaders->OptionalHeader.DllCharacteristics);
	printf("\t Size of Stack Reserve: %x\n", NTHeaders->OptionalHeader.SizeOfStackReserve);
	printf("\t Size of Stack Commit: %x\n", NTHeaders->OptionalHeader.SizeOfStackCommit);
	printf("\t Size of Heap Reserve: %x\n", NTHeaders->OptionalHeader.SizeOfHeapReserve);
	printf("\t Size of Heap Commit: %x\n", NTHeaders->OptionalHeader.SizeOfHeapCommit);
	printf("\t Loader Flags: %x\n", NTHeaders->OptionalHeader.LoaderFlags);
	printf("\t Number of RVA and Sizes: %x\n", NTHeaders->OptionalHeader.NumberOfRvaAndSizes);
	printf("\n[            Data Directories           ]\n");
	printf("\t Export Directory Address: 0x%x Size: 0x%x\n", NTHeaders->OptionalHeader.DataDirectory[0].VirtualAddress, NTHeaders->OptionalHeader.DataDirectory[0].Size);
	printf("\t Import Directory Address: 0x%x Size: 0x%x\n", NTHeaders->OptionalHeader.DataDirectory[1].VirtualAddress, NTHeaders->OptionalHeader.DataDirectory[1].Size);


}
