//
//  WobbleObject.cpp
//  GameEngine
//
//  Created by John Saba on 1/25/25.
//

#include "WobbleObject.hpp"
#include "Rand.hpp"
#include "Lerp.h"

WobbleObject::WobbleObject(WobbleData data):
    id(data.id),
    res(data.res),
    renderMode(data.renderMode),
    pos(data.pos),
    lastPos(data.pos),
    vel(data.vel),
    col(data.col),
    radStart(data.radStart),
    radEnd(data.radEnd),
    rad(data.radStart),
    lastRad(data.radStart),
    life(data.life),
    wobbleStartSpeed(data.wobbleStartSpeed),
    pull(data.pull),
    damp(data.damp),
    fadeOut(data.fadeOut)
{
    printf("\n");
    for (int i = 0; i < res; ++i)
    {
        float angle = 2 * M_PI * i / res;
        float x = rad * cos(angle);
        float y = rad * sin(angle);
        auto p = glm::vec2(x, y);
        addPoint(p);
        restingPoints.push_back(p);
        
        printf("\npoint %f, %f", x, y);
    }
}

WobbleObject::WobbleObject(GeoData data):
    id(data.id),
    pos(data.pos),
    lastPos(data.pos),
    col(data.col),
    wobbleStartSpeed(data.wobbleStartSpeed),
    pull(data.pull),
    damp(data.damp),

    // not configurable
    vel(glm::vec2(0.0f, 0.0f)),
    res(0),
    radStart(0.0f),
    radEnd(0.0f),
    rad(0.0f),
    lastRad(0.0f),
    life(0),
    fadeOut(false),

    renderMode(RENDER_MODE_LINE)
{
    for (int i = 0; i < 2; ++i)
    {
        for (glm::vec2 &p: data.pts)
        {
            glm::vec2 sp = p * data.scale;
            addPoint(sp);
            restingPoints.push_back(sp);
        }
        for (auto iter = data.pts.rbegin() + 1; iter != data.pts.rend() - 1; ++iter)
        {
            glm::vec2 sp = *iter * data.scale;
            addPoint(sp);
            restingPoints.push_back(sp);
        }
    }
}

void WobbleObject::addPoint(glm::vec2 pos)
{
    float r1 = unitRand() * wobbleStartSpeed;
    float r2 = unitRand() * wobbleStartSpeed;
    
    points.push_back(PointMass(pos, glm::vec2(r1, r2)));
}

void WobbleObject::update()
{
    float decay = 0.0f;
    if (life > 0)
    {
        decay = fmin(static_cast<float>(t) / static_cast<float>(life), 1.0f);
    }
    if (fadeOut) // TODO: life should imply fadeout
    {
        t += 1;
        if (t >= (life))
        {
            shouldDelete = true;
        }
        alpha = 1.0f - decay;
    }
    
    // Move object position
    lastPos = pos;
    pos += vel;
    
    if (fadeOut) // TODO: life should imply fadeout
    {
        // Update radius
        lastRad = rad;
        rad = lerp(radStart, radEnd, decay);
    }
        
    // Animate wobbly points
    int i = 0;
    for (auto &p: points)
    {
        // update resting point if needed
        if (rad != lastRad)
        {
            updateRestingPoints(i);
        }
        
        glm::vec2 rp = restingPoints[i];

        // get direction
        glm::vec2 dir = rp - p.pos;
        if (glm::dot(dir, dir) > 0)
        {
            dir = glm::normalize(dir);
        }
        dir *= pull;
        ++i;
        
        p.acl = dir;
        p.vel += p.acl;
        p.vel *= 1.0f - damp;
        p.lastPos = p.pos;
        p.pos += p.vel;
    }
}

void WobbleObject::shake()
{
    pull += 3.0f;
}

void WobbleObject::updateRestingPoints(int i)
{
    float angle = 2 * M_PI * i / res;
    float x = rad * cos(angle);
    float y = rad * sin(angle);
    auto p = glm::vec2(x, y);
    restingPoints[i] = p;
}
