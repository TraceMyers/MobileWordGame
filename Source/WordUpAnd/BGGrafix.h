#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGGrafix.generated.h"

UENUM()
enum BGGRAFIX_BG_NAME {
	BGGRAFIX_PURPLE_PILLARS	
};

UCLASS()
class WORDUPAND_API ABGGrafix : public AActor {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* bg_plane;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* direction_cone;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	class ADirectionalLight* light;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float speed = 3.0f;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TEnumAsByte<BGGRAFIX_BG_NAME> bg_name;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	int obj_ct = 200;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float travel_rot = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float pitch_rot = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool roll = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UMaterial* m_purple;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UStaticMesh* mesh_pillar;
	
	ABGGrafix();
	virtual void Tick(float DeltaTime) override;
	void setBG(BGGRAFIX_BG_NAME name);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<class ABGGrafixObject*> objects;

	TSubclassOf<ABGGrafixObject> BP_BGGrafixObject;
	FVector obj_move_dir;
	FRotator obj_rotation;
	float spawn_radius_naive;
	float spawn_radius;
	float spawn_radius_sq;

	FVector purple_pillars_scale = FVector(4.0f, 4.0f, 8.0f);
};
