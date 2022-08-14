#pragma once

#include "CoreMinimal.h"
#include "ServerData.h"
#include "GameFramework/GameModeBase.h"
#include "WordUpAndGameModeBase.generated.h"

UCLASS()
class WORDUPAND_API AWordUpAndGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:

private:
	ServerData server_data;	
	
};
