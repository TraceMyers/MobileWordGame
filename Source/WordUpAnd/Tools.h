#pragma once

#include "CoreMinimal.h"

#define print(x, ...) \
	if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT(x), __VA_ARGS__));}

namespace Tools {
	// FProcHandle createProc(
	// 	const TCHAR* URL,
	// 	const TCHAR* Parms,
	// 	bool bLaunchDetached,
	// 	bool bLaunchHidden,
	// 	bool bLaunchReallyHidden,
	// 	uint32* OutProcessID,
	// 	int32 PriorityModifier,
	// 	const TCHAR* OptionalWorkingDirectory,
	// 	void* PipeWriteChild,
	// 	void * PipeReadChild = nullptr,
	// 	bool show_window=false
	// );
}
