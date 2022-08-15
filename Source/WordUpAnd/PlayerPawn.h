#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class WORDUPAND_API APlayerPawn : public APawn {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCameraComponent* camera;
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	UStaticMeshComponent* static_mesh;
	UPROPERTY(ReplicatedUsing=OnRep_replicatedFreeLoc)
	FVector replicated_free_loc;
	UPROPERTY(ReplicatedUsing=OnRep_replicatedFreeRot)
	FRotator replicated_free_rot;
	UPROPERTY(Replicated)
	FVector sim_linear_velocity;
	UPROPERTY(Replicated)
	FRotator sim_angular_velocity;
	
	APlayerPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void lookTilt(float throttle);
	void lookPan(float throttle);
	void moveFB(float throttle);
	void moveLR(float throttle);
	void lookAndMove(float delta_time);
	void setFreeRoam(bool setting);
	
	UFUNCTION(Server, Reliable)
	void server_lookTilt(float amt);
	UFUNCTION(Server, Reliable)
	void server_lookPan(float amt);
	UFUNCTION(Server, Reliable, WithValidation)
	void server_moveFB(float amt);
	UFUNCTION(Server, Reliable, WithValidation)
	void server_moveLR(float amt);
	UFUNCTION()
	void OnRep_replicatedFreeLoc();
	UFUNCTION()
	void OnRep_replicatedFreeRot();

protected:
	virtual void BeginPlay() override;

private:
	static constexpr int AV_MAX = 10;
	
	bool can_look_and_move = false;
	float look_speed = 90.0f * PI / 180.0f;
	float move_speed = 300.0f;
	const float _MAX_PITCH = 80.0f;
	const float _MIN_PITCH = -80.0f;
	
	FVector play_loc;
	FRotator play_rot;
	FVector free_loc;
	FRotator free_rot;
	FVector tick_mov;
	FRotator tick_rot;
};