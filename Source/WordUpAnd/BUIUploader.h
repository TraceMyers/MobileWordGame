#pragma once

#include "Interfaces/IHttpRequest.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BUIUploader.generated.h"

UCLASS()
class WORDUPAND_API UBUIUploader : public UObject {
	GENERATED_BODY()

public:
	void pairServerSend();
	void onPairServerResponse(
		FHttpRequestPtr request,
		FHttpResponsePtr response,
		bool request_success
	);
	
protected:

private:
};
