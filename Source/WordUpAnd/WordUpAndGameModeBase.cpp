// Copyright Epic Games, Inc. All Rights Reserved.


#include "WordUpAndGameModeBase.h"

void AWordUpAndGameModeBase::InitGame(
	const FString& MapName,
	const FString& Options,
	FString& ErrorMessage
) {
	Super::InitGame(MapName, Options, ErrorMessage);
	server_data.initSession();
}
