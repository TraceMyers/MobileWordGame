#include "Tools.h"
// #include "Windows/WindowsPlatformProcess.h"
// #include "HAL/PlatformMisc.h"
// #include "Misc/AssertionMacros.h"
// #include "Logging/LogMacros.h"
// #include "HAL/UnrealMemory.h"
// #include "CoreGlobals.h"
// #include "Containers/UnrealString.h"
// #include "Misc/SingleThreadEvent.h"
// #include "Windows/WindowsHWrapper.h"
// #include "Windows/AllowWindowsPlatformTypes.h"
// 	#include <shellapi.h>
// 	#include <ShlObj.h>
// #include "Windows/HideWindowsPlatformTypes.h"
// #include "Windows/WindowsPlatformMisc.h"
//
// #pragma comment(lib, "psapi.lib")
//
// PRAGMA_DISABLE_UNSAFE_TYPECAST_WARNINGS
// FProcHandle Tools::createProc(
// 	const TCHAR* URL,
// 	const TCHAR* Parms, 
// 	bool bLaunchDetached,
// 	bool bLaunchHidden,
// 	bool bLaunchReallyHidden,
// 	uint32* OutProcessID,
// 	int32 PriorityModifier,
// 	const TCHAR* OptionalWorkingDirectory,
// 	void* PipeWriteChild,
// 	void * PipeReadChild,
// 	bool show_window
// ) {
// 	print("%s", URL);
	//UE_LOG(LogWindows, Log,  TEXT("CreateProc %s %s"), URL, Parms );
	//
	// // initialize process creation flags
	// uint32 CreateFlags = NORMAL_PRIORITY_CLASS;
	// if (PriorityModifier < 0)
	// {
	// 	CreateFlags = (PriorityModifier == -1) ? BELOW_NORMAL_PRIORITY_CLASS : IDLE_PRIORITY_CLASS;
	// }
	// else if (PriorityModifier > 0)
	// {
	// 	CreateFlags = (PriorityModifier == 1) ? ABOVE_NORMAL_PRIORITY_CLASS : HIGH_PRIORITY_CLASS;
	// }
	//
	// if (bLaunchDetached)
	// {
	// 	CreateFlags |= DETACHED_PROCESS;
	// }
	//
	// // initialize window flags
	// uint32 dwFlags = 0;
	// uint16 ShowWindowFlags = (show_window ? SW_SHOW : SW_HIDE);
	// if (bLaunchReallyHidden)
	// {
	// 	dwFlags = STARTF_USESHOWWINDOW;
	// }
	// else if (bLaunchHidden)
	// {
	// 	dwFlags = STARTF_USESHOWWINDOW;
	// 	ShowWindowFlags = SW_SHOWMINNOACTIVE;
	// }
	//
	// if (PipeWriteChild != nullptr || PipeReadChild != nullptr)
	// {
	// 	dwFlags |= STARTF_USESTDHANDLES;
	// }
	//
	// // initialize startup info
	// STARTUPINFO StartupInfo = {
	// 	sizeof(STARTUPINFO),
	// 	NULL, NULL, NULL,
	// 	(DWORD)CW_USEDEFAULT,
	// 	(DWORD)CW_USEDEFAULT,
	// 	(DWORD)CW_USEDEFAULT,
	// 	(DWORD)CW_USEDEFAULT,
	// 	(DWORD)0,
	// 	(DWORD)0,
	// 	(DWORD)0,
	// 	(DWORD)dwFlags,
	// 	ShowWindowFlags,
	// 	0, NULL,
	// 	HANDLE(PipeReadChild),
	// 	HANDLE(PipeWriteChild),
	// 	HANDLE(PipeWriteChild)
	// };
	//
	// bool bInheritHandles = (dwFlags & STARTF_USESTDHANDLES) != 0;
	//
	// // create the child process
	// FString CommandLine = FString::Printf(TEXT("\"%s\" %s"), URL, Parms);
	// PROCESS_INFORMATION ProcInfo;
	//
	// if (!CreateProcess(NULL, CommandLine.GetCharArray().GetData(), nullptr, nullptr, bInheritHandles, (DWORD)CreateFlags, NULL, OptionalWorkingDirectory, &StartupInfo, &ProcInfo))
	// {
	// 	DWORD ErrorCode = GetLastError();
	//
	// 	TCHAR ErrorMessage[512];
	// 	FWindowsPlatformMisc::GetSystemErrorMessage(ErrorMessage, 512, ErrorCode);
	//
	// 	UE_LOG(LogWindows, Warning, TEXT("CreateProc failed: %s (0x%08x)"), ErrorMessage, ErrorCode);
	// 	if (ErrorCode == ERROR_NOT_ENOUGH_MEMORY || ErrorCode == ERROR_OUTOFMEMORY)
	// 	{
	// 		// These errors are common enough that we want some available memory information
	// 		FPlatformMemoryStats Stats = FPlatformMemory::GetStats();
	// 		UE_LOG(LogWindows, Warning, TEXT("Mem used: %.2f MB, OS Free %.2f MB"), Stats.UsedPhysical / 1048576.0f, Stats.AvailablePhysical / 1048576.0f);
	// 	}
	// 	UE_LOG(LogWindows, Warning, TEXT("URL: %s %s"), URL, Parms);
	// 	if (OutProcessID != nullptr)
	// 	{
	// 		*OutProcessID = 0;
	// 	}
	//
	// 	return FProcHandle();
	// }
	//
	// if (OutProcessID != nullptr)
	// {
	// 	*OutProcessID = ProcInfo.dwProcessId;
	// }
	//
	// ::CloseHandle( ProcInfo.hThread );
	//
	// return FProcHandle(ProcInfo.hProcess);
// 	return FProcHandle();
// }
