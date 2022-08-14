#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WordUpGameInstance.generated.h"

UCLASS()
class WORDUPAND_API UWordUpGameInstance : public UGameInstance {
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void showMenu();
	
	UWordUpGameInstance(const FObjectInitializer& object_initializer);
	virtual void Init() override;
	void quit() const;
	
protected:

private:
	UPROPERTY()
	class UMenu* menu = nullptr;
	UPROPERTY()
	class UBUIUploader* pair_fairy;

	TSubclassOf<class UUserWidget> BP_Menu;
};
