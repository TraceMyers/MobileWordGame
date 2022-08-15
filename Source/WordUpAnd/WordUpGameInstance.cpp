#include "WordUpGameInstance.h"
#include "Tools.h"
#include "Blueprint/UserWidget.h"
#include "BUIUploader.h"
#include "Menu.h"
#include "PlayerPawn.h"
#include "BGGrafix.h"
#include "Kismet/GameplayStatics.h"


UWordUpGameInstance::UWordUpGameInstance(const FObjectInitializer& object_initializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> MENU_BP(TEXT("/Game/Blueprints/BP_MENU.BP_MENU_C"));
	if (!MENU_BP.Class) {
		return;
	}
	BP_Menu = MENU_BP.Class;
	pair_fairy = CreateDefaultSubobject<UBUIUploader>(FName("pair fairy"));
}

void UWordUpGameInstance::Init() {
	Super::Init();
	menu = CreateWidget<UMenu>(this, BP_Menu);
	menu->setGameInstance(this);
	pair_fairy->setGameInstance(this);
}

void UWordUpGameInstance::quit() const {
	APlayerController* player_controller = GetFirstLocalPlayerController();
	if (player_controller) {
		player_controller->ConsoleCommand("quit");
	}
}

void UWordUpGameInstance::showMenu() {
	menu->show(GetFirstLocalPlayerController());
}

void UWordUpGameInstance::pair_server_send(const FString& message) const {
	pair_fairy->pairServerSend(message);
}

void UWordUpGameInstance::free_roam(int setting) const {
	const APlayerController* player_controller = GetFirstLocalPlayerController();
	if (player_controller) {
		APlayerPawn* player_pawn = Cast<APlayerPawn>(player_controller->GetPawn());
		if (player_pawn) {
			player_pawn->setFreeRoam(setting != 0);
		}
	}
}

void UWordUpGameInstance::clientMessage(const FString& message) {
	APlayerController* player_controller = GetFirstLocalPlayerController();
	if (player_controller) {
		player_controller->ClientMessage(message);
	}
}

void UWordUpGameInstance::host() {
	print("hosting");
	
	UWorld* world = GetWorld();
	if (!world) {
		return;
	}
	menu->hide();
	ABGGrafix* bg_grafix = 
		Cast<ABGGrafix>(UGameplayStatics::GetActorOfClass(world, ABGGrafix::StaticClass()));
	if (bg_grafix) {
		bg_grafix->tear_down();
	}
	world->ServerTravel("/Game/Maps/TestMultiMap?listen");
}

void UWordUpGameInstance::join(const FString& address) {
	print("joining %s", *address);
	
	APlayerController* player_controller = GetFirstLocalPlayerController();
	if (!player_controller) {
		return;
	}
	menu->hide();
	ABGGrafix* bg_grafix = 
		Cast<ABGGrafix>(UGameplayStatics::GetActorOfClass(GetWorld(), ABGGrafix::StaticClass()));
	if (bg_grafix) {
		bg_grafix->tear_down();
	}
	player_controller->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}