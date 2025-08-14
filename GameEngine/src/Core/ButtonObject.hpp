//
//  ButtonObject.hpp
//  GameEngine
//
//  Created by John Saba on 2/24/25.
//

#ifndef ButtonObject_hpp
#define ButtonObject_hpp

#include <glm/glm.hpp>

struct ButtonData
{
    glm::vec2 pos;
    glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec2 size;
};

class ButtonObject
{
public:
    ButtonObject(ButtonData data);

    glm::vec2 pos;
    glm::vec3 col;
    glm::vec2 size;
    float alpha = 1.0;
    
    void update();
    bool handleSelection(glm::vec2 pt);
    
private:
    const int flashPeriod = 30;
    int flash = 0;

};

#endif /* ButtonObject_hpp */
