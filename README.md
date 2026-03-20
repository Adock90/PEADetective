# PEADetective
A Small PE Application (PEA) File Header Inspector. Work is in Progress with DLL Imports. 



# Building Source

1:
git clone <code>git clone https://github.com/Adock90/PEADetective</code>

or 

Download ZIP

2:

In src there is a Move.ps1 Scipt. Run it with.

<code>powershell.exe -ExeuctionPolicy Bypass -File src/Move.ps1</code>

3:

Open the PEADetective.sln file in Visual Studio. Then build with Ctrl+Shift+B.


# Running it

<code>./PEADetective.exe [File] [Sections]</code>

[File]: The path to the PE File. Can be: ".exe", ".dll", ".scr", ".sys", ".efi".

[Sections]: The different Sections of the PE file. These include: "--DOS"(Dos Headers), "--NT"(NT Headers), "--SECTION"(Section Headers) and "--DLL"(Imported DLLs). "--all"(for all sections).
# Examples

This Outputs DOS and NT Headers from the PEADetective.exe.

<code>PEADetective.exe ./PEADetective.exe --DOS --NT</code>

This Outputs All Headers and Sections in Windows Calculator.

<code>PEADetective.exe C:\Windows\System32\calc.exe --all</code>

If you need help just ask:

<code>PEADetective.exe --h</code>

# Sources used:

<a href="https://learn.microsoft.com/en-us/windows/win32/debug/pe-format">Microsoft</a>

<a href="https://www.ired.team/miscellaneous-reversing-forensics/windows-kernel-internals/pe-file-header-parser-in-c++">Red Team Notes</a>
