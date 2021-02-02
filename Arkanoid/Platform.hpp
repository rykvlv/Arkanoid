#pragma once
#include <SFML/Graphics.hpp>

namespace rykvlv{
    struct Platform{
        Platform();
        sf::Vector2f velocity;
        sf::RectangleShape shape;
        
        void update();
        
        int x();
        int y();
        int left();
        int right();
        int top();
        int bottom();
    };
}

