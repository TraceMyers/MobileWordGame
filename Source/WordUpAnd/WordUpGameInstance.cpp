#include "WordUpGameInstance.h"
#include "Tools.h"
#include "Blueprint/UserWidget.h"
#include "BUIUploader.h"
#include "Menu.h"
#include "PlayerPawn.h"
#include "BGGrafix.h"
#include "Kismet/GameplayStatics.h"


// buggy include, windows code
#define _WIN32_WINNT_WIN10_TH2 0
#define _WIN32_WINNT_WIN10_RS1 0
#define _WIN32_WINNT_WIN10_RS2 0
#define _WIN32_WINNT_WIN10_RS3 0
#define _WIN32_WINNT_WIN10_RS4 0
#define _WIN32_WINNT_WIN10_RS5 0

#define CURL_STATICLIB
#include "curl/curl.h"

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

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

/*
 * A open mapname?listen (on port 17777)
 * A call url to B IP:17777
 * B open host ip
 */

void UWordUpGameInstance::call_url(const FString& address) {
	print("curling %s", *address);
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, *address);
	curl_easy_setopt(curl, CURLOPT_LOCALPORT, 7777L);
	const CURLcode code = curl_easy_perform(curl);
	print("curl code %d", code);
	curl_easy_cleanup(curl);
}
