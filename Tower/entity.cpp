#include "entity.hpp"


tower::Entity::Entity(){
    mName = "";
}
tower::Entity::Entity(tower::string aName){
    mName = aName;
}

void tower::Entity::setName(tower::string aName){
    mName = aName;
}