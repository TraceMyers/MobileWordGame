#include "Words.h"
#include "Tools.h"

Words::Words() {
	FString path = "D:\\projects\\Unreal Projects\\WordUpAnd\\Content\\Text\\wordlist_caps_3.txt";
	bool load_success = FFileHelper::LoadANSITextFileToStrings(
		*path,	
		&IFileManager::Get(),
		len_3_words	
	);
	if (!load_success) {
		print("could not load len 3 words");
	}
	path = "D:\\projects\\Unreal Projects\\WordUpAnd\\Content\\Text\\wordlist_caps_4.txt";
	load_success = FFileHelper::LoadANSITextFileToStrings(
		*path,	
		&IFileManager::Get(),
		len_4_words	
	);
	if (!load_success) {
		print("could not load len 4 words");
	}
	path = "D:\\projects\\Unreal Projects\\WordUpAnd\\Content\\Text\\wordlist_caps_5.txt";
	load_success = FFileHelper::LoadANSITextFileToStrings(
		*path,	
		&IFileManager::Get(),
		len_5_words	
	);
	if (!load_success) {
		print("could not load len 5 words");
	}
	path = "D:\\projects\\Unreal Projects\\WordUpAnd\\Content\\Text\\wordlist_caps_6.txt";
	load_success = FFileHelper::LoadANSITextFileToStrings(
		*path,	
		&IFileManager::Get(),
		len_6_words	
	);
	if (!load_success) {
		print("could not load len 6 words");
	}
}
