#include <bits/stdc++.h>
#include "zoo_species.h"

// Zoo_manager methods
void Zoo_manager::print_category(char category, int num_category) const {
    switch (category) 
    {
        case 'M':
            cout << "mammal " << num_category << endl;
            break;
        case 'R':
            cout << "reptile " << num_category << endl;
            break;
        case 'B':
            cout << "bird " << num_category << endl;
            break;
        case 'Q':
            cout << "aquatic " << num_category << endl;
            break;
    }
    for (Zoo_species* species : zoo) {
        if (species->Get_category() == category) {
            species->Print();
        }
    }
}

Zoo_manager::Zoo_manager() {
    num_mammals = 0;
    num_reptiles = 0;
    num_birds = 0;
    num_aquatics = 0;
}

Zoo_manager::~Zoo_manager() {
    for (Zoo_species* species : zoo) {
        delete species;
    }
    delete &zoo;
}

void Zoo_manager::add_species(char category, string name, int count, string special_attr) {
    bool found = false;
    for (Zoo_species* species : zoo) {
        if (species->Match(name, category)) {
            found = true;
            if (species->Match_special_attr(special_attr)) {
                species->Set_count(species->Get_count() + count);
            }
            else {
                cout << "Error: Special attribute mismatch" << endl;
            }
            break;
        }
    }
    if (!found) {
        switch (category) 
        {
            case 'M':
                if (special_attr == "herbivore") {
                    zoo.push_back(new Mammal(name, count, herbivore));
                    num_mammals++;
                }
                else if (special_attr == "carnivore") {
                    zoo.push_back(new Mammal(name, count, carnivore));
                    num_mammals++;
                }
                else
                    cout << "Error: Invalid special attribute" << endl;
                break;
            case 'R':
                if (special_attr == "small") {
                    zoo.push_back(new Reptile(name, count, small));
                    num_reptiles++;
                }
                else if (special_attr == "medium") {
                    zoo.push_back(new Reptile(name, count, medium));
                    num_reptiles++;
                }
                else if (special_attr == "large") {
                    zoo.push_back(new Reptile(name, count, large));
                    num_reptiles++;
                }
                else
                    cout << "Error: Invalid special attribute" << endl;
                break;
            case 'B':
                if (special_attr == "grain") {
                    zoo.push_back(new Bird(name, count, grain));
                    num_birds++;
                }
                else if (special_attr == "insect") {
                    zoo.push_back(new Bird(name, count, insect));
                    num_birds++;
                }
                else if (special_attr == "fish") {
                    zoo.push_back(new Bird(name, count, fish));
                    num_birds++;
                }
                else
                    cout << "Error: Invalid special attribute" << endl;
                break;
            case 'Q':
                if (special_attr == "fishfood") {
                    zoo.push_back(new Aquatic(name, count, fishfood));
                    num_aquatics++;
                }
                else if (special_attr == "livefish") {
                    zoo.push_back(new Aquatic(name, count, livefish));
                    num_aquatics++;
                }
                else if (special_attr == "plants") {
                    zoo.push_back(new Aquatic(name, count, plants));
                    num_aquatics++;
                }
                else
                    cout << "Error: Invalid special attribute" << endl;
                break;
            default:
                cout << "Error: Invalid category" << endl;
                break;
        }
    }
}

void Zoo_manager::delete_species(char category, string name, int count) {
    bool found = false;
        for (int i = 0; i < zoo.size(); i++) {
            if (zoo[i]->Match(name, category)) {
                found = true;
                if (zoo[i]->Get_count() > count) {
                    zoo[i]->Set_count(zoo[i]->Get_count() - count);
                    break;
                }
                else if (zoo[i]->Get_count() == count) {
                    Zoo_species* species = zoo[i];
                    zoo.erase(zoo.begin() + i);
                    char species_category = species->Get_category();
                    switch (species_category) 
                    {
                        case 'M':
                            num_mammals--;
                            break;
                        case 'R':
                            num_reptiles--;
                            break;
                        case 'B':
                            num_birds--;
                            break;
                        case 'Q':
                            num_aquatics--;
                            break;
                    }
                    delete species;
                    break;
                }
                else {
                    cout << "Error: Count to delete exceeds current count" << endl;
                    break;
                }
            }
        }
        if (!found) {
            cout << "Error: Given species not found" << endl;
        }
}

void Zoo_manager::show_species(char category) const {
    if (category == 'A') {
            cout << "total species " << zoo.size() << endl;
            print_category('M', num_mammals);
            print_category('R', num_reptiles);
            print_category('B', num_birds);
            print_category('Q', num_aquatics);
    }
    else if (category == 'M') {
        print_category('M', num_mammals);
    }
    else if (category == 'R') {
        print_category('R', num_reptiles);
    }
    else if (category == 'B') {
        print_category('B', num_birds);
    }
    else if (category == 'Q') {
        print_category('Q', num_aquatics);
    }
    else {
        cout << "Error: Invalid category" << endl;
    }
}

void Zoo_manager::save_to_txt(ofstream& fout) const{
    int num_species_to_save = 0;
    int species_saved = 0;
    fout << "total species " << zoo.size() << endl;
    
    fout << "mammal " << num_mammals << endl;
    num_species_to_save = num_mammals;
    species_saved = 0;
    for (Zoo_species* species : zoo) {
        if (species->Get_category() == 'M') {
            fout << species->to_str() << endl;
            species_saved++;
        }
        if (species_saved == num_species_to_save)
            break;
    }

    fout << "reptile " << num_reptiles << endl;
    num_species_to_save = num_reptiles;
    species_saved = 0;
    for (Zoo_species* species : zoo) {
        if (species->Get_category() == 'R') {
            fout << species->to_str() << endl;
            species_saved++;
        }
        if (species_saved == num_species_to_save)
            break;
    }
    
    fout << "bird " << num_birds << endl;
    num_species_to_save = num_birds;
    species_saved = 0;
    for (Zoo_species* species : zoo) {
        if (species->Get_category() == 'B') {
            fout << species->to_str() << endl;
            species_saved++;
        }
        if (species_saved == num_species_to_save)
            break;
    }

    fout << "aquatic " << num_aquatics << endl;
    num_species_to_save = num_aquatics;
    species_saved = 0;
    for (Zoo_species* species : zoo) {
        if (species->Get_category() == 'Q') {
            fout << species->to_str() << endl;
            species_saved++;
        }
        if (species_saved == num_species_to_save)
            break;
    }
}
