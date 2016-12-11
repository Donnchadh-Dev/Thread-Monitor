/*
*
* Name: ErrorHandler.h
*
* Description: The following header file prints any errors we may encounter. It formats the various data types so that we can print them via console.
*
* Author: © Donnchadh Murphy
*
* Date: 04/08/2016
*
* Version 1.0
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
* Function declarations
*
*/
void printError(TCHAR* msg);
