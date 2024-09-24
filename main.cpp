#include <fstream>
#include <iostream>
#include <sstream>
#include "zoo_classes.h"
#include "input_validation.h"

using namespace std;

const string FileName = "db.txt";

int main() {
    string command, name, special_attr;
    int count;
    char category;

    Zoo_manager* manager = new Zoo_manager();
    
    ifstream fin(FileName);
    if (!fin.is_open()) {
        ofstream fout(FileName);
        fout.close();
    }

    string line;
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
                iss >> name >> species_to_read;
                if (species_to_read == 0)
                    current = declaration;
            }
            else if (line.substr(0, 7) == "reptile") {
                current = reptile_reading;
                iss >> name >> species_to_read;
                if (species_to_read == 0)
                    current = declaration;
            }
            else if (line.substr(0, 4) == "bird") {
                current = bird_reading;
                iss >> name >> species_to_read;
                if (species_to_read == 0)
                    current = declaration;
            }
            else if (line.substr(0, 7) == "aquatic") {
                current = aquatic_reading;
                iss >> name >> species_to_read;
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
    
    int num_spaces;

    cout << "Start now" << endl;
    while (true) {
        cin >> command;
        if (command == "add") {
            cin >> ws;
            getline(cin, line);
            if (validateAddCommand(line, category, name, count, special_attr)) {
                cout << category << ":" << name << ":" << count << ":" << special_attr << endl;
                manager->add_species(category, name, count, special_attr);
            }
            else {
                cout << "Error: Invalid command. Valid command for 'add' is 'add <category character> <species name> <species count> <special attribute>'" << endl;
            }
        }
        else if (command == "delete") {
            cin >> ws;
            getline(cin, line);
            if (validateDeleteCommand(line, category, name, count)) {
                manager->delete_species(category, name, count);
            }
            else {
                cout << "Error: Invalid command. Valid command for 'delete' is 'delete <category character> <species name> <species count>'" << endl;
            }
        }
        else if (command == "show") {
            cin >> ws;
            getline(cin, line);
            if (validateShowCommand(line, category)) {
                manager->show_species(category);
            }
            else {
                cout << "Error: Invalid command. Valid command for 'show' is 'show <category character>'" << endl;
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
                cout << "Error: Invalid command. Valid command for 'exit' is 'exit'" << endl;
            }
        }
        else {
            cout << "Error: Invalid command. Valid commands are add, delete, show and exit." << endl;
        }
    }
    return 0;
}
