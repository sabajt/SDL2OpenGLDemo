//
//  SliderObject.hpp
//  GameEngine
//
//  Created by John Saba on 2/14/25.
//

#ifndef SliderObject_hpp
#define SliderObject_hpp

#include <glm/glm.hpp>
#include <vector>

struct SliderData
{
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f);
    int minVal;
    int maxVal;
    int initVal;
};

class SliderObject
{
public:
    SliderObject(SliderData data);

    glm::vec2 pos;
    glm::vec2 size;
    glm::vec3 col;
    int val;
    glm::vec2 valSize;

    bool handleSelection(glm::vec2 pt);
    void randomize();

    // TODO: This gives offset norm which we rely on but not intended / predictable,
    float normVal();
    
private:
    // minVal is passed in val - 1 to get correct snapping behavior
    int minVal;
    int maxVal;
    
    void snapValSize();
};
#endif /* SliderObject_hpp */
