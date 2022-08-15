#include "WordUpAndGameModeBase.h"
#include "Tools.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AWordUpAndGameModeBase::AWordUpAndGameModeBase() {
	static ConstructorHelpers::FClassFinder<APlayerPawn>
		PlayerPawn_BP(TEXT("/Game/Blueprints/BP_PlayerPawn.BP_PlayerPawn_C"));
	if (PlayerPawn_BP.Class) {
		BP_PlayerPawn = PlayerPawn_BP.Class;
	}
	else {
		print("AWordUpAndGameModeBase::AWordUpAndGameModeBase(): couldn't find BP_PlayerPawn");
	}
}

void AWordUpAndGameModeBase::InitGame(
	const FString& MapName,
	const FString& Options,
	FString& ErrorMessage
) {
	Super::InitGame(MapName, Options, ErrorMessage);
	server_data.initSession();
}

void AWordUpAndGameModeBase::BeginPlay() {
	Super::BeginPlay();
	UWorld* world = GetWorld();
	if (BP_PlayerPawn && world) {
		TArray<AActor*> player_starts;
		UGameplayStatics::GetAllActorsOfClass(world, APlayerStart::StaticClass(), player_starts);
		const FString ps1_start_name = "PlayerStart1";
		if (player_starts.Num() == 1 || (player_starts.Num() > 1 && !p2_pc)) {
			ps1 = Cast<APlayerStart>(player_starts[0]);
			spawnPawn(world, p1_pc, ps1);
			p1_spawned_alone = true;
			if (player_starts.Num() > 1) {
				ps2 = Cast<APlayerStart>(player_starts[1]);
			}	
		}
		else if (player_starts.Num() > 1) {
			ps1 = Cast<APlayerStart>(player_starts[0]);
			ps2 = Cast<APlayerStart>(player_starts[1]);
			// if the first player start we find is named "PlayerStart1", spawn in the given order
			// any other naming configuration spawns players in the other order, including
			// if the player starts have whatever names; more than 2 player starts gives
			// potentially random spawn locations, even if one of them is called "PlayerStart1"
			if (ps1->GetName() == ps1_start_name) {
				spawnPawn(world, p1_pc, ps1);
				spawnPawn(world, p2_pc, ps2);
			}
			else {
				spawnPawn(world, p1_pc, ps2);
				spawnPawn(world, p2_pc, ps1);
			}
		}
		else {
			print("AWordUpAndGameModeBase::BeginPlay(): no player starts");
		}
	}
	else {
		print("AWordUpAndGameModeBase::BeginPlay(): couldn't find BP_PlayerPawn OR no world");
	}
}

void AWordUpAndGameModeBase::PostLogin(APlayerController* pc)  {
	// Super::PostLogin(NewPlayer);
	// print("%s", *pc->GetName());
	if (!p1_pc) {
		p1_pc = pc;
	}
	else if (!p2_pc) {
		p2_pc = pc;
		if (p1_spawned_alone && ps2) {
			spawnPawn(GetWorld(), p2_pc, ps2);
		}
	}
}

APlayerPawn* AWordUpAndGameModeBase::spawnPawn(UWorld* world, APlayerController* pc, APlayerStart* ps) const {
	APlayerPawn* pawn = Cast<APlayerPawn>(world->SpawnActor(BP_PlayerPawn));
	pawn->SetActorLocation(ps->GetActorLocation());
	pawn->SetActorRotation(ps->GetActorRotation());
	pc->Possess(pawn);
	pc->SetPawn(pawn);
	ps->Destroy();
	return pawn;
}
