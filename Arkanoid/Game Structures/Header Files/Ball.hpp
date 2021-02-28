#pragma once
#include <SFML/Graphics.hpp>

namespace rykvlv{
    struct Ball{
        Ball();
        sf::Vector2f velocity;
        sf::CircleShape shape;
        
        void update();
        
        float x();
        float y();
        float left();
        float right();
        float top();
        float bottom();
    };
}
