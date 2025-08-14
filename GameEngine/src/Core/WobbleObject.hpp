//
//  WobbleObject.hpp
//  GameEngine
//
//  Created by John Saba on 1/25/25.
//

#ifndef WobbleObject_hpp
#define WobbleObject_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "PointMass.h"
#include "Constants.h"

enum WobbleRenderMode
{
    RENDER_MODE_LINE = 0,
    RENDER_MODE_SOLID,
    RENDER_MODE_SDF_PARTICLE,
    RENDER_MODE_GRADIENT,
    RENDER_MODE_COOL
};

struct WobbleData
{
    unsigned int id;
    unsigned int res;
    WobbleRenderMode renderMode;
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec3 col;
    float radStart;
    float radEnd;
    int life;
    float wobbleStartSpeed;
    float pull;
    float damp;
    bool fadeOut = true;
};

struct GeoData
{
    unsigned int id;
    std::vector<glm::vec2> pts;
    glm::vec2 pos;
    glm::vec3 col;
    glm::vec2 scale;
    
    // defaults
    float wobbleStartSpeed = UI_WOBBLE_START_SPEED;
    float pull = UI_WOBBLE_PULL;
    float damp = UI_WOBBLE_DAMP;
};

class WobbleObject
{
public:
    WobbleObject(WobbleData data);
    WobbleObject(GeoData data);

    unsigned int id;
    WobbleRenderMode renderMode;
    glm::vec3 col;
    glm::vec2 pos;
    glm::vec2 lastPos;
    std::vector<PointMass> points;
    
    float alpha = 1.0f;
    int t = 0;
    bool shouldDelete = false;
    
    void update();
    void shake();
    
private:
    unsigned int res;
    float radStart;
    float radEnd;
    float rad;
    float lastRad;
    int life;
    glm::vec2 vel;
    std::vector<glm::vec2> restingPoints;
    bool fadeOut;
    float wobbleStartSpeed;
    float damp;
    float pull;
    
    void addPoint(glm::vec2 pos);
    void updateRestingPoints(int i);

};
#endif /* WobbleObject_hpp */
