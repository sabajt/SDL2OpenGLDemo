//
//  TextureEntity.hpp
//  GameEngine
//
//  Created by John Saba on 7/24/24.
//

#ifndef TextureEntity_hpp
#define TextureEntity_hpp

#include "Entity.hpp"
#include "Texture.h"
#include <memory.h>

class TextureEntity : public Entity
{
public:
    // TODO: Should constructors be implemented in header (inline)?
    TextureEntity(Vec2 pos = Vec2(0, 0), Vec2 vel = Vec2(0, 0)): Entity(pos, vel) 
    {
        texture_ = std::make_unique<Texture>();
    }
    
    static std::unique_ptr<TextureEntity> createFromFile(std::string fileName, Vec2 pos = Vec2(0, 0), Vec2 vel = Vec2(0, 0))
    {
        auto entity = std::make_unique<TextureEntity>(pos, vel);
        entity->texture_->loadFromFile(fileName, SDL_Color{0, 0xFF, 0, 0xFF});
        
        return entity;
    }
    
    static std::unique_ptr<TextureEntity> createFromText(std::string text, SDL_Color color, Vec2 pos = Vec2(0, 0), Vec2 vel = Vec2(0, 0))
    {
        auto entity = std::make_unique<TextureEntity>(pos, vel);
        if (!entity->texture_->loadFromRenderedText(text, color))
        {
            printf("Failed to render text!\n");
        }
        
        return entity;
    }
    
    virtual void render();
    
private:
    std::unique_ptr<Texture> texture_;
};

#endif /* TextureEntity_hpp */
