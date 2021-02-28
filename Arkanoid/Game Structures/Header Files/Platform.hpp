#pragma once
#include <SFML/Graphics.hpp>

namespace rykvlv{
    struct Platform{
        Platform();
        sf::Vector2f velocity;
        sf::RectangleShape shape;
        
        void update();
        
        float x();
        float y();
        float left();
        float right();
        float top();
        float bottom();
    };
}

