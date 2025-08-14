//
//  ButtonObject.cpp
//  GameEngine
//
//  Created by John Saba on 2/24/25.
//

#include "ButtonObject.hpp"

ButtonObject::ButtonObject(ButtonData data):
    pos(data.pos),
    col(data.col),
    size(data.size)
{
    
}

void ButtonObject::update()
{
    const float scale = 1.0f;
    
    if (flash > 0)
    {
        float t = static_cast<float>(flash) * scale;
        alpha = (sin(t) + 1.0f) / 2.0f;
        
        --flash;
    }
    else 
    {
        alpha = 1.0f;
    }
}

bool ButtonObject::handleSelection(glm::vec2 pt)
{
    if (pt.x > pos.x && pt.x < pos.x + size.x && pt.y > pos.y && pt.y < pos.y + size.y)
    {
        flash = flashPeriod;
        return true;
    }
    return false;
}
