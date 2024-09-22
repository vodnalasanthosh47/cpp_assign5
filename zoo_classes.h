#include <bits/stdc++.h>

using namespace std;

enum diet_type {herbivore, carnivore};
enum size_type {small, medium, large};
enum bird_feed_type {grain, insect, fish};
enum aqua_feed_type {fishfood, livefish, plants};

string diet_type_to_string(diet_type type) {
    switch (type)
    {
    case herbivore:
        return "herbivore";
    case carnivore:
        return "carnivore";
    default:
        return "";
    }
    
}

string size_type_to_string(size_type type) {
    switch (type)
    {
    case small:
        return "small";
    case medium:
        return "medium";
    case large:
        return "large";
    default:
        return "";
    }
}

string bird_feed_type_to_string(bird_feed_type type) {
    switch (type)
    {
    case grain:
        return "grain";
    case insect:
        return "insect";
    case fish:
        return "fish";
    default:
        return "";
    }
}

string aqua_feed_type_to_string(aqua_feed_type type) {
    switch (type)
    {
    case fishfood:
        return "fishfood";
    case livefish:
        return "livefish";
    case plants:
        return "plants";
    default:
        return "";
    }
}

class Zoo_species {
protected:
    string Species_name;
    char category;
    int Species_count;
public:
    Zoo_species(string name, int count) 
    : Species_name(name), Species_count(count) {}
    
    virtual ~Zoo_species() {}
    
    void Set_name(string name) {
        Species_name = name;
    }

    void Set_count(int count) {
        Species_count = count;
    }

    int Get_count() {
        return Species_count;
    }

    char Get_category() {
        return category;
    }

    virtual string to_str() {
        return Species_name + " " + to_string(Species_count);
    }

    virtual void Print() {
        cout << Species_name << " " << Species_count << " ";
    }

    bool Match(string name, char category) {
        return Species_name == name && this->category == category;
    }

    virtual bool Match_special_attr(string special_attr) = 0;
};

class Mammal: public Zoo_species {
private:
    diet_type Diet_type;
public:
    Mammal(string name, int count, diet_type type)
    : Zoo_species(name, count) {
        Diet_type = type;
        category = 'M';
    }
    
    void Set_diet_type(diet_type type) {
        Diet_type = type;
    }

    string to_str() {
        return Zoo_species::to_str() + " " + diet_type_to_string(Diet_type);
    }

    void Print() {
        Zoo_species::Print();
        cout << diet_type_to_string(Diet_type) << endl;
    }

    bool Match_special_attr(string special_attr) {
        return special_attr == diet_type_to_string(Diet_type);
    }
};

class Reptile: public Zoo_species {
private:
    size_type Feed_size;
public:
    Reptile(string name, int count, size_type type)
    : Zoo_species(name, count) {
        Feed_size = type;
        category = 'R';
    }
    
    void Set_feed_size(size_type type) {
        Feed_size = type;
    }

    string to_str() {
        return Zoo_species::to_str() + " " + size_type_to_string(Feed_size);
    }
    
    void Print() {
        Zoo_species::Print();
        cout << size_type_to_string(Feed_size) << endl;
    }

    bool Match_special_attr(string special_attr) {
        return special_attr == size_type_to_string(Feed_size);
    }
};

class Bird: public Zoo_species {
private:
    bird_feed_type Bird_feed;
public:
    Bird(string name, int count, bird_feed_type type)
    : Zoo_species(name, count) {
        Bird_feed = type;
        category = 'B';
    }
    
    void Set_bird_feed(bird_feed_type type) {
        Bird_feed = type;
    }
    
    string to_str() {
        return Zoo_species::to_str() + " " + bird_feed_type_to_string(Bird_feed);
    }
    
    void Print() {
        Zoo_species::Print();
        cout << bird_feed_type_to_string(Bird_feed) << endl;
    }

    bool Match_special_attr(string special_attr) {
        return special_attr == bird_feed_type_to_string(Bird_feed);
    }
};

class Aquatic: public Zoo_species {
private:
    aqua_feed_type Aqua_feed;
public:
    Aquatic(string name, int count, aqua_feed_type type)
    : Zoo_species(name, count) {
        Aqua_feed = type;
        category = 'Q';
    }
    
    void Set_aqua_feed(aqua_feed_type type) {
        Aqua_feed = type;
    }
    
    string to_str() {
        return Zoo_species::to_str() + " " + aqua_feed_type_to_string(Aqua_feed);
    }
    
    void Print() {
        Zoo_species::Print();
        cout << aqua_feed_type_to_string(Aqua_feed) << endl;
    }

    bool Match_special_attr(string special_attr) {
        return special_attr == aqua_feed_type_to_string(Aqua_feed);
    }
};

class Zoo_manager {
private:
    vector<Zoo_species*> zoo;
    int num_mammals, num_reptiles, num_birds, num_aquatics;

    void print_category(char category, int num_category) {
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
public:
    Zoo_manager() {
        num_mammals = 0;
        num_reptiles = 0;
        num_birds = 0;
        num_aquatics = 0;
    }

    void add_species(char category, string name, int count, string special_attr) {
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

    void delete_species(char category, string name, int count) {
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

    void show_species(char category) {
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

    void save_to_txt(ofstream& fout) {
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
};
