//
//  TextureEntity.cpp
//  GameEngine
//
//  Created by John Saba on 7/24/24.
//

#include "TextureEntity.hpp"

void TextureEntity::render()
{
    // TODO: this converts from float to int... figure out the "right" way
    texture_->render(pos.x, pos.y);
}
