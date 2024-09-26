#include <fstream>
#include <iostream>
#include <sstream>
#include "zoo_classes.h"
#include "input_validation.h"

using namespace std;

// Some constants used in the program
const string FileName = "db.txt";
const string AddCommandFormat = "add <category character> <species name> <species count> <special attribute>";
const string DeleteCommandFormat = "delete <category character> <species name> <species count>";
const string ShowCommandFormat = "show <category character>";
const string ExitCommandFormat = "exit";
const string InvalidCommandError = "Error: Invalid command. Valid commands are add, delete, show and exit.\n";

void loadFromFile(Zoo_manager* manager) {
    ifstream fin(FileName);
    try {
        if (!fin.is_open()) {
            throw runtime_error("Error: Cannot open file " + FileName);
        }
    } catch (const runtime_error& e) {
        ofstream fout(FileName);
        if (!fout) {
            cerr << "Failed to create " + FileName << endl;
        }
        fout.close();
    }

    string line;
    string name, special_attr;
    string temp;
    int count;
    char category;

    enum read_status {declaration, mammal_reading, reptile_reading, bird_reading, aquatic_reading};
    int species_to_read;
    int species_read = 0;

    read_status current = declaration;
    while (getline(fin, line)) {
        istringstream iss(line);
        if (current == declaration) {
            if (line.substr(0, 13) == "total species") {
                current = declaration;
            }
            if (line.substr(0, 6) == "mammal") {
                current = mammal_reading;
                iss >> temp >> species_to_read;
                if (species_to_read == 0)
                    current = declaration;
            }
            else if (line.substr(0, 7) == "reptile") {
                current = reptile_reading;
                iss >> temp >> species_to_read;
                if (species_to_read == 0)
                    current = declaration;
            }
            else if (line.substr(0, 4) == "bird") {
                current = bird_reading;
                iss >> temp >> species_to_read;
                if (species_to_read == 0)
                    current = declaration;
            }
            else if (line.substr(0, 7) == "aquatic") {
                current = aquatic_reading;
                iss >> temp >> species_to_read;
                if (species_to_read == 0)
                    current = declaration;
            }
        }
        else {
            iss >> name >> count >> special_attr;
            switch (current)
            {
            case mammal_reading:
                category = 'M';
                break;
            case reptile_reading:
                category = 'R';
                break;
            case bird_reading:
                category = 'B';
                break;
            case aquatic_reading:
                category = 'Q';
                break;
            }
            manager->add_species(category, name, count, special_attr);
            species_read++;
            if (species_read == species_to_read) {
                current = declaration;
                species_read = 0;
            }
        }
    }
    fin.close();
}

int main() {
    string line;
    string command, name, special_attr;
    int count;
    char category;

    Zoo_manager* manager = new Zoo_manager();
    
    loadFromFile(manager);

    cout << "Data loaded from " + FileName << endl;
    while (true) {
        cin >> command;
        if (command == "add") {
            cin >> ws;
            getline(cin, line);
            if (validateAddCommand(line, category, name, count, special_attr)) {
                manager->add_species(category, name, count, special_attr);
            }
            else {
                cout << "Error: Invalid format. Valid format is '" << AddCommandFormat << "'" << endl;
            }
        }
        else if (command == "delete") {
            cin >> ws;
            getline(cin, line);
            if (validateDeleteCommand(line, category, name, count)) {
                manager->delete_species(category, name, count);
            }
            else {
                cout << "Error: Invalid format. Valid format is '" << DeleteCommandFormat << "'" << endl;
            }
        }
        else if (command == "show") {
            cin >> ws;
            getline(cin, line);
            if (validateShowCommand(line, category)) {
                manager->show_species(category);
            }
            else {
                cout << "Error: Invalid format. Valid format is '" << ShowCommandFormat << "'" << endl;
            }
        }
        else if (command == "exit") {
            getline(cin, line);
            if (validateExitCommand(line)) {
                ofstream fout(FileName);
                manager->save_to_txt(fout);
                fout.close();
                delete manager;
                break;
            }
            else {
                cout << "Error: Invalid format. Valid format is '" << ExitCommandFormat << "'" << endl;
            }
        }
        else {
            getline(cin, line);
            cout << InvalidCommandError;
        }
    }
    return 0;
}
