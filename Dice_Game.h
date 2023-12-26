#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

// Created the class DiceGame
class DiceGame {
private:
    // Declaring the member variables
    string player1Name;
    string player2Name;
    string computers;  // This variable declares the name assigned to the computer for the single player mode.
    int player1Score;
    int player2Score;
    int player1Rolls;
    int player2Rolls;
    int highestScore;
    int winningScore;

public:
    // Created a constructor and uses it to initialise the member variables
    DiceGame();

    // Declaring the other member functions of the game
    void rollSingleDice(int& score, int& rolls, const string& playerName);
    void rollDoubleDice(int& score, int& rolls, const string& playerName);
    void loadSingleGameState(string& filename);
    void saveSingleGameState(string& filename);
    void previousSinglePlayerMode();
    void newSinglePlayerMode();
    void singlePlayerMode();
    void saveDoublePlayerGameState(string& filename);
    void loadDoublePlayerGameState(string& filename);
    void previousTwoPlayerMode();
    void newTwoPlayerMode();
    void twoPlayerMode();
    void playGame();
};