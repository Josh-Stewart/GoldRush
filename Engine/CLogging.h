//CLogging.h

#ifndef CLOGGING_HEADER
#define CLOGGING_HEADER

#include "globals.h"
#include <tlhelp32.h>

class CLogging  
{
private:
	static bool m_fEnableLogging;

public:
	CLogging();
	virtual ~CLogging();

	static void StartLogging();
	static void StopLogging();
	static void LogError(char *lpszText, ...);
	static void LogInfo(char *lpszText, ...);
	static void LogWarning(char *lpszText, ...);
	static DWORD GetMemoryUsage();
	static void LogMemoryUsage();
};

#endif