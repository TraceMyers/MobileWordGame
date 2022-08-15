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
	UFUNCTION()
	void clientMessage(const FString& message);
	
	UFUNCTION(Exec)
	void pair_server_send(const FString& message) const;
	UFUNCTION(Exec)
	void free_roam(int setting) const;
	UFUNCTION(Exec)
	void host();
	UFUNCTION(Exec)
	void join(const FString& address);
	
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
