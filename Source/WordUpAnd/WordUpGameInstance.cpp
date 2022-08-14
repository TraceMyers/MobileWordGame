#include "WordUpGameInstance.h"
#include "Tools.h"
#include "Blueprint/UserWidget.h"
#include "BUIUploader.h"
#include "Menu.h"


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
}

void UWordUpGameInstance::quit() const {
	APlayerController* player_controller = GetFirstLocalPlayerController();
	player_controller->ConsoleCommand("quit");
}

void UWordUpGameInstance::showMenu() {
	menu->show(GetFirstLocalPlayerController());
	pair_fairy->pairServerSend();
}
