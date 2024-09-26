#ifndef ZOO_CLASSES_H
#define ZOO_CLASSES_H

#include <bits/stdc++.h>

using namespace std;

enum diet_type
{
    herbivore,
    carnivore
};
enum size_type
{
    small,
    medium,
    large
};
enum bird_feed_type
{
    grain,
    insect,
    fish
};
enum aqua_feed_type
{
    fishfood,
    livefish,
    plants
};

class Zoo_species
{
protected:
    string Species_name;
    char category;
    int Species_count;

public:
    Zoo_species(string name, int count);

    virtual ~Zoo_species() = default;

    void Set_name(string name);

    void Set_count(int count);

    int Get_count() const;

    char Get_category() const;

    virtual string to_str() const;

    virtual void Print() const;

    bool Match(string name, char category) const;

    virtual bool Match_special_attr(string special_attr) const = 0;
};

class Mammal : public Zoo_species
{
private:
    diet_type Diet_type;

public:
    Mammal(string name, int count, diet_type type);

    ~Mammal() = default;

    void Set_diet_type(diet_type type);

    string to_str() const;

    void Print() const;

    bool Match_special_attr(string special_attr) const;
};

class Reptile : public Zoo_species
{
private:
    size_type Feed_size;

public:
    Reptile(string name, int count, size_type type);

    ~Reptile() = default;

    void Set_feed_size(size_type type);

    string to_str() const;

    void Print() const;

    bool Match_special_attr(string special_attr) const;
};

class Bird : public Zoo_species
{
private:
    bird_feed_type Bird_feed;

public:
    Bird(string name, int count, bird_feed_type type);

    ~Bird() = default;

    void Set_bird_feed(bird_feed_type type);

    string to_str() const;

    void Print() const;

    bool Match_special_attr(string special_attr) const;
};

class Aquatic : public Zoo_species
{
private:
    aqua_feed_type Aqua_feed;

public:
    Aquatic(string name, int count, aqua_feed_type type);

    ~Aquatic() = default;

    void Set_aqua_feed(aqua_feed_type type);

    string to_str() const;

    void Print() const;

    bool Match_special_attr(string special_attr) const;
};

class Zoo_manager
{
private:
    vector<Zoo_species *> zoo;
    int num_mammals, num_reptiles, num_birds, num_aquatics;

    void print_category(char category, int num_category) const;

public:
    Zoo_manager();

    ~Zoo_manager();

    void add_species(char category, string name, int count, string special_attr);

    void delete_species(char category, string name, int count);

    void show_species(char category) const;

    void save_to_txt(ofstream &fout) const;
};

#endif