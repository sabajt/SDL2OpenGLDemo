//
//  Lerp.h
//  GameEngine
//
//  Created by John Saba on 9/10/24.
//

#ifndef Lerp_h
#define Lerp_h

#include <glm/glm.hpp>

float lerp(float a, float b, float t);

// TODO: just use glm::mix probably...
glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t);
glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t);

#endif /* Lerp_h */
