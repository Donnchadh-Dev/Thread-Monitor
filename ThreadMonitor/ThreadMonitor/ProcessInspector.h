/*
*
* Name: ProcessInspector.h
*
* Description: The following header file contains our function declaration which allows us to iterate through the process snapshot
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
#include <fstream>
#include <sstream>
#pragma once

/*
*
* Including local header files
*
*/
#include "ErrorHandler.h"
#pragma once

/*
*
* Function declarations
*
*/
BOOL ListProcessModules(DWORD dwPID);

void GetProcessName();