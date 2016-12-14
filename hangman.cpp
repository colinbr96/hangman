// HangMan Game in C++
//
// hangman.cpp
// @author colinrb@uci.edu


///////////////////////////////// DEFINITIONS /////////////////////////////////

#define TITLE    " _   _                  ___  ___ \n| | | |                 |  \\/  | \n| |_| | __ _ _ __   __ _| .  . | __ _ _ __ \n|  _  |/ _` | '_ \\ / _` | |\\/| |/ _` | '_ \\ \n| | | | (_| | | | | (_| | |  | | (_| | | | | \n\\_| |_/\\__,_|_| |_|\\__, \\_|  |_/\\__,_|_| |_| \n                    __/ | \n      _______      |___/       version Beta \n      |     | \n      |     O \n      |    /|\\ \n      |    / \\         by Colin Brown \n  ____|________           colinrb@uci.edu \n /    |       /| \n/____________/ / \n|____________|/"
#define COMMANDS "Commands: \n-------------------- \nS     Start new game \nQ               Quit"
#define STATE_0  "      _______ \n      |     | \n      | \n      | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/"
#define STATE_1  "      _______ \n      |     | \n      |     O \n      | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/"
#define STATE_2  "      _______ \n      |     | \n      |     O \n      |     | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/"
#define STATE_3  "      _______ \n      |     | \n      |     O \n      |    /| \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/"
#define STATE_4  "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/"
#define STATE_5  "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      |    / \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/"
#define STATE_6  "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      |    / \\ \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/"


////////////////////////////////// INCLUSIONS /////////////////////////////////

#include <iostream>
#include <algorithm>


////////////////////////////////// FUNCTIONS //////////////////////////////////

/*
    Prints the command prompt.
    @return std::string: User input
*/
std::string prompt() {
    std::cout << "\n>> ";
    std::string userInput;
    getline(std::cin, userInput);
    std::cout << std::endl;
    return userInput;
}


/*
    Simulates a game of Hangman.
    @return void: When game is finished
*/
void play() {
    std::cout << "Game Over." << std::endl;
    return;
}


/* 
   Prints the title screen graphic.
   Prompts for commands endlessly until a valid one is inputted.

   @return 0: User exited the game
   @return 1: User started a new game
*/
int main_menu() {
    std::cout << "\n" << TITLE << "\n\n" << COMMANDS << "\n";

    while(true) {
        std::string command = prompt();
        transform(command.begin(), command.end(), command.begin(), ::toupper);

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
        switch(main_menu()) {
            case 0:
                return 0;
            case 1:
                play();
        }
    }
    return 0;
}