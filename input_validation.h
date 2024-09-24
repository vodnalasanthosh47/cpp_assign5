#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

vector<string> splitInput(const string& line) {
    istringstream iss(line);
    vector<string> words;
    string word;
    while (iss >> word)
        words.push_back(word);
    
    return words;
}

bool isIntegar(const string &str) {
    for (char c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool validateAddCommand(const string& line, char& category, string& name, int& count, string& special_attr) {
    vector<string> words = splitInput(line);

    if (words.size() != 4)
        return false;
    
    if (words[0].size() != 1 || !isalpha(words[0][0]))
        return false;
    else
        category = words[0][0];
    
    name = words[1];

    if (!isIntegar(words[2]))
        return false;
    else
        count = stoi(words[2]);
    
    special_attr = words[3];

    return true;
}

bool validateDeleteCommand(const string& line, char& category, string& name, int& count) {
    vector<string> words = splitInput(line);

    if (words.size() != 3)
        return false;
    
    if (words[0].size() != 1 || !isalpha(words[0][0]))
        return false;
    else
        category = words[0][0];
    
    name = words[1];

    if (!isIntegar(words[2]))
        return false;
    else
        count = stoi(words[2]);
    
    return true;
}

bool validateShowCommand(const string& line, char& category) {
    vector<string> words = splitInput(line);
    if (words[0].size() != 1 || !isalpha(words[0][0]))
        return false;
    else
        category = words[0][0];
    
    return true;
}

bool validateExitCommand(const string& line) {
    return line == "";
}
