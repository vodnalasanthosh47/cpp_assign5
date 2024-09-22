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
    
    void Print() {
        Zoo_species::Print();
        cout << aqua_feed_type_to_string(Aqua_feed) << endl;
    }

    bool Match_special_attr(string special_attr) {
        return special_attr == aqua_feed_type_to_string(Aqua_feed);
    }
};
