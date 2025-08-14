//
//  PointMass.h
//  GameEngine
//
//  Created by John Saba on 1/25/25.
//

#ifndef PointMass_h
#define PointMass_h

#include <glm/glm.hpp>

struct PointMass
{
    PointMass(glm::vec2 position, glm::vec2 velocity): 
        pos(position),
        lastPos(position),
        vel(velocity)
    {
        
    }
    
    glm::vec2 pos;
    glm::vec2 lastPos;
    glm::vec2 vel;
    glm::vec2 acl;
};

#endif /* PointMass_h */
