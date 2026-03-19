#ifndef UNICODE
#define UNICODE
#endif



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

PIMAGE_DOS_HEADER GetDOSHeader(LPVOID MappedFile)
{
	PIMAGE_DOS_HEADER DOSHeader = (PIMAGE_DOS_HEADER)MappedFile;
	return DOSHeader;
}

bool VerifyMagicHeader(PIMAGE_DOS_HEADER DOSHeader)
{
	if (DOSHeader->e_magic == IMAGE_DOS_SIGNATURE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void OutputDOSHeader(PIMAGE_DOS_HEADER DOSHeader)
{
	if (VerifyMagicHeader(DOSHeader))
	{
		printf("\t DOS Signature Matched: (MZ)\n");
	}

	printf("[               DOS Header               ]\n");
	printf("\t Magic Number: %x\n", DOSHeader->e_magic);
	printf("\t Bytes on last page of file: %x\n", DOSHeader->e_cblp);
	printf("\t Pages in file: %x\n", DOSHeader->e_cp);
	printf("\t Relocations: %x\n", DOSHeader->e_crlc);
	printf("\t Size of header in paragraphs: %x\n", DOSHeader->e_cparhdr);
	printf("\t Minimum extra paragraphs needed: %x\n", DOSHeader->e_minalloc);
	printf("\t Maximum extra paragraphs needed: %x\n", DOSHeader->e_maxalloc);
	printf("\t Initial (relative) SS value: %x\n", DOSHeader->e_ss);
	printf("\t Initial SP value: %x\n", DOSHeader->e_sp);
	printf("\t Inital Checksum: %x\n", DOSHeader->e_csum);
	printf("\t Inital IP value: %x\n", DOSHeader->e_ip);
	printf("\t Inital (relative) CS value: %x\n", DOSHeader->e_cs);
	printf("\t File address of relocation table: %x\n", DOSHeader->e_lfarlc);
	printf("\t Overlay number: %x\n", DOSHeader->e_ovno);
	printf("\t Reserved Words: %x\n", DOSHeader->e_res[4]);
	printf("\t OEM identifier: %x\n", DOSHeader->e_oemid);
	printf("\t OEM information: %x\n", DOSHeader->e_oeminfo);
	printf("\t Reserved Words 2: %x\n", DOSHeader->e_res2);
	printf("\t File address for new exe header: %x\n", DOSHeader->e_lfanew);
}
