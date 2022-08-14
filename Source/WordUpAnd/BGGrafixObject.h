#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BGGrafixObject.generated.h"

UENUM()
enum BGGRAFIX_OBJ_TYPE {
	BGGRAFIX_PILLAR	
};

UENUM()
enum BGGRAFIX_MAT_NAME {
	BGGRAFIX_PURPLE
};

UCLASS()
class WORDUPAND_API ABGGrafixObject : public AStaticMeshActor {
	GENERATED_BODY()
	
public:
	FVector spawn_loc;
	
	ABGGrafixObject();
	void init(
		UStaticMesh* static_mesh,
		UMaterial* material,
		const FVector& scale,
		const FRotator& rotation
	);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TEnumAsByte<BGGRAFIX_OBJ_TYPE> bggrafix_obj_type;
};
