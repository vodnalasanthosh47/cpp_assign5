#include <bits/stdc++.h>
#include "zoo_classes.h"
#include "enum_to_str.h"

using namespace std;

// Zoo_species methods
Zoo_species::Zoo_species(string name, int count) : Species_name(name), Species_count(count) {}

    
void Zoo_species::Set_name(string name) {
    Species_name = name;
}

void Zoo_species::Set_count(int count) {
    Species_count = count;
}

int Zoo_species::Get_count() const{
    return Species_count;
}

char Zoo_species::Get_category() const {
    return category;
}

string Zoo_species::to_str() const {
    return Species_name + " " + to_string(Species_count);
}

void Zoo_species::Print() const {
    cout << Species_name << " " << Species_count << " ";
}

bool Zoo_species::Match(string name, char category) const {
    return Species_name == name && this->category == category;
}

// Mammal methods
Mammal::Mammal(string name, int count, diet_type type) : Zoo_species(name, count) {
    Diet_type = type;
    category = 'M';
}

void Mammal::Set_diet_type(diet_type type) {
    Diet_type = type;
}

string Mammal::to_str() const{
    return Zoo_species::to_str() + " " + diet_type_to_string(Diet_type);
}

void Mammal::Print() const {
    Zoo_species::Print();
    cout << diet_type_to_string(Diet_type) << endl;
}

bool Mammal::Match_special_attr(string special_attr) const{
    return special_attr == diet_type_to_string(Diet_type);
}


// Reptile methods
Reptile::Reptile(string name, int count, size_type type) : Zoo_species(name, count) {
    Feed_size = type;
    category = 'R';
}

void Reptile::Set_feed_size(size_type type) {
    Feed_size = type;
}

string Reptile::to_str() const {
    return Zoo_species::to_str() + " " + size_type_to_string(Feed_size);
}

void Reptile::Print() const {
    Zoo_species::Print();
    cout << size_type_to_string(Feed_size) << endl;
}

bool Reptile::Match_special_attr(string special_attr) const {
    return special_attr == size_type_to_string(Feed_size);
}


// Bird methods
Bird::Bird(string name, int count, bird_feed_type type) : Zoo_species(name, count) {
    Bird_feed = type;
    category = 'B';
}

void Bird::Set_bird_feed(bird_feed_type type) {
    Bird_feed = type;
}

string Bird::to_str() const {
    return Zoo_species::to_str() + " " + bird_feed_type_to_string(Bird_feed);
}

void Bird::Print() const {
    Zoo_species::Print();
    cout << bird_feed_type_to_string(Bird_feed) << endl;
}

bool Bird::Match_special_attr(string special_attr) const {
    return special_attr == bird_feed_type_to_string(Bird_feed);
}


// Aquatic methods
Aquatic::Aquatic(string name, int count, aqua_feed_type type) : Zoo_species(name, count) {
    Aqua_feed = type;
    category = 'Q';
}

void Aquatic::Set_aqua_feed(aqua_feed_type type) {
    Aqua_feed = type;
}

string Aquatic::to_str() const {
    return Zoo_species::to_str() + " " + aqua_feed_type_to_string(Aqua_feed);
}

void Aquatic::Print() const {
    Zoo_species::Print();
    cout << aqua_feed_type_to_string(Aqua_feed) << endl;
}

bool Aquatic::Match_special_attr(string special_attr) const {
    return special_attr == aqua_feed_type_to_string(Aqua_feed);
}
