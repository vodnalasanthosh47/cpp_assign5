#include "zoo_species.h"
#include "enum_to_str.h"

using namespace std;

string diet_type_to_string(diet_type type) {
    switch (type)
    {
    case herbivore:
        return "herbivore";
    case carnivore:
        return "carnivore";
    default:
        return "invalid";
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
        return "invalid";
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
        return "invalid";
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
        return "invalid";
    }
}
