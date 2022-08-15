#include "PlayerPawn.h"
#include "Tools.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/GameSession.h"
#include "Net/UnrealNetwork.h"


APlayerPawn::APlayerPawn() {
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(FName("root"));
	if (root) {
		SetRootComponent(root);
	}
	camera = CreateDefaultSubobject<UCameraComponent>(FName("camera"));
	camera->SetupAttachment(GetRootComponent());
	static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("static mesh"));
	static_mesh->SetupAttachment(GetRootComponent());	
	bReplicates = true;
}


void APlayerPawn::BeginPlay() {
	Super::BeginPlay();
	play_loc = GetActorLocation();
	play_rot = GetActorRotation();
	free_loc = play_loc;
	free_rot = play_rot;

	// frequency low since APlayerPawn is mainly used for debug freeRoam(noclip)
	// would be better to just make freeRoam local & unreplicated, but it's not important
	// and I was just using this to learn basic replication
	if (HasAuthority()) {
		NetUpdateFrequency = 3;
	}
}

FString getEnumText(ENetRole Role) {
	switch(Role) {
	case ROLE_None:
		return "None";
	case ROLE_SimulatedProxy:
		return "SimulatedProxy";
	case ROLE_AutonomousProxy:
		return "AutonomousProxy";
	case ROLE_Authority:
		return "Authority";
	default:
		return "Error";
	}
}

void APlayerPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (can_look_and_move) {
		lookAndMove(DeltaTime);
		tick_mov = FVector::ZeroVector;
		tick_rot = FRotator::ZeroRotator;
	}

	DrawDebugString(
		GetWorld(),
		FVector(0, 0, 100.0f),
		getEnumText(GetLocalRole()),
		this,
		FColor::White,
		DeltaTime
	);
}

void APlayerPawn::OnRep_replicatedFreeLoc() {
	SetActorLocation(replicated_free_loc);
}

void APlayerPawn::OnRep_replicatedFreeRot() {
	SetActorRotation(replicated_free_rot);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("LookTilt", this, &APlayerPawn::lookTilt);
	PlayerInputComponent->BindAxis("LookPan", this, &APlayerPawn::lookPan);
	PlayerInputComponent->BindAxis("MoveFB", this, &APlayerPawn::moveFB);
	PlayerInputComponent->BindAxis("MoveLR", this, &APlayerPawn::moveLR);
}

void APlayerPawn::lookTilt(float throttle) {
	const float amt = throttle * look_speed;
	tick_rot.Pitch += amt;
	server_lookTilt(amt);
}

void APlayerPawn::lookPan(float throttle) {
	const float amt = throttle * look_speed;	
	tick_rot.Yaw += amt;
	server_lookPan(amt);
}

void APlayerPawn::moveFB(float throttle) {
	const float amt = throttle * move_speed;	
	tick_mov.Y += amt;
	server_moveFB(amt);
}

void APlayerPawn::moveLR(float throttle) {
	const float amt = throttle * move_speed;	
	tick_mov.X += amt;
	server_moveLR(amt);
}

void APlayerPawn::lookAndMove(float delta_time) {
	FRotator rot;
	if (GetLocalRole() == ROLE_SimulatedProxy) {
		free_loc = GetActorLocation() + sim_linear_velocity * delta_time;
		rot = sim_angular_velocity * delta_time;
	}
	else {
		const FVector linear_velocity = 
			(GetActorForwardVector() * tick_mov.Y + GetActorRightVector() * tick_mov.X);
		free_loc = GetActorLocation() + linear_velocity * delta_time;
		rot = tick_rot * delta_time;
		
		if (HasAuthority()) {
			sim_linear_velocity = linear_velocity;
			sim_angular_velocity = tick_rot;
			replicated_free_loc = free_loc;
			replicated_free_rot = free_rot;
		}
	}
	const FQuat rot_delta_yaw(GetActorUpVector(), rot.Yaw);
	const FQuat rot_delta_pitch(-GetActorRightVector(), rot.Pitch);
	AddActorWorldRotation(rot_delta_yaw);	
	AddActorWorldRotation(rot_delta_pitch);
	free_rot = GetActorRotation();
	free_rot.Roll = 0.0f;
	if (free_rot.Pitch > _MAX_PITCH) {
		free_rot.Pitch = _MAX_PITCH;
	}
	else if (free_rot.Pitch < _MIN_PITCH) {
		free_rot.Pitch = _MIN_PITCH;
	}
	SetActorRotation(free_rot);
	SetActorLocation(free_loc);
}

void APlayerPawn::setFreeRoam(bool setting) {
	if (setting) {
		camera->SetProjectionMode(ECameraProjectionMode::Perspective);
		SetActorLocation(free_loc);
		SetActorRotation(free_rot);
		can_look_and_move = true;
	}
	else {
		camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
		SetActorLocation(play_loc);
		SetActorRotation(play_rot);
		can_look_and_move = false;
	}
}

void APlayerPawn::server_lookTilt_Implementation(float amt) {
	tick_rot.Pitch += amt;
}

void APlayerPawn::server_lookPan_Implementation(float amt) {
	tick_rot.Yaw += amt;	
}

void APlayerPawn::server_moveFB_Implementation(float amt) {
	tick_mov.Y += amt;
}

bool APlayerPawn::server_moveFB_Validate(float amt) {
	return FMath::Abs(amt) <= move_speed;
}

void APlayerPawn::server_moveLR_Implementation(float amt) {
	tick_mov.X += amt;
}

bool APlayerPawn::server_moveLR_Validate(float amt) {
	return FMath::Abs(amt) <= move_speed;
}

void APlayerPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerPawn, replicated_free_loc);
	DOREPLIFETIME(APlayerPawn, replicated_free_rot);
	DOREPLIFETIME(APlayerPawn, sim_linear_velocity);
	DOREPLIFETIME(APlayerPawn, sim_angular_velocity);
}
