#include <SFML/Graphics.hpp>

namespace rykvlv{
    struct Brick{
        Brick(float x, float y, sf::Color color);
        sf::RectangleShape shape;
        
        bool isDestroyed {false};
        
        float x();
        float y();
        float left();
        float right();
        float top();
        float bottom();
    };
}
