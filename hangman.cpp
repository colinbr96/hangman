// HangMan Game in C++
//
// hangman.cpp
// @author colinrb@uci.edu


////////////////////////////////// INCLUSIONS /////////////////////////////////

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <random>


////////////////////////////////// CONSTANTS //////////////////////////////////


// Graphics
const std::string TITLE    = " _   _                  ___  ___ \n| | | |                 |  \\/  | \n| |_| | __ _ _ __   __ _| .  . | __ _ _ __ \n|  _  |/ _` | '_ \\ / _` | |\\/| |/ _` | '_ \\ \n| | | | (_| | | | | (_| | |  | | (_| | | | | \n\\_| |_/\\__,_|_| |_|\\__, \\_|  |_/\\__,_|_| |_| \n                    __/ | \n      _______      |___/       version Beta \n      |     | \n      |     O \n      |    /|\\ \n      |    / \\         by Colin Brown \n  ____|________           colinrb@uci.edu \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_0  = "      _______ \n      |     | \n      | \n      | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_1  = "      _______ \n      |     | \n      |     O \n      | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_2  = "      _______ \n      |     | \n      |     O \n      |     | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_3  = "      _______ \n      |     | \n      |     O \n      |    /| \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_4  = "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_5  = "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      |    / \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_6  = "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      |    / \\ \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";

// Text
const std::string COMMANDS = "Commands: \n-------------------- \nS     Start new game \nQ               Quit";

// Directories
const std::string VOCAB_FOLDER = "vocab/";


/////////////////////////////////// HELPERS ///////////////////////////////////

/*
    @return: Parameter string converted to uppercase
*/
void toUppercase(std::string& s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}


/*
    @return: Parameter string converted to lowercase
*/
void toLowercase(std::string& s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}


/*
    Prints the command prompt.
    @return: User input
*/
std::string prompt() {
    std::cout << "\n>> ";
    std::string userInput;
    getline(std::cin, userInput);
    std::cout << std::endl;
    return userInput;
}


/*
    @return: List of lines in the given file
*/
std::vector<std::string> readLines(std::string filename) {
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> list;

    while(getline(infile, line)) {
        list.push_back(line);
    }

    return list;
}


/*
    @return: Single random element of given vector
*/
template<typename T>
T pickRandomElement(std::vector<T> v) {
   std::random_device seed;
   std::mt19937 engine(seed());
   std::uniform_int_distribution<int> choose(0, v.size()-1);
   return v[choose(engine)];
}


////////////////////////////////// FUNCTIONS //////////////////////////////////

/*
    Prompts the user for which vocabulary list to use.
    @return: List of vocab words
*/
std::vector<std::string> promptVocab() {
    std::cout << "What vocabulary list do you want to use?" << std::endl;
    std::cout << "    1. Food" << std::endl;

    while(true) {
        std::string response = prompt();
        toLowercase(response);

        if(response == "1" || response == "food")
            return readLines(VOCAB_FOLDER + "food.txt");
        else
            std::cout << "The vocabulary list \"" << response << "\" is not recognized." << std::endl;
    }
}


/*
    Simulates a game of Hangman.
    @return: When game is finished
*/
void play() {
    std::vector<std::string> vocabList = promptVocab();
    std::string word = pickRandomElement(vocabList);

    std::cout << "Your word is " << word << std::endl;

    std::cout << "Game Over." << std::endl;
    return;
}


/* 
   Prints the title screen graphic.
   Prompts for commands endlessly until a valid one is inputted.

   @return 0: User exited the game
   @return 1: User started a new game
*/
int mainMenu() {
    std::cout << "\n" << TITLE << "\n\n" << COMMANDS << "\n";

    while(true) {
        std::string command = prompt();
        toUppercase(command);

        if(command == "S")
            return 1;
        else if(command == "Q")
            return 0;
        else
            std::cout << "The command \"" << command << "\" is not recognized." << std::endl;
    }
}


///////////////////////////////////// MAIN ////////////////////////////////////

int main(int argc, char const *argv[])
{
    while(true) {
        switch(mainMenu()) {
            case 0:
                return 0;
            case 1:
                play();
        }
    }
    return 0;
}