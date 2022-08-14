#pragma once

#include "CoreMinimal.h"

#define print(x, ...) \
	if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT(x), __VA_ARGS__));}