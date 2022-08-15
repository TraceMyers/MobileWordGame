#include "BUIUploader.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "WordUpGameInstance.h"
#include "Tools.h"

void UBUIUploader::pairMe(
	UWordUpGameInstance* instance,
	void(* callback)(MULTIPLAYER_ROLE role, FString other_ip_address)
) {
	
}

void UBUIUploader::setGameInstance(UWordUpGameInstance* g) {
	game_instance = g;
}

void UBUIUploader::pairServerSend(const FString& msg) {
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> http_request = FHttpModule::Get().CreateRequest();
	http_request->SetVerb("POST");
	http_request->SetHeader("Content-Type", "application/json");
	http_request->SetURL(*FString::Printf(TEXT("%hs"), "http://154.12.226.174:80"));
	http_request->SetContentAsString(msg);
	http_request->OnProcessRequestComplete().BindUObject(this, &UBUIUploader::onPairServerResponse);
	http_request->ProcessRequest();
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> end_request = FHttpModule::Get().CreateRequest();
	// attempting to stop unreal engine from keeping some http output stream set to the pair server
	// was sending random get requests during editor use; I don't know if setting it to localhost is
	// a good idea.
	end_request->SetURL(*FString::Printf(TEXT("%hs"), "http://localhost:17777"));
	end_request->ProcessRequest();
}

void UBUIUploader::onPairServerResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool success) {
	const FString response_string = response->GetContentAsString();
	if (game_instance) {
		game_instance->clientMessage(response_string);
	}
}