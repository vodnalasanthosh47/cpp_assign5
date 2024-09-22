#include <fstream>
#include <iostream>
#include <sstream>
#include "zoo_classes.h"

using namespace std;

int main() {
    string command, name, special_attr;
    int count;
    char category;

    Zoo_manager manager;
    
    ifstream fin("db.txt");
    if (!fin.is_open()) {
        ofstream fout("db.txt");
        fout.close();
    }

    if (fin.peek() != ifstream::traits_type::eof()) {
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
                manager.add_species(category, name, count, special_attr);
                species_read++;
                if (species_read == species_to_read) {
                    current = declaration;
                    species_read = 0;
                }
            }
        }
    }

    cout << "Start now" << endl;
    while (true) {
        cin >> command;
        if (command == "add") {
            cin >> category >> name >> count >> special_attr;
            manager.add_species(category, name, count, special_attr);
        }
        else if (command == "delete") {
            cin >> category >> name >> count;
            manager.delete_species(category, name, count);
        }
        else if (command == "show") {
            cin >> category;
            manager.show_species(category);
        }
        else if (command == "exit") {
            ofstream fout("db.txt");
            manager.save_to_txt(fout);
            break;
        }
    }
    return 0;
}
