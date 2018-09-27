#pragma once

#include "FBullCowGame.h"
#include <map>

#define Tmap std::map
using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); } //default constructor

void FBullCowGame::Reset()
{

	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

int32 FBullCowGame::getCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bIsGameWon; }

void FBullCowGame::setHiddenWordLength(FString length)
{
	Tmap<FString, FString> WordLengthToHiddenWord{ {"3","ant"},{"4","hero"},{ "5","watch" },{ "6","condom" } };
	MyHiddenWord = WordLengthToHiddenWord[length];

	return;
}

int32 FBullCowGame::getMaxTries() const 
{
	Tmap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 12}, {6, 16} }; 
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
	
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_LowerCase;
	}
	else if (Guess.length() != getHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}



// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString GuessWord)
{
	MyCurrentTry++;
	FBullCowCount bullCowCount;

	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess  
	//loop through all letter in the hidden word 
	for (int32 i = 0; i < WordLength; i++) {
		for (int32 j = 0; j < WordLength; j++) {
		//compare letters against the guess
			if (MyHiddenWord[i] == GuessWord[j]) {
				if (i == j)
					bullCowCount.Bulls++;
				else
					bullCowCount.Cows++;
			}

		}

	}
	if (bullCowCount.Bulls == WordLength) { bIsGameWon = true; }
	else
		bIsGameWon = false;

	return bullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	Tmap<char, bool> LetterSeen; 

	// loop through all the letters of the word
		// if the letter is in the map return false(we do NOT have an isogram)
		//else add the letter into the map as seen 

	//for all letters of the word
	for (auto Letter : Word){

		Letter = tolower(Letter); //handle mixed case

		if (LetterSeen[Letter]) { 
			return false; 
		} else {
			LetterSeen[Letter] = true;
		}
	}


	return true;
}
bool FBullCowGame::IsLowercase(FString word) const
{
	if (word.length() <= 1) return true;

	for (auto Letter : word) {

		if (!islower(Letter)) return false; 
	}
	return true;

}