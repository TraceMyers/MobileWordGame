#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

UENUM()
enum MENU_NAME {
	MENU_NAME_MAIN,
	MENU_NAME_PLAY,
	MENU_NAME_EXIT,
	MENU_NAME_NONE
};

UENUM()
enum MENU_TRANSITION_STAGE {
	MENU_TRANS_EXIT_ANIM,
	MENU_TRANS_ENTER_ANIM,
	MENU_TRANS_NONE
};

UCLASS()
class WORDUPAND_API UMenu : public UUserWidget {
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void setGameInstance(class UWordUpGameInstance* game_instance);
	void begin();
	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;
	void show(APlayerController* player_controller);
	void hide(APlayerController* player_controller);

protected:

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* play_button;
	UPROPERTY(meta=(BindWidget))
	UButton* settings_button;
	UPROPERTY(meta=(BindWidget))
	UButton* how_to_button;
	UPROPERTY(meta=(BindWidget))
	UButton* exit_button;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* play_transition;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* settings_transition;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* how_to_transition;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* play_hover;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* settings_hover;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* how_to_hover;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* exit_hover;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* exit_unhover;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* main_menu_enter;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* play_menu_enter;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* play_menu_exit;
	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* menu_switch;
	UPROPERTY(meta=(BindWidget))
	UButton* exit_yes_button;
	UPROPERTY(meta=(BindWidget))
	UButton* exit_no_button;
	UPROPERTY(meta=(BindWidget))
	UButton* back_button;
	UPROPERTY(meta=(BindWidget))
	class USizeBox* main_menu;
	UPROPERTY(meta=(BindWidget))
	class USizeBox* play_menu;
	UPROPERTY(meta=(BindWidget))
	class UOverlay* exit_menu;

	UFUNCTION()
	void onPlayButtonSelected();
	UFUNCTION()
	void onSettingsButtonSelected();
	UFUNCTION()
	void onHowToButtonSelected();
	UFUNCTION()
	void onExitButtonSelected();
	UFUNCTION()
	void onPlayButtonHovered();
	UFUNCTION()
	void onSettingsButtonHovered();
	UFUNCTION()
	void onHowToButtonHovered();
	UFUNCTION()
	void onExitButtonHovered();
	UFUNCTION()
	void onPlayButtonUnhovered();
	UFUNCTION()
	void onSettingsButtonUnhovered();
	UFUNCTION()
	void onHowToButtonUnhovered();
	UFUNCTION()
	void onExitButtonUnhovered();
	UFUNCTION()
	void onExitYesButtonSelected();
	UFUNCTION()
	void onExitNoButtonSelected();
	UFUNCTION()
	void onBackButtonSelected();

	void transitionMenu(MENU_NAME end_menu, MENU_NAME start_menu=MENU_NAME_NONE);
	void setActiveMenu(MENU_NAME active_menu, MENU_NAME from_menu=MENU_NAME_NONE);
	void hideAll() ;

	UWordUpGameInstance* game_instance;
	UWidgetAnimation* looping_animation = nullptr;
	UWidgetAnimation* transition_animations[2] {nullptr, nullptr};
	MENU_TRANSITION_STAGE menu_trans_stage;
	MENU_NAME trans_to_menu;
	MENU_NAME current_menu;
};
