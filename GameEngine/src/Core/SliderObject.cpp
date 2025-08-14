//
//  SliderObject.cpp
//  GameEngine
//
//  Created by John Saba on 2/14/25.
//

#include "SliderObject.hpp"
#include "Rand.hpp"

SliderObject::SliderObject(SliderData data):
    pos(data.pos),
    size(data.size),
    col(data.col),
    minVal(data.minVal - 1),
    maxVal(data.maxVal),
    val(data.initVal)
{
    snapValSize();
}

bool SliderObject::handleSelection(glm::vec2 pt)
{
    if (pt.x > pos.x && pt.x < pos.x + size.x && pt.y > pos.y && pt.y < pos.y + size.y)
    {
        float percent = (pt.x - pos.x) / size.x;
        float percentValue = percent * float(maxVal - minVal);
        val = minVal + int(ceil(percentValue));
        snapValSize();
        
        return true;
    }
    return false;
}

void SliderObject::randomize()
{
    val = intRandRange(minVal + 1, maxVal);
    snapValSize();
}

float SliderObject::normVal()
{
    return static_cast<float>(val) / static_cast<float>(maxVal);
}

void SliderObject::snapValSize()
{
    float snapped = (float(val - minVal) / float(maxVal - minVal));
    valSize = glm::vec2(snapped * size.x, size.y);
}
