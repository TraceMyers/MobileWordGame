#pragma once

#include "GameFramework/PlayerStart.h"
#include "PlayerPawn.h"
#include "CoreMinimal.h"
#include "ServerData.h"
#include "GameFramework/GameModeBase.h"
#include "WordUpAndGameModeBase.generated.h"

UCLASS()
class WORDUPAND_API AWordUpAndGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	UPROPERTY()
	APlayerStart* ps1;
	UPROPERTY()
	APlayerStart* ps2;
	UPROPERTY()
	APlayerController*p1_pc;
	UPROPERTY()
	APlayerController*p2_pc;
	UPROPERTY()
	APlayerPawn* p1_pawn;
	UPROPERTY()
	APlayerPawn* p2_pawn;

	AWordUpAndGameModeBase();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* pc) override;

protected:

private:
	ServerData server_data;
	TSubclassOf<APlayerPawn> BP_PlayerPawn = nullptr;
	int spawn_ctr = 0;
	int controller_ctr = 0;
	bool p1_spawned_alone = false;

	APlayerPawn* spawnPawn(UWorld* world, APlayerController* pc, class APlayerStart* ps) const;
	
};
