//
//  LineSegmentObject.cpp
//  GameEngine
//
//  Created by John Saba on 2/23/25.
//

#include "LineSegmentObject.hpp"

LineSegmentObject::LineSegmentObject(LineSegmentData data):
    id(data.id),
    pos(data.pos),
    col(data.col)
{
    for (glm::vec2 &p: data.pts)
    {
        glm::vec2 sp = p * data.scale;
        points.push_back(sp);
    }
}
