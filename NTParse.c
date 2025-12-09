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
	printf("[PEADetective] Signature: %x\n", NTHeaders->Signature);
	printf("\n[              FILE HEADER               ]\n");
	printf("[PEADetective] Machine: %x\n", NTHeaders->FileHeader.Machine);
	printf("[PEADetective] Number of Sections: %x\n", NTHeaders->FileHeader.NumberOfSections);
	printf("[PEADetective] Time Stamp: %x\n", NTHeaders->FileHeader.TimeDateStamp);
	printf("[PEADetective] Pointer to Symbol Table: %x\n", NTHeaders->FileHeader.PointerToSymbolTable);
	printf("[PEADetective] Number of Symbols: %x\n", NTHeaders->FileHeader.NumberOfSymbols);
	printf("[PEADetective] Size of Optional Header: %x\n", NTHeaders->FileHeader.SizeOfOptionalHeader);
	printf("[PEADetective] Characteristics: %x\n", NTHeaders->FileHeader.Characteristics);
	printf("\n[            OPTIONAL HEADER           ]\n");
	printf("[PEADetective] Magic Header: %x\n", NTHeaders->OptionalHeader.Magic);
	printf("[PEADetective] Major Linker Version: %x\n", NTHeaders->OptionalHeader.MajorLinkerVersion);
	printf("[PEADetective] Minor Linker Version: %x\n", NTHeaders->OptionalHeader.MinorLinkerVersion);
	printf("[PEADetective] Size of Code: %x\n", NTHeaders->OptionalHeader.SizeOfCode);
	printf("[PEADetective] Size of Initialized Data: %x\n", NTHeaders->OptionalHeader.SizeOfInitializedData);
	printf("[PEADetective] Size of UnInitalized Data: %x\n", NTHeaders->OptionalHeader.SizeOfUninitializedData);
	printf("[PEADetective] Address of Entry Point '.text': %x\n", NTHeaders->OptionalHeader.AddressOfEntryPoint);
	printf("[PEADetective] Base of Code: %x\n", NTHeaders->OptionalHeader.BaseOfCode);
	printf("[PEADetective] Image Base: %x\n", NTHeaders->OptionalHeader.ImageBase);
	printf("[PEADetective] Section Alignment: %x\n", NTHeaders->OptionalHeader.SectionAlignment);
	printf("[PEADetective] File Alignment: %x\n", NTHeaders->OptionalHeader.FileAlignment);
	printf("[PEADetective] Major Operating System Version: %x\n", NTHeaders->OptionalHeader.MajorOperatingSystemVersion);
	printf("[PEADetective] Minor Operating System Version: %x\n", NTHeaders->OptionalHeader.MinorOperatingSystemVersion);
	printf("[PEADetective] Major Image Version: %x\n", NTHeaders->OptionalHeader.MajorImageVersion);
	printf("[PEADetective] Minor Image Version: %x\n", NTHeaders->OptionalHeader.MinorImageVersion);
	printf("[PEADetective] Major Subsystem Version: %x\n", NTHeaders->OptionalHeader.MajorSubsystemVersion);
	printf("[PEADetective] Minor Subsystem Version: %x\n", NTHeaders->OptionalHeader.MinorSubsystemVersion);
	printf("[PEADetective] Win32 Version Value: %x\n", NTHeaders->OptionalHeader.Win32VersionValue);
	printf("[PEADetective] Size of Image: %x\n", NTHeaders->OptionalHeader.SizeOfImage);
	printf("[PEADetective] Size of Headers: %x\n", NTHeaders->OptionalHeader.SizeOfHeaders);
	printf("[PEADetective] Checksum: %x\n", NTHeaders->OptionalHeader.CheckSum);
	printf("[PEADetective] Subsystem: %x\n", NTHeaders->OptionalHeader.DllCharacteristics);
	printf("[PEADetective] DLL Characteristics: %x\n", NTHeaders->OptionalHeader.DllCharacteristics);
	printf("[PEADetective] Size of Stack Reserve: %x\n", NTHeaders->OptionalHeader.SizeOfStackReserve);
	printf("[PEADetective] Size of Stack Commit: %x\n", NTHeaders->OptionalHeader.SizeOfStackCommit);
	printf("[PEADetective] Size of Heap Reserve: %x\n", NTHeaders->OptionalHeader.SizeOfHeapReserve);
	printf("[PEADetective] Size of Heap Commit: %x\n", NTHeaders->OptionalHeader.SizeOfHeapCommit);
	printf("[PEADetective] Loader Flags: %x\n", NTHeaders->OptionalHeader.LoaderFlags);
	printf("[PEADetective] Number of RVA and Sizes: %x\n", NTHeaders->OptionalHeader.NumberOfRvaAndSizes);
	printf("\n[            Data Directories           ]\n");
	printf("[PEADetective] Export Directory Address: 0x%x Size: 0x%x\n", NTHeaders->OptionalHeader.DataDirectory[0].VirtualAddress, NTHeaders->OptionalHeader.DataDirectory[0].Size);
	printf("[PEADetective] Import Directory Address: 0x%x Size: 0x%x\n", NTHeaders->OptionalHeader.DataDirectory[1].VirtualAddress, NTHeaders->OptionalHeader.DataDirectory[1].Size);


}

#endif