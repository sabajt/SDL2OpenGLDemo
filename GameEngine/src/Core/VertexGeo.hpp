//
//  VertexGeo.hpp
//  GameEngine
//
//  Created by John Saba on 2/23/25.
//

#ifndef VertexGeo_hpp
#define VertexGeo_hpp

#include <vector>
#include <string>
#include <glm/glm.hpp>

void fillLineVerticalVtx(std::vector<glm::vec2> &points);
void fillLineHorizontalVtx(std::vector<glm::vec2> &points);

void fillRightArrowVtx(std::vector<glm::vec2> &points);
void fillLeftArrowVtx(std::vector<glm::vec2> &points);

void fillLetterVtx(std::vector<glm::vec2> &points, std::string letter);

#endif /* VertexGeo_hpp */
