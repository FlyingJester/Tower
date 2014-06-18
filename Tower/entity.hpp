#pragma once
#include <string>

namespace tower{

typedef std::string string;

class Entity {
protected:
    string mName;
public:
    Entity();
    Entity(string);
    void setName(string aName);
};

}