#pragma once
#include "location.hpp"
#include "entity.hpp"
#include <string>

namespace tower {

typedef std::string string;

/////
// Base class that all in game building entities are built out of.
class Room : public Location, public Entity{
    string mName;
    unsigned long long ID;
public:
    Room() : Location(0, 0) {}
    Room(int x, int y) : Location(x, y) {}
    
    void setName(string aName){
        mName = aName;
    }
    
};

}