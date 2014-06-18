#include "location.hpp"

#include <cmath>
#include <cassert>

static inline unsigned int deltaDistance(int xd, int yd){
    yd*=yd;
    xd*=xd;
    
    unsigned ad = xd+yd;
    
    return sqrt(ad);
}


namespace tower {

Location::Location(int _x, int _y)
  : x(_x)
  , y(_y){
}
    
unsigned int Location::distance(const Location &r) const{
    int xd = x-r.x;
    int yd = y-r.y;
    
    return deltaDistance(xd, yd);
    
}

unsigned int Location::distance(const Location *r) const{
    assert(r!=nullptr);
    int xd = x-r->x;
    int yd = y-r->y;
    
    return deltaDistance(xd, yd);
}



}