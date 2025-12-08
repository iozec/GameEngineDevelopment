#pragma once
#include <stdarg.h>
#include <cstdio>
#include <windows.h>
#include <Debugapi.h>



	extern int VDebugPrintF(const char* format, va_list argList);
	extern int DebugPrintF(const char* format, ...);
	extern int g_vernosity;
	extern int VerboseDebugPrintF(int verbosity, const char* format, ...);

enum Verbosity
{
	None,
	Error,
	Warning,
	Info,
	All

};

