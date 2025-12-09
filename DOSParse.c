#ifndef UNICODE
#define UNICODE
#endif

#ifndef DOSPARSE_H
#define DOSPARSE_H

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
		printf("[PEADetective] DOS Signature Matched: (MZ)\n");
	}

	printf("[               DOS Header               ]\n");
	printf("[PEADetective] Magic Number: %x\n", DOSHeader->e_magic);
	printf("[PEADetective] Bytes on last page of file: %x\n", DOSHeader->e_cblp);
	printf("[PEADetective] Pages in file: %x\n", DOSHeader->e_cp);
	printf("[PEADetective] Relocations: %x\n", DOSHeader->e_crlc);
	printf("[PEADetective] Size of header in paragraphs: %x\n", DOSHeader->e_cparhdr);
	printf("[PEADetective] Minimum extra paragraphs needed: %x\n", DOSHeader->e_minalloc);
	printf("[PEADetective] Maximum extra paragraphs needed: %x\n", DOSHeader->e_maxalloc);
	printf("[PEADetective] Initial (relative) SS value: %x\n", DOSHeader->e_ss);
	printf("[PEADetective] Initial SP value: %x\n", DOSHeader->e_sp);
	printf("[PEADetective] Inital Checksum: %x\n", DOSHeader->e_csum);
	printf("[PEADetective] Inital IP value: %x\n", DOSHeader->e_ip);
	printf("[PEADetective] Inital (relative) CS value: %x\n", DOSHeader->e_cs);
	printf("[PEADetective] File address of relocation table: %x\n", DOSHeader->e_lfarlc);
	printf("[PEADetective] Overlay number: %x\n", DOSHeader->e_ovno);
	printf("[PEADetective] Reserved Words: %x\n", DOSHeader->e_res[4]);
	printf("[PEADetective] OEM identifier: %x\n", DOSHeader->e_oemid);
	printf("[PEADetective] OEM information: %x\n", DOSHeader->e_oeminfo);
	printf("[PEADetective] Reserved Words 2: %x\n", DOSHeader->e_res2);
	printf("[PEADetective] File address for new exe header: %x\n", DOSHeader->e_lfanew);
}

#endif