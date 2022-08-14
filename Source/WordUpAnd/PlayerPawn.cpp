#include "PlayerPawn.h"

#include "Camera/CameraComponent.h"

APlayerPawn::APlayerPawn() {
	PrimaryActorTick.bCanEverTick = true;

	camera = CreateDefaultSubobject<UCameraComponent>(FName("camera"));
	camera->SetupAttachment(GetRootComponent());
}

void APlayerPawn::BeginPlay() {
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

