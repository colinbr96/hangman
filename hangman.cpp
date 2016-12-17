// HangMan Game in C++
//
// hangman.cpp
// @author colinrb@uci.edu


////////////////////////////////// INCLUSIONS /////////////////////////////////

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <set>
#include <random>


////////////////////////////////// CONSTANTS //////////////////////////////////

// Ascii Art
const std::string TITLE   = " _   _                  ___  ___ \n| | | |                 |  \\/  | \n| |_| | __ _ _ __   __ _| .  . | __ _ _ __ \n|  _  |/ _` | '_ \\ / _` | |\\/| |/ _` | '_ \\ \n| | | | (_| | | | | (_| | |  | | (_| | | | | \n\\_| |_/\\__,_|_| |_|\\__, \\_|  |_/\\__,_|_| |_| \n                    __/ | \n      _______      |___/       version Beta \n      |     | \n      |     O \n      |    /|\\ \n      |    / \\         by Colin Brown \n  ____|________           colinrb@uci.edu \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_0 = "\n\n\n\n\n  _____________\n /            /|\n/____________/ /\n|____________|/";
const std::string STATE_1 = "      _______ \n      |     | \n      | \n      | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_2 = "      _______ \n      |     | \n      |     O \n      | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_3 = "      _______ \n      |     | \n      |     O \n      |     | \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_4 = "      _______ \n      |     | \n      |     O \n      |    /| \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_5 = "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      | \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_6 = "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      |    / \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE_7 = "      _______ \n      |     | \n      |     O \n      |    /|\\ \n      |    / \\ \n  ____|________ \n /    |       /| \n/____________/ / \n|____________|/";
const std::string STATE[8] = {STATE_0, STATE_1, STATE_2, STATE_3, STATE_4, STATE_5, STATE_6, STATE_7};
const std::string YOU_WON   = "__   __            _    _             _ \n\\ \\ / /           | |  | |           | | \n \\ V /___  _   _  | |  | | ___  _ __ | | \n  \\ // _ \\| | | | | |/\\| |/ _ \\| '_ \\| | \n  | | (_) | |_| | \\  /\\  / (_) | | | |_| \n  \\_/\\___/ \\__,_|  \\/  \\/ \\___/|_| |_(_)";
const std::string GAME_OVER = " _____                        _____                _ \n|  __ \\                      |  _  |              | | \n| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __| | \n| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__| | \n| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |  |_| \n \\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|  (_)";
const std::string DELIMITER = ",.-~*¨¯¨*·~-.,¸_¸,.-~*¨¯¨*·~-.¸_¸,.-~*¨¯";

// Text
const std::string COMMANDS = "Commands: \n-------------------- \nS     Start new game \nQ               Quit";

// Directories
const std::string VOCAB_FOLDER = "vocab/";


///////////////////////////////// TEXT HELPERS ////////////////////////////////

/*
    Converts given string to uppercase.
    @return: Reference to given string
*/
std::string& toUppercase(std::string& s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}


/*
    Converts given char to uppercase.
    Silently ignores chars that aren't letters.
    @return: Reference to given char
*/
char& toUppercase(char& c) {
    if(c >= 97 && c <= 122)
        c -= 32;
    return c;
}


/*
    Converts given string to lowercase.
    @return: Reference to given string
*/
std::string& toLowercase(std::string& s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}


/*
    Converts given char to lowercase.
    Silently ignores chars that aren't letters.
    @return: Reference to given char
*/
char& toLowercase(char& c) {
    if(c >= 65 && c <= 90)
        c += 32;
    return c;
}


/*
    @return: Whether the given char is A-Z or a-z
*/
bool isLetter(char& c) {
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}


/*
    @return: Whether the given string contains the given char
*/
bool stringContains(std::string s, char c) {
    return s.find(c) != std::string::npos;
}


///////////////////////////////// MISC HELPERS ////////////////////////////////


/*
    Prints the command prompt.
    @return: User input
*/
std::string prompt(std::string prefix=">>") {
    std::cout << "\n" << prefix << " ";
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


/*
    @return: Whether the given vector contains the given element
*/
template<typename T>
bool vectorContains(std::vector<T> v, T element) {
    return std::find(v.begin(), v.end(), element) != v.end();
}


/*
    @return: Whether the given set contains the given element
*/
template<typename T>
bool setContains(std::set<T> s, T element) {
    return s.find(element) != s.end();
}


///////////////////////////////// PLAY HELPERS ////////////////////////////////

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
            std::cout << "Error: The vocabulary list \"" << response << "\" is not a valid option." << std::endl;
    }
}


/*
    Prompts the user for a letter.
    Ensures that the letter is valid and not previously used.
    @return: char (A-z)
*/
char makeGuess(std::set<char>& guesses) {
    while(true) {
        std::cout << "\nGuess a Letter: ";
        std::string userInput;
        getline(std::cin, userInput);

        //Validation
        if(userInput.length() == 1) {
            char c = userInput.at(0);
            if(isLetter(c)) {
                toUppercase(c);
                if(!setContains(guesses, c))
                    return c;
                else
                    std::cout << "\nError: The letter \"" << c << "\" was already guessed." << std::endl;
            }
            else
                std::cout << "\nError: The character \"" << c << "\" is not a letter (A-z)." << std::endl;
        }
        else
            std::cout << "\nError: The input \"" << userInput << "\" is not a single character." << std::endl;
    }
}


/*
    Prints the state of the game in the format:
    <Hang State>
    <Word Progress>
    <Wrong Characters>
*/
void printTurn(int hangProgress, std::string word, std::set<char> guesses, std::set<char> badGuesses) {
    std::cout << STATE[hangProgress] << "\n" << std::endl;

    for(char& c : word) {
        if(setContains(guesses, c))
            std::cout << c << " ";
        else
            std::cout << "_ ";
    }

    if(!badGuesses.empty()) {
        std::cout << "\n\nIncorrect: ";
        int commaCount = badGuesses.size()-1;
        for(char c : badGuesses) {
            std::cout << c;
            if(commaCount > 0) {
                std::cout << ", ";
                --commaCount;
            }
        }
    }
    std::cout << std::endl;
}


/*
    @return: Whether the player has a winning condition.
*/
bool won(std::string& word, std::set<char>& guesses) {
    for(char& c : word) {
        if(!setContains(guesses, c))
            return false;
    }
    return true;
}


////////////////////////////////// FUNCTIONS //////////////////////////////////

/*
    Simulates a game of Hangman.
    @return: When game is finished
*/
void play() {
    std::vector<std::string> vocabList = promptVocab();
    std::string word = pickRandomElement(vocabList);
    std::set<char> guesses;
    std::set<char> badGuesses;
    int hangProgress = 0;

    // std::cout << "Your word is: " << word << std::endl; // debugging

    while(hangProgress < 8) {
        std::cout << DELIMITER << std::endl;
        printTurn(hangProgress, word, guesses, badGuesses);

        if(won(word, guesses))
            break;

        char guess = makeGuess(guesses);
        guesses.insert(guess);
        if(!stringContains(word, guess)) {
            ++hangProgress;
            badGuesses.insert(guess);
        }

        std::cout << std::endl;
    }

    if(hangProgress >= 7) {
        std::cout << "\n" << GAME_OVER << std::endl;
        std::cout << "\nYour word was: " << word << "." << std::endl;
    }
    else
        std::cout << "\n" << YOU_WON << std::endl;
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
            std::cout << "Error: The command \"" << command << "\" is not recognized." << std::endl;
    }
}


///////////////////////////////////// MAIN ////////////////////////////////////

int main(int argc, char const *argv[]) {
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