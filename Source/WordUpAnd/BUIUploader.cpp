#include "BUIUploader.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "Tools.h"

void UBUIUploader::pairServerSend() {
	const FString request_content("register,dent,*");
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> http_request = FHttpModule::Get().CreateRequest();
	http_request->SetVerb("POST");
	http_request->SetHeader("Content-Type", "application/json");
	http_request->SetURL(*FString::Printf(TEXT("%hs"), "http://154.12.226.174:80"));
	http_request->SetContentAsString(request_content);
	http_request->OnProcessRequestComplete().BindUObject(this, &UBUIUploader::onPairServerResponse);
	http_request->ProcessRequest();
}

void UBUIUploader::onPairServerResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool success) {
	const FString response_string = response->GetContentAsString();
	if (success && response->GetContentType() == "") {
		if (response->GetContentType() == "text/html") {
			print("success!, response: %s", *response_string);
		}
		else {
			print("not text");
		}
	}
	else {
		print("failure :(, response: %s", *response_string);
	}
}