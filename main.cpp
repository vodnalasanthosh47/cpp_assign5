#include <fstream>
#include <iostream>
#include <sstream>
#include "zoo_classes.h"

using namespace std;

const string FileName = "db.txt";

int space_counter(const string &str) {
    int count = 0;
    for (char c : str) {
        if (c == ' ')
            count++;
    }
    return count;
}

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
            getline(cin, line);
            num_spaces = space_counter(line);
            if (num_spaces == 4) {
                istringstream iss(line);
                iss >> category >> name >> count >> special_attr;
                manager->add_species(category, name, count, special_attr);
            }
            else {
                cout << "Error: Invalid command. Valid command for 'add' is 'add <category character> <species name> <species count> <special attribute>'" << endl;
            }
        }
        else if (command == "delete") {
            getline(cin, line);
            num_spaces = space_counter(line);
            if (num_spaces == 3) {
                istringstream iss(line);
                iss >> category >> name >> count;
                manager->delete_species(category, name, count);
            }
            else {
                cout << "Error: Invalid command. Valid command for 'delete' is 'delete <category character> <species name> <species count>'" << endl;
            }
        }
        else if (command == "show") {
            getline(cin, line);
            num_spaces = space_counter(line);
            if (num_spaces == 1) {
                manager->show_species(line[1]);
            }
            else {
                cout << "Error: Invalid command. Valid command for 'show' is 'show <category character>'" << endl;
            }
        }
        else if (command == "exit") {
            ofstream fout(FileName);
            manager->save_to_txt(fout);
            fout.close();
            delete manager;
            break;
        }
        else {
            cout << "Error: Invalid command. Valid commands are add, delete, show and exit." << endl;
        }
    }
    return 0;
}
