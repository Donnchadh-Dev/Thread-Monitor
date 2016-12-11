/*
*
* Name: main.cpp
*
* Description: The following class class our recursive process snapshot function and presents the user with the initial primitive UI
*
*/

/*
*
*	Including external librarys
*
*/
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma once

/*
*
* Including local header files
*
*/
#include "ErrorHandler.h"

using namespace std;

BOOL GetProcessList(); //  recursive function to find target process
void GetProcessName();

LPCWSTR WindowName = L"Thread Monitor"; // naming our window
int main(void)
{
	SetConsoleTitle(WindowName); // setting the window name for the hack

	// primitive UI
	_tprintf(TEXT("====================================================="));
	_tprintf(TEXT("\n Thread Monitor by Donnchadh"));
	_tprintf(TEXT("\n====================================================="));
	_tprintf(TEXT("\n Please enter the name of the process you want to monitor. For example process.exe"));

	GetProcessName();

	GetProcessList(); // lets start examining the target process if it is running

	return 0;
}
