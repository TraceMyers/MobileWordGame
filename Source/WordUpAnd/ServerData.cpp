#include "ServerData.h"
#include "Tools.h"
#include "Words.h"

ServerData::ServerData() {
	
}

ServerData::~ServerData() {
	
}

void ServerData::initSession() {
	// no Q, X, Z in draw pool
	strcpy(
		vowel_pool,
		"AAAAAAAAAEEEEEEEEEEEEIIIIIIIIIOOOOOOOOUUUU"
	);
	strcpy(
		consonant_pool,
		"BBCCDDDDFFGGGHHJKLLLLMMNNNNNNPPRRRRRRSSSSTTTTTTVVWWYY"
	);
	strcpy(
		cblock,
		"******"
	);
	const int starting_word_i = FMath::RandRange(0, Words::WORDS_3_CT - 1);
	strcpy(center, "******");
	// memcpy(center, words.words_3[starting_word_i], 3 * sizeof(char));

	p1_letter_ct = P_HAND_MAX;
	p2_letter_ct = P_HAND_MAX;
	int p1_vowel_ctr = FMath::RandRange(4, 6);
	p1_vowel_ct = p1_vowel_ctr;
	int p2_vowel_ctr = FMath::RandRange(4, 6);
	p2_vowel_ct = p2_vowel_ctr;
	// alternate draws so that no player unfairly draws all of the most common letters
	for (int i = 0; i < P_HAND_MAX; i++) {
		// alternate who draws first every draw turn, otherwise p1 accrues draw advantage
		//		(p1 p2), (p2 p1), (p1 p2), ...
		// vs	(p1 p2), (p1 p2), (p1 p2)
		if (i % 2 == 0) {
			if (p1_vowel_ctr > 0) {
				p1_vowel_ctr--;
				p1_hand[i] = drawVowel();	
			}
			else {
				p1_hand[i] = drawConsonant();	
			}
			if (p2_vowel_ctr > 0) {
				p2_vowel_ctr--;	
				p2_hand[i] = drawVowel();	
			}
			else {
				p2_hand[i] = drawConsonant();	
			}
		}
		else {
			if (p2_vowel_ctr > 0) {
				p2_vowel_ctr--;
				p2_hand[i] = drawVowel();	
			}
			else {
				p2_hand[i] = drawConsonant();	
			}
			if (p1_vowel_ctr > 0) {
				p1_vowel_ctr--;	
				p1_hand[i] = drawVowel();	
			}
			else {
				p1_hand[i] = drawConsonant();	
			}
		}
	}
	p1_hand[P_HAND_MAX] = '\0';
	p2_hand[P_HAND_MAX] = '\0';
	shuffleHand(P1);
	shuffleHand(P2);
	
	// print("%hs", p1_hand);
	// print("%hs", p2_hand);
	// print("%hs", center);
	// print("%hs", cblock);
	
	// print("draw pool len: %llu", strlen(draw_pool));
	// print("%hs", words.words_3[6]);
	// print("%hs", draw_pool);
	// print("%hs", center);
}

char ServerData::drawVowel() {
	int vowel_i = FMath::RandRange(0, VOWEL_POOL_MAX - 1);
	char vowel = vowel_pool[vowel_i];
	if (vowel == '*') {
		int search_right = vowel_i + 1;
		int search_left = vowel_i - 1;
		while (search_right != search_left && search_right != search_left + 1) {
			if (search_right >= VOWEL_POOL_MAX) {
				search_right = 0;
			}
			vowel = vowel_pool[search_right];
			if (vowel != '*') {
				vowel_i = search_right;	
				break;
			}
			if (search_left <= 0) {
				search_left = VOWEL_POOL_MAX - 1;
			}
			vowel = vowel_pool[search_left];
			if (vowel != '*') {
				vowel_i = search_left;
				break;
			}
			search_right++;
			search_left--;
		}
	}
	if (vowel == '*') {
		exit(EXIT_FAILURE);
	}
	vowel_pool[vowel_i] = '*';
	return vowel;
}

char ServerData::drawConsonant() {
	int consonant_i = FMath::RandRange(0, CONSONANT_POOL_MAX - 1);
	char consonant = consonant_pool[consonant_i];
	if (consonant == '*') {
		int search_right = consonant_i + 1;
		int search_left = consonant_i - 1;
		while (search_right != search_left && search_right != search_left + 1) {
			if (search_right >= CONSONANT_POOL_MAX) {
				search_right = 0;
			}
			consonant = consonant_pool[search_right];
			if (consonant != '*') {
				consonant_i = search_right;	
				break;
			}
			if (search_left <= 0) {
				search_left = CONSONANT_POOL_MAX - 1;
			}
			consonant = consonant_pool[search_left];
			if (consonant != '*') {
				consonant_i = search_left;
				break;
			}
			search_right++;
			search_left--;
		}
	}
	if (consonant == '*') {
		exit(EXIT_FAILURE);
	}
	consonant_pool[consonant_i] = '*';
	return consonant;
}

void ServerData::redraw(PLAYER p) {
	int vowel_ct;
	int letter_ct;
	char* hand;
	if (p == P1) {
		vowel_ct = p1_vowel_ct;
		letter_ct = p1_letter_ct;
		hand = p1_hand;
	}
	else {
		vowel_ct = p2_vowel_ct;
		letter_ct = p2_letter_ct;
		hand = p2_hand;
	}
	int vowel_ctr = vowel_ct;
	for (int i = 0; i < letter_ct; i++) {
		if (vowel_ctr > 0) {
			vowel_ctr--;
			hand[i] = drawVowel();	
		}
		else {
			hand[i] = drawConsonant();	
		}
	}
	for (int i = letter_ct; i < P_HAND_MAX; ++i) {
		hand[i] = '*';
	}
}

// Assumes hand has trailing '*' after last letter to end, as in "RRQAPS******", as formatted in initSession() and
// redraw()
void ServerData::shuffleHand(PLAYER p) {
	int letter_ct_m1;
	char* hand;
	if (p == P1) {
		letter_ct_m1 = p1_letter_ct - 1;
		hand = p1_hand;
	}
	else {
		letter_ct_m1 = p2_letter_ct - 1;
		hand = p2_hand;
	}
	for (int i = 0; i < letter_ct_m1; ++i) {
		const int swap_index = FMath::RandRange(i + 1, letter_ct_m1);
		const char temp = hand[i];
		hand[i] = hand[swap_index];
		hand[swap_index] = temp;
	}
}
