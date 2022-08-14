#pragma once

#include "CoreMinimal.h"
#include "Words.h"

UENUM()
enum PLAYER {P1, P2};

class WORDUPAND_API ServerData {
public:
	ServerData();
	~ServerData();
	void initSession();
	
protected:

private:
	static constexpr int P_HAND_MAX = 12;
	static constexpr int CENTER_MAX = 6;
	static constexpr int CBLOCK_MAX = 6;
	static constexpr int VOWEL_POOL_MAX = 42;
	static constexpr int CONSONANT_POOL_MAX = 53;
	
	char p1_hand[P_HAND_MAX + 1];
	char p2_hand[P_HAND_MAX + 1];
	char center[CENTER_MAX + 1];
	char cblock[CBLOCK_MAX + 1];

	char vowel_pool[VOWEL_POOL_MAX + 1];
	char consonant_pool[CONSONANT_POOL_MAX + 1];

	int p1_vowel_ct;
	int p1_letter_ct;
	int p2_vowel_ct;
	int p2_letter_ct;

	Words words;

	char drawVowel();
	char drawConsonant();
	void redraw(PLAYER p);
	void shuffleHand(PLAYER p);
	
};
