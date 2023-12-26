#include "Dice_Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

// Initialization of DiceGame Class member variables

DiceGame::DiceGame() : player1Score(0), player2Score(0), player1Rolls(0), player2Rolls(0), highestScore(0), winningScore(20), computers("Computer") {}

// Definitions of all member funtions declared in the class DiceGame

// This function declares and defines the score, rolls and diceScore for a single die roll;
void DiceGame::rollSingleDice(int& score, int& rolls, const string& playerName) {

    int diceValue = (rand() % 6) + 1;
    cout << "Dice rolled: " << diceValue << endl;
    rolls++;

    if (score + diceValue <= winningScore) {
        score += diceValue;
    }
}

// This function declares and defines the score, rolls and diceScore for a double dice rolls;
void DiceGame::rollDoubleDice(int& score, int& rolls, const string& playerName) {

    int diceValue1 = (rand() % 6) + 1;
    int diceValue2 = (rand() % 6) + 1;
    int sum = diceValue1 + diceValue2;

    cout << "Dice rolled: " << diceValue1 << " and " << diceValue2 << endl;
    cout << "Sum of dice values: " << sum << endl;
    rolls++;

    if (score + sum <= winningScore) {
        score += sum;
    }
    else {
        //cout << "score cannot exceed target \n";
    }
}

// This function reads in or load the state of the game from gameSinglePlayerState.txt
void DiceGame::loadSingleGameState(string& filename) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        inputFile >> player1Name;
        inputFile >> computers;
        inputFile >> player1Score;
        inputFile >> player2Score;
        inputFile >> player1Rolls;
        inputFile >> player2Rolls;
        inputFile >> highestScore;
        inputFile >> winningScore;
        inputFile.close();
        cout << "Game state loaded successfully!" << endl;
    }
    else {
        cout << "Unable to load game state. Starting new game." << endl;
    }
}

// This function saved/write-to the state of the game in the gameSinglePlayerState.txt

void DiceGame::saveSingleGameState(string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << player1Name << "\n";
        outputFile << computers << "\n";
        outputFile << player1Score << "\n";
        outputFile << player2Score << "\n";
        outputFile << player1Rolls << "\n";
        outputFile << player2Rolls << "\n";
        outputFile << highestScore << "\n";
        outputFile << winningScore << "\n";
        outputFile.close();
        cout << "Game state saved successfully!" << endl;
    }
    else {
        cout << "Unable to save game state." << endl;
    }
}

// This function allows the continuation of previously saved single player mode part of the game, picking the computers's value and the player's value.

void DiceGame::previousSinglePlayerMode() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "Welcome Back!\n\n";

    string filename = "gameSinglePlayerState.txt";
    cout << "reading from file gameSinglePlayerState.txt\n";
    loadSingleGameState(filename);

    cout << "Enter the new winning score: ";
    cin >> winningScore;

    cout << "Entering function singlePlayerMode() \n";
    singlePlayerMode();
    cout << "leaving function singlePlayerMode() \n";

    cout << "writing to file gameSinglePlayerState.txt\n";
    saveSingleGameState(filename);
}

// This function starts a new single player game mode

void DiceGame::newSinglePlayerMode() {
    srand(static_cast<unsigned int>(time(0)));

    string filename = "gameSinglePlayerState.txt";

    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        inputFile >> highestScore;
        inputFile.close();
    }

    cout << "Highest Score: " << highestScore << endl;

    cout << "Enter your name: ";
    cin >> player1Name;

    cout << "Enter the winning score : ";
    cin >> winningScore;

    cout << "Entering function singlePlayerMode() \n";
    singlePlayerMode();
    cout << "leaving function singlePlayerMode() \n";
    
    cout << "writing to file gameSinglePlayerState.txt\n";
    saveSingleGameState(filename);
}

void DiceGame::singlePlayerMode() {
    cout << "Entering function rollSingleDice or rollDoubleDice \n";
    cout << "Enter 's' for single dice or 'd' for double dice: ";
    char choice;
    cin >> choice;
    cout << "\n";
    
    int randomStart = rand() % 2;
    bool player1Turn = (randomStart == 0);
    
    while (player1Score < winningScore && player2Score < winningScore) {
        if (player1Turn) {
            cout << player1Name << "'s turn." << endl;
            if (choice == 's') {
                cout << "Press 'r' to roll the single dice: ";
                char rollChoice;
                cin >> rollChoice;
                if (rollChoice == 'r') {
                   
                    rollSingleDice(player1Score, player1Rolls, player1Name);
                }
            }
            else if (choice == 'd') {
                cout << "Press 'r' to roll the double dice: ";
                char rollChoice;
                cin >> rollChoice;
                if (rollChoice == 'r') {
                    rollDoubleDice(player1Score, player1Rolls, player1Name);
                }
            }

            cout << player1Name << "'s Score: " << player1Score << endl;
            cout << player1Name << "'s Rolls: " << player1Rolls << endl;
            cout << "\n";

            if (player1Score >= winningScore) {
                cout << player1Name << " wins!" << endl;
                break;
            }
        }
        else {
            cout << "Computer's turn." << endl;
            if (choice == 's') {
                rollSingleDice(player2Score, player2Rolls, computers);
            }
            else if (choice == 'd') {
                rollDoubleDice(player2Score, player2Rolls, computers);
            }

            cout << computers << "'s Score: " << player2Score << endl;
            cout << computers << "'s Rolls: " << player2Rolls << endl;
            cout << "\n";

            if (player2Score >= winningScore) {
                cout << computers << " wins!" << endl;
                break;
            }
        }

        player1Turn = !player1Turn;
    }
   

    if (player1Score >= winningScore || player2Score >= winningScore) {
        string winnerName = (player1Score >= winningScore) ? player1Name : computers;
        int winnerScore = (player1Score >= winningScore) ? player1Score : player2Score;
        int winnerRolls = (player1Score >= winningScore) ? player1Rolls : player2Rolls;

        cout << "Game Over!" << endl;
        cout << "The winner is: " << winnerName << endl;
        cout << "The winner's score: " << winnerScore << endl;
        cout << "Number of rolls for the winner: " << winnerRolls << endl;

        if (winnerScore > highestScore) {
            highestScore = winnerScore;
            ofstream outputFile("highestScoreSingleGame.txt");
            if (outputFile.is_open()) {
                outputFile << highestScore;
                outputFile.close();
            }
            cout << "New highest score saved!" << endl;
        }
    }
    cout << "Leaving function rollSingleDice or rollDoubleDice \n";
}

// This function write-to gameDoublePlayerState.txt to save the game state

void DiceGame::saveDoublePlayerGameState(string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << player1Name << "\n";
        outputFile << player2Name << "\n";
        outputFile << player1Score << "\n";
        outputFile << player2Score << "\n";
        outputFile << player1Rolls << "\n";
        outputFile << player2Rolls << "\n";
        outputFile << highestScore << "\n";
        outputFile << winningScore << "\n";
        outputFile.close();
        cout << "Game state saved successfully!" << endl;
    }
    else {
        cout << "Unable to save game state." << endl;
    }
}

// This function reads in or load the state of the game from gameDoublePlayerState.txt

void DiceGame::loadDoublePlayerGameState(string& filename) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        inputFile >> player1Name;
        inputFile >> player2Name;
        inputFile >> player1Score;
        inputFile >> player2Score;
        inputFile >> player1Rolls;
        inputFile >> player2Rolls;
        inputFile >> highestScore;
        inputFile >> winningScore;
        inputFile.close();
        cout << "Game state loaded successfully!" << endl;
    }
    else {
        cout << "Unable to load game state. Starting new game." << endl;
    }
}

// This function starts a new double player mode game
void DiceGame::newTwoPlayerMode() {
    srand(static_cast<unsigned int>(time(0)));

    ifstream inputFile("game_state.txt");
    if (inputFile.is_open()) {
        inputFile >> highestScore;
        inputFile.close();
    }

    cout << "Highest Score: " << highestScore << endl;

    cout << "Enter Player 1's name: ";
    cin >> player1Name;
    cout << "Enter Player 2's name: ";
    cin >> player2Name;
    cout << "Enter the winning score: ";
    cin >> winningScore;

    cout << "Entering the function twoPlayerMode () \n";
    twoPlayerMode();
    cout << "Leaving the function twoPlayerMode() \n";

    string filename = "gameDoublePlayerState.txt";
    cout << "writing to file gameDoublePlayerState.txt\n";
    saveDoublePlayerGameState(filename);  // Save game state at the end
}

// This function allows the continuation of previously saved double player mode part of the game, picking the player1 and the player2 details.

void DiceGame::previousTwoPlayerMode() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "Welcome back!\n\n";

    string filename = "gameDoublePlayerState.txt";

    cout << "reading from file gameDoublePlayerState.txt\n";
    loadDoublePlayerGameState(filename);                             // Calling the function that Load the game state from the text file

    cout << "New winning score must exceed previous winning score. Enter the winning score: ";
    cin >> winningScore;

    cout << "Entering the function twoPlayerMode() \n";
    twoPlayerMode();                                                 // Calling the two player mode function.
    cout << "Leaving the function twoPlayerMode() \n";

    cout << "writing to file gameDoublePlayerState.txt\n";
    saveDoublePlayerGameState(filename);                             // Calliing the function that Save game state at the end
}

// This function get hold of dice choice, allows the each of the players

void DiceGame::twoPlayerMode() {
    cout << "Entering function rollSingleDice() or rollDoubleDice() \n";
    cout << "Enter 's' for single dice or 'd' for double dice: ";
    char choice;
    cin >> choice;
    cout << "\n";

    int randomStart = rand() % 2;
    bool player1Turn = (randomStart == 0);  // Allows either of the players to start the game randomly

    while (player1Score < winningScore && player2Score < winningScore) {
        if (player1Turn) {
            cout << player1Name << "'s turn." << endl;
            if (choice == 's') {
                cout << "Press 'r' to roll the single dice: ";
                char rollChoice;
                cin >> rollChoice;
                if (rollChoice == 'r') {
                    rollSingleDice(player1Score, player1Rolls, player1Name);  // Calling the singlde dice function
                }
            }
            else if (choice == 'd') {
                cout << "Press 'r' to roll the double dice: ";
                char rollChoice;
                cin >> rollChoice;
                if (rollChoice == 'r') {
                    rollDoubleDice(player1Score, player1Rolls, player1Name);  // Calling the double dice function
                }
            }

            cout << player1Name << "'s Score: " << player1Score << endl;
            cout << player1Name << "'s Rolls: " << player1Rolls << endl;
            cout << "\n";

            if (player1Score >= winningScore) {
                cout << player1Name << " wins!" << endl;
                break;
            }
        }
        else {
            cout << player2Name << "'s turn." << endl;
            if (choice == 's') {
                cout << "Press 'r' to roll the single dice: ";
                char rollChoice;
                cin >> rollChoice;
                if (rollChoice == 'r') {
                    rollSingleDice(player2Score, player2Rolls, player2Name);  // Calling the singlde dice function
                }
            }
            else if (choice == 'd') {
                cout << "Press 'r' to roll the double dice: ";
                char rollChoice;
                cin >> rollChoice;
                if (rollChoice == 'r') {
                    rollDoubleDice(player2Score, player2Rolls, player2Name);  // Calling the double dice function
                }
            }

            cout << player2Name << "'s Score: " << player2Score << endl;
            cout << player2Name << "'s Rolls: " << player2Rolls << endl;
            cout << "\n";

            if (player2Score >= winningScore) {
                cout << player2Name << " wins!" << endl;
            }
        }

        player1Turn = !player1Turn;
    }

    // This statement prints the winner of the game details
    if (player1Score >= winningScore || player2Score >= winningScore) {
        string winnerName = (player1Score >= winningScore) ? player1Name : player2Name;
        int winnerScore = (player1Score >= winningScore) ? player1Score : player2Score;
        int winnerRolls = (player1Score >= winningScore) ? player1Rolls : player2Rolls;

        cout << "Game Over!" << endl;
        cout << "The winner is: " << winnerName << endl;
        cout << "The winner's score: " << winnerScore << endl;
        cout << "Number of rolls for the winner: " << winnerRolls << endl;

        if (winnerScore > highestScore) {
            highestScore = winnerScore;
            ofstream outputFile("gameDoublePlayerState.txt");
            if (outputFile.is_open()) {
                outputFile << highestScore;
                outputFile.close();
            }
            cout << "New highest score saved!" << endl;
        }
    }
    cout << "Leaving the function rollSingleDice() or rollDoubleDice() \n";
}

// This function starts the game and allows to choose either a single or a double player mode. It also allows to to select if you want to start a new game or continue with previous one

void DiceGame::playGame() {

    cout << "Select Mode: \nPress '1' for Single Player Mode OR Press '2' for  Two Players Mode: ";
    int choice;
    cin >> choice;
    cout << "\n";
    if (choice == 1) {
        cout << "Single Player Mode Selected\n";

        cout << "Entering newSinglePlayerMode() or previousSinglePlayerMode() \n";
        cout << "Press '1' to start a New Game OR Press '2' to Continue Previous Game: ";
        int options;
        cin >> options;
        cout << "\n";
        if (options == 1) {
            newSinglePlayerMode();  // Get called if new game is selected
        }
        else if (options == 2) {
            previousSinglePlayerMode();  // Get called if previous game is selected
        }
        else {
            cout << "Invalid Option, try again";
        }
    }
    else if (choice == 2) {
        cout << "Double Player Mode Selected!\n";
        
        cout << "Enterig newTwoPlayerMode() or previousTwoPlayerMode() \n";
        cout << "Press '1' to Start a New Game or Press '2' to  Continue Previous Game: ";
        int options;
        cin >> options;
        cout << "\n";
        if (options == 1) {
            newTwoPlayerMode();  // Get called if new game is selected
        }
        else if (options == 2) {
            previousTwoPlayerMode();  // Get called if previous game is selected
        }
        else {
            cout << "Invalid Option, try again";
        }
    }
    else {
        cout << "Invalid mode selected, restart the game";
    }
}

int main() {
    DiceGame game;    // Created an instance of class DiceGame;
    cout << "WELCOME TO THE DICE GAME \n\n";
    cout << "Entering the function playGame() \n";
    game.playGame();  // Game play started

    return 0;
}