
/*
	This is the executable console which makes to use of the BullCow class
	This acts as the view in a MVC pattern, and is responsible for all user interaction.
	For game logic, see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using Ftext = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void getInfoFromPlayer();
void PlayGame();
Ftext GetValidGuess(); 
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame; //instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{
	bool bplayAgain = false;
	do {
		PrintIntro();
		getInfoFromPlayer();
		PlayGame();
		bplayAgain = AskToPlayAgain();

	} 
	while (bplayAgain);
		
	return 0; // exit the game
} 

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game\n" << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |--\-- |              |---,,-|  * " << std::endl;
	std::cout << "    ^     ^              ^      ^ " << std::endl;
	//std::cout << "Can you guess the " << BCGame.getHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	
	
	return;
}
void getInfoFromPlayer()
{
	FString length = "";
	std::cout << "Can you choose length of the hidden isogram word(from 3 to 6 letters): "<<std::endl;
	std::getline(std::cin, length);
	BCGame.setHiddenWordLength(length);
	return;
}

void PrintGameSummary()
{
	if (BCGame.isGameWon())
		std::cout << "\n ********   YOU WIN!   ********\n\n";
	else
		std::cout << "\n ------- GAMEOVER motherfucker! ------- \n\n";
}

// plays a single game to completion
void PlayGame()
{
	
	BCGame.Reset();
	int32 MaxTries = BCGame.getMaxTries();

	// loop asking for  guesses while the game is NOT WON and there are still tries remaining

	while(!BCGame.isGameWon() && BCGame.getCurrentTry() <= MaxTries){ 
		
		Ftext Guess = GetValidGuess();

		// submit valid guess to the  game, and receive counts
		FBullCowCount BullCowCount =  BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls ;
		std::cout << " | Cows = " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();
	return;
}
// loop continually until the user gives a valid guess
Ftext GetValidGuess()
{
	Ftext Guess = "";
	EGuessStatus Status = EGuessStatus::invalid_status;

	do {	
		// get a guess from the player
		int32 CurrentTry = BCGame.getCurrentTry();
		std::cout << std::endl;
		std::cout << "try " << CurrentTry << " of " << BCGame.getMaxTries();
		std::cout << ". Enter your guess: ";
		getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "please enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
		

	} while (Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word?(y/n) ";
	Ftext Response = "";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
