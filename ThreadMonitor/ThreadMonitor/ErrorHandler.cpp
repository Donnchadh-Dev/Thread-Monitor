/*
*
* Name: ErrorHandler.cpp
*
* Description: The following class notifys the user of any errors when reading processes
*
* Author: © Donnchadh Murphy
*
* Date: 05/08/2016
*
* Version 1.1
*
*/

/*
*
*	Including external librarys
*
*/
#include <Windows.h>
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
* Function to notify the user of any errors
*
*/
void printError(TCHAR* msg)
{
	DWORD eNum; // hold DWORD
	TCHAR sysMsg[256]; // char array to hold message
	TCHAR* p; // pointer to char array

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// output the message to console
	//_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg); // commented out as it made the console ilegible
}