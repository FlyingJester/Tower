#pragma once

namespace tower {

class Location {
public:
    Location(int, int);
    virtual ~Location(){}
    int x, y;
    
    virtual unsigned int distance(const Location &r) const;
    virtual unsigned int distance(const Location *) const;
    
};


}