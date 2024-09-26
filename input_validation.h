#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Splits the string into words. Splitting at spaces
vector<string> splitInput(const string& line) {
    istringstream iss(line);
    vector<string> words;
    string word;
    while (iss >> word)
        words.push_back(word);
    
    return words;
}

// Returns if the string is an positive integar or not
bool isIntegar(const string &str) {
    for (char c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// Function to validate the format of add command
bool validateAddCommand(const string& line, char& category, string& name, int& count, string& special_attr) {
    // split the input into words
    vector<string> words = splitInput(line);

    // if the number of words is not 4, return false
    if (words.size() != 4) {
        return false;
    }

    // If category is not a single character or not an alphabet, return false
    if (words[0].size() != 1 || !isalpha(words[0][0])) {
        return false;
    }
    else
        category = words[0][0];
    
    // name is the second word
    name = words[1];

    // If count is not an integar, return false
    if (!isIntegar(words[2])) {
        return false;
    }
    else
        count = stoi(words[2]);
    
    // special attribute is the last word
    special_attr = words[3];

    return true;
}

// Function to validate the format of delete command
bool validateDeleteCommand(const string& line, char& category, string& name, int& count) {
    // split the input into words
    vector<string> words = splitInput(line);

    // if the number of words is not 3, return false
    if (words.size() != 3) {
        return false;
    }
    
    // If category is not a single character or not an alphabet, return false
    if (words[0].size() != 1 || !isalpha(words[0][0])) {
        return false;
    }
    else
        category = words[0][0];
    
    // name is the second word
    name = words[1];

    // If count is not an integar, return false
    if (!isIntegar(words[2])) {
        return false;
    }
    else
        count = stoi(words[2]);
    
    return true;
}

// Function to validate the format of show command
bool validateShowCommand(const string& line, char& category) {
    // split the input into words
    vector<string> words = splitInput(line);
    
    if (words.size() != 1) {
        return false;
    }

    // If category is not a single character or not an alphabet, return false
    if (words[0].size() != 1 || !isalpha(words[0][0])) {
        return false;
    }
    else
        category = words[0][0];
    
    return true;
}

// Function to validate the format of exit command
bool validateExitCommand(const string& line) {
    // exit command is valid if there is nothing following 'exit'
    return line == "";
}
