#pragma once

#include "Interfaces/IHttpRequest.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BUIUploader.generated.h"

UENUM()
enum MULTIPLAYER_ROLE {
	ROLE_SERVER,
	ROLE_CLIENT
};

UCLASS()
class WORDUPAND_API UBUIUploader : public UObject {
	GENERATED_BODY()

public:
	void setGameInstance(class UWordUpGameInstance* g);
	void pairServerSend(const FString& message);
	
	void onPairServerResponse(
		FHttpRequestPtr request,
		FHttpResponsePtr response,
		bool request_success
	);
	void pairMe(
		class UWordUpGameInstance* instance,
		void(* callback)(MULTIPLAYER_ROLE role, FString other_ip_address)
	);
	
	
protected:

private:
	UWordUpGameInstance* game_instance = nullptr;
	
};
