//
//  RadioButtonObject.hpp
//  GameEngine
//
//  Created by John Saba on 2/17/25.
//

#ifndef RadioButtonObject_hpp
#define RadioButtonObject_hpp

#include <glm/glm.hpp>
#include <vector>

struct RadioButtonData
{
    glm::vec2 pos;
    glm::vec3 col;
    glm::vec2 buttonSize;
    int numButtons;
};

class RadioButtonObject
{
public:
    RadioButtonObject(RadioButtonData data);

    glm::vec2 pos;
    glm::vec3 col;
    glm::vec2 buttonSize;
    int numButtons;
    int selectedButton;
    
    float buttonPadding = 10.0f;

    bool handleSelection(glm::vec2 pt);
    void randomize();
};

#endif /* RadioButtonObject_hpp */
