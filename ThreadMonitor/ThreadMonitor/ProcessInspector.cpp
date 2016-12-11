/*
*
* Name: ProcessInspector.cpp
*
* Description: The following class contains the function that allows us to create a process snapshot and output the info to the user via console
*
*/

/*
*
* Including external librarys
*
*/
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#pragma once

/*
*
* Including local header files
*
*/
#include "ProcessInspector.h"
#include "ErrorHandler.h"
//#include "ThreadInspector.h"
#pragma once

HANDLE hProcessSnap; // handle for process snaphot
HANDLE hProcess; // handle for process
PROCESSENTRY32 pe32; // store the process entry here
DWORD dwPriorityClass; // store priorty class of process
char *str = new char[4046]; // hold conversion here to compare process name
char *processName = new char[4046]; // store process name
int maxThreadUsage = 18; // this is the maximum number of permitted threads, based off research of target program

/*
*
* Function to generate a process snaphot and traverse the process list and output data to console. This function targets the process of the target game
*
*/
BOOL GetProcessList()
{
	// take a snapshot of all processes in the system
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) // invalid handle
	{
		printError(TEXT("CreateToolhelp32Snapshot (of processes)")); // notify user
		return(FALSE);
	}

	pe32.dwSize = sizeof(PROCESSENTRY32); // set the size of the data structure prior to using it.

	// retrieve information about the first process
	if (!Process32First(hProcessSnap, &pe32)) // was it successful?
	{
		printError(TEXT("Process32First")); // notify user
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return(FALSE);
	}

	do // walk snapshot until we find the target process
	{
		wcstombs(str, pe32.szExeFile, 4000); // convert process name so we can string compare

		if (_stricmp(str, processName) == 0) // if we have found the target process
		{
			system("cls");

			// primitve UI
			_tprintf(TEXT("====================================================="));
			_tprintf(TEXT("\n Monitoring Thread Count"));
			_tprintf(TEXT("\n====================================================="));

			// notify user of the data we are monitoring
			_tprintf(TEXT("\n  Process Name: %s"), pe32.szExeFile);
			_tprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
			_tprintf(TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
			_tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
			_tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
		}
		
		// retrieve the priority class
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (hProcess == NULL)
			printError(TEXT("OpenProcess"));
		else
		{
			dwPriorityClass = GetPriorityClass(hProcess);
			if (!dwPriorityClass)
				printError(TEXT("GetPriorityClass"));
			CloseHandle(hProcess);
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap); // close handle on process snapshot
	Sleep(2000); // lets not over-do our checks
	GetProcessList(); // recursive
	return(TRUE);
}

/*
	Function to take users input
*/
void GetProcessName()
{
	std::cout << ("\n Please enter process name: ");
	std::cin >> processName;
}

