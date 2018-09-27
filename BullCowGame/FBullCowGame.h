/*The game logic (no view code or direct user interaction)
the game is a simple guess game the word game based on mastermind
*/

#pragma once
#include <string>
// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// ***DO NOT USE "USING NAMESPACE" IN HEADER FILES***

//all values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};

class FBullCowGame
{
public:

	FBullCowGame(); //constructor

	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const; 

	void setHiddenWordLength(FString);

	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

	


private:


	// see constructor fpr initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	// Helper function
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
