#include "Menu.h"

#include "Tools.h"
#include "Components/Button.h"
#include "WordUpGameInstance.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

class UTextBlock;

bool UMenu::Initialize() {
	const bool super_init = Super::Initialize();
	if (!super_init) {
		return false;
	}
	play_button->OnClicked.AddDynamic(this, &UMenu::onPlayButtonSelected);
	settings_button->OnClicked.AddDynamic(this, &UMenu::onSettingsButtonSelected);
	how_to_button->OnClicked.AddDynamic(this, &UMenu::onHowToButtonSelected);
	exit_button->OnClicked.AddDynamic(this, &UMenu::onExitButtonSelected);
	exit_yes_button->OnClicked.AddDynamic(this, &UMenu::onExitYesButtonSelected);
	exit_no_button->OnClicked.AddDynamic(this, &UMenu::onExitNoButtonSelected);
	back_button->OnClicked.AddDynamic(this, &UMenu::onBackButtonSelected);
	
	play_button->OnHovered.AddDynamic(this, &UMenu::onPlayButtonHovered);
	settings_button->OnHovered.AddDynamic(this, &UMenu::onSettingsButtonHovered);
	how_to_button->OnHovered.AddDynamic(this, &UMenu::onHowToButtonHovered);
	exit_button->OnHovered.AddDynamic(this, &UMenu::onExitButtonHovered);
	
	play_button->OnUnhovered.AddDynamic(this, &UMenu::onPlayButtonUnhovered);
	settings_button->OnUnhovered.AddDynamic(this, &UMenu::onSettingsButtonUnhovered);
	how_to_button->OnUnhovered.AddDynamic(this, &UMenu::onHowToButtonUnhovered);
	exit_button->OnUnhovered.AddDynamic(this, &UMenu::onExitButtonUnhovered);

	return true;
}

void UMenu::setGameInstance(UWordUpGameInstance* _game_instance) {
	game_instance = _game_instance;
}

void UMenu::begin() {
	
}

void UMenu::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) {
	Super::OnAnimationFinishedPlaying(Player);
	const UWidgetAnimation* anim = Player.GetAnimation();
	if (menu_trans_stage == MENU_TRANS_EXIT_ANIM && anim == transition_animations[0]) {
		setActiveMenu(trans_to_menu, current_menu);
		current_menu = trans_to_menu;
		if (transition_animations[1]) {
			PlayAnimation(transition_animations[1]);
			menu_trans_stage = MENU_TRANS_ENTER_ANIM;
		}
		else {
			menu_trans_stage = MENU_TRANS_NONE;
		}
	}
	else if (menu_trans_stage == MENU_TRANS_ENTER_ANIM && anim == transition_animations[1]) {
		menu_trans_stage = MENU_TRANS_NONE;
	}
	else if (looping_animation) {
		PlayAnimation(looping_animation);		
	}
}

void UMenu::show(APlayerController* player_controller) {
	AddToViewport();
	FInputModeUIOnly input_mode;
	input_mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	player_controller->SetInputMode(input_mode);
	player_controller->bShowMouseCursor = true;

	hideAll();
	transitionMenu(MENU_NAME_MAIN);	
}

void UMenu::hide(APlayerController* player_controller) {
	RemoveFromViewport();	
}

void UMenu::onPlayButtonSelected() {
	transitionMenu(MENU_NAME_PLAY, MENU_NAME_MAIN);
}

void UMenu::onSettingsButtonSelected() {
	
}

void UMenu::onHowToButtonSelected() {
	
}

void UMenu::onExitButtonSelected() {
	setActiveMenu(MENU_NAME_EXIT, MENU_NAME_MAIN);
}

void UMenu::onPlayButtonHovered() {
	if (looping_animation != play_hover && menu_trans_stage == MENU_TRANS_NONE) {
		PlayAnimation(play_hover);
		looping_animation = play_hover;
	}
}

void UMenu::onSettingsButtonHovered() {
	if (looping_animation != settings_hover && menu_trans_stage == MENU_TRANS_NONE) {
		PlayAnimation(settings_hover);
		looping_animation = settings_hover;
	}
}

void UMenu::onHowToButtonHovered() {
	if (looping_animation != how_to_hover && menu_trans_stage == MENU_TRANS_NONE) {
		PlayAnimation(how_to_hover);
		looping_animation = how_to_hover;
	}
}

void UMenu::onExitButtonHovered() {
	PlayAnimation(exit_hover);	
}

void UMenu::onPlayButtonUnhovered() {
	StopAnimation(play_hover);
	looping_animation = nullptr;	
}

void UMenu::onSettingsButtonUnhovered() {
	StopAnimation(settings_hover);	
	looping_animation = nullptr;	
}

void UMenu::onHowToButtonUnhovered() {
	StopAnimation(how_to_hover);
	looping_animation = nullptr;	
}

void UMenu::onExitButtonUnhovered() {
	PlayAnimation(exit_unhover);
}

void UMenu::onExitYesButtonSelected() {
	game_instance->quit();
}

void UMenu::onExitNoButtonSelected() {
	setActiveMenu(MENU_NAME_MAIN, MENU_NAME_EXIT);
}

void UMenu::onBackButtonSelected() {
	transitionMenu(MENU_NAME_MAIN, current_menu);
}

void UMenu::transitionMenu(MENU_NAME end_menu, MENU_NAME start_menu) {
	switch(start_menu) {
	case MENU_NAME_MAIN:
		switch(end_menu) {
		case MENU_NAME_PLAY:
			transition_animations[0] = play_transition;
			break;
		case MENU_NAME_EXIT:
		case MENU_NAME_NONE:
		default:
			transition_animations[0] = nullptr;
		}	
		break;
	case MENU_NAME_PLAY:
		transition_animations[0] = play_menu_exit;
		break;
	case MENU_NAME_EXIT:
	case MENU_NAME_NONE:
	default:
		transition_animations[0] = nullptr;	
	}
	switch(end_menu) {
	case MENU_NAME_MAIN:
		transition_animations[1] = main_menu_enter;
		break;
	case MENU_NAME_PLAY:
		transition_animations[1] = play_menu_enter;
		break;
	case MENU_NAME_EXIT:
	case MENU_NAME_NONE:
	default:
		transition_animations[1] = nullptr;	
	}

	StopAllAnimations();
	looping_animation = nullptr;
	trans_to_menu = end_menu;
	if (transition_animations[0]) {
		PlayAnimation(transition_animations[0]);
		menu_trans_stage = MENU_TRANS_EXIT_ANIM;
	}
	else {
		setActiveMenu(end_menu, start_menu);
		if (transition_animations[1]) {
			PlayAnimation(transition_animations[1]);
			menu_trans_stage = MENU_TRANS_ENTER_ANIM;
		}
		else {
			menu_trans_stage = MENU_TRANS_NONE;
		}
	}
}

void UMenu::setActiveMenu(MENU_NAME active_menu, MENU_NAME from_menu) {
	switch(from_menu) {
	case MENU_NAME_MAIN:
		main_menu->SetVisibility(ESlateVisibility::Hidden);
		exit_button->SetVisibility(ESlateVisibility::Hidden);
		break;
	case MENU_NAME_PLAY:
		play_menu->SetVisibility(ESlateVisibility::Hidden);
		back_button->SetVisibility(ESlateVisibility::Hidden);
		break;
	case MENU_NAME_EXIT:
		exit_menu->SetVisibility(ESlateVisibility::Hidden);
		break;
	case MENU_NAME_NONE:
		break;
	}

	switch(active_menu) {
	case MENU_NAME_MAIN:
		main_menu->SetVisibility(ESlateVisibility::Visible);
		exit_button->SetVisibility(ESlateVisibility::Visible);
		break;
	case MENU_NAME_PLAY:
		play_menu->SetVisibility(ESlateVisibility::Visible);
		back_button->SetVisibility(ESlateVisibility::Visible);
		break;
	case MENU_NAME_EXIT:
		exit_menu->SetVisibility(ESlateVisibility::Visible);
		break;
	case MENU_NAME_NONE:
		break;
	}
}

void UMenu::hideAll() {
	main_menu->SetVisibility(ESlateVisibility::Hidden);
	exit_button->SetVisibility(ESlateVisibility::Hidden);
	play_menu->SetVisibility(ESlateVisibility::Hidden);
	back_button->SetVisibility(ESlateVisibility::Hidden);
	exit_menu->SetVisibility(ESlateVisibility::Hidden);
}
