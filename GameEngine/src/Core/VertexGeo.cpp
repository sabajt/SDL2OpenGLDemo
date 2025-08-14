//
//  VertexGeo.cpp
//  GameEngine
//
//  Created by John Saba on 2/23/25.
//

#include "VertexGeo.hpp"

void fillLineVerticalVtx(std::vector<glm::vec2> &points)
{
    points.push_back(glm::vec2(0.0f, 0.0f));
    points.push_back(glm::vec2(0.0f, 1.0f));
}

void fillLineHorizontalVtx(std::vector<glm::vec2> &points)
{
    points.push_back(glm::vec2(0.0f, 0.0f));
    points.push_back(glm::vec2(1.0f, 0.0f));
}

void fillRightArrowVtx(std::vector<glm::vec2> &points)
{
    points.push_back(glm::vec2(-1.0f, -0.5f));
    points.push_back(glm::vec2(0.0f, -0.5f));
    points.push_back(glm::vec2(0.0f, -1.0f));
    points.push_back(glm::vec2(1.0f, 0.0f));
    points.push_back(glm::vec2(0.0f, 1.0f));
    points.push_back(glm::vec2(0.0f, 0.5f));
    points.push_back(glm::vec2(-1.0f, 0.5f));
    points.push_back(glm::vec2(-1.0f, -0.5f));
}

void fillLeftArrowVtx(std::vector<glm::vec2> &points)
{
    points.push_back(glm::vec2(1.0f, -0.5f));
    points.push_back(glm::vec2(0.0f, -0.5f));
    points.push_back(glm::vec2(0.0f, -1.0f));
    points.push_back(glm::vec2(-1.0f, 0.0f));
    points.push_back(glm::vec2(0.0f, 1.0f));
    points.push_back(glm::vec2(0.0f, 0.5f));
    points.push_back(glm::vec2(1.0f, 0.5f));
    points.push_back(glm::vec2(1.0f, -0.5f));
}

void fillLetterVtx(std::vector<glm::vec2> &points, std::string letter)
{
    if (letter == "a")
    {
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
    }
    else if (letter == "b")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -0.5f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 0.5f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
    }
    else if (letter == "c")
    {
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
    else if (letter == "d")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -0.5f));
        points.push_back(glm::vec2(1.0f, 0.5f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
    }
    else if (letter == "e")
    {
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(0.5f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
    else if (letter == "f")
    {
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
    }
    else if (letter == "g")
    {
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
    }
    else if (letter == "h")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
    }
    else if (letter == "i")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
    else if (letter == "j")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
    }
    else if (letter == "k")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
    }
    else if (letter == "l")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
    else if (letter == "m")
    {
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
    else if (letter == "n")
    {
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
    }
    else if (letter == "o")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
    }
    else if (letter == "p")
    {
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
    }
    else if (letter == "q")
    {
        points.push_back(glm::vec2(0.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(0.0f, 1.0f));
        points.push_back(glm::vec2(0.5f, 0.5f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
        points.push_back(glm::vec2(0.5f, 0.5f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(0.0f, -1.0f));
    }
    else if (letter == "r")
    {
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
    else if (letter == "s")
    {
        points.push_back(glm::vec2(-1.0f, 0.5f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -0.5f));
    }
    else if (letter == "t")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 1.0f));
    }
    else if (letter == "u")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
    }
    else if (letter == "v")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
    }
    else if (letter == "w")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
    }
    else if (letter == "x")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
    else if (letter == "y")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(0.0f, 0.0f));
        points.push_back(glm::vec2(0.0f, 1.0f));
    }
    else if (letter == "z")
    {
        points.push_back(glm::vec2(-1.0f, -1.0f));
        points.push_back(glm::vec2(1.0f, -1.0f));
        points.push_back(glm::vec2(-1.0f, 1.0f));
        points.push_back(glm::vec2(1.0f, 1.0f));
    }
}
