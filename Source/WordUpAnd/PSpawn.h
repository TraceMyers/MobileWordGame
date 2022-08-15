#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PSpawn.generated.h"

UCLASS()
class WORDUPAND_API APSpawn : public AStaticMeshActor {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	int player;
	
};
