//
//  LineSegmentObject.hpp
//  GameEngine
//
//  Created by John Saba on 2/23/25.
//

#ifndef LineSegmentObject_hpp
#define LineSegmentObject_hpp

#include <glm/glm.hpp>
#include <vector>

struct LineSegmentData
{
    unsigned int id;
    glm::vec2 pos;
    glm::vec3 col;
    glm::vec2 scale;
    std::vector<glm::vec2> pts;
};

class LineSegmentObject
{
public:
    LineSegmentObject(LineSegmentData data);

    unsigned int id;
    glm::vec3 col;
    glm::vec2 pos;
    std::vector<glm::vec2> points;
};

#endif /* LineSegmentObject_hpp */
