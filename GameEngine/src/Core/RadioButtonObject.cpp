//
//  RadioButtonObject.cpp
//  GameEngine
//
//  Created by John Saba on 2/17/25.
//

#include "RadioButtonObject.hpp"
#include "Rand.hpp"

RadioButtonObject::RadioButtonObject(RadioButtonData data):
    pos(data.pos),
    col(data.col),
    buttonSize(data.buttonSize),
    selectedButton(0),
    numButtons(data.numButtons)
{
    
}

bool RadioButtonObject::handleSelection(glm::vec2 pt)
{
    if ((pt.y > pos.y && pt.y < pos.y + buttonSize.y) == false)
    {
        return false;
    }
        
    for (int i = 0; i < numButtons; ++i)
    {
        float left = pos.x + (float(i) * buttonSize.x) + (float(i) * buttonPadding);
        float right = left + buttonSize.x;
        
        if (pt.x > left && pt.x < right)
        {
            selectedButton = i;
            return true;
        }
    }
    return false;
}

void RadioButtonObject::randomize()
{
    selectedButton = intRandRange(0, numButtons - 1);
}
