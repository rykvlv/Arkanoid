#include "Brick.hpp"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "ResourcePath.hpp"

namespace rykvlv{
    Brick::Brick(float x, float y, sf::Color color){
            Brick::shape.setPosition(x, y);
            Brick::shape.setOrigin(BRICK_WIDTH / 2, BRICK_HEIGHT / 2);
            Brick::shape.setFillColor(color);
            Brick::shape.setSize({BRICK_WIDTH, BRICK_HEIGHT});;
    }

    float Brick::x() {
        return Brick::shape.getPosition().x;
    }
    float Brick::y() {
        return Brick::shape.getPosition().y;
    }
    float Brick::left() {
        return x() - shape.getSize().x / 2.f;
    }
    float Brick::right() {
        return x() + shape.getSize().x / 2.f;
    }
    float Brick::top() {
        return y() - shape.getSize().x / 2.f;
    }
    float Brick::bottom() {
        return y() + shape.getSize().y / 2.f;
    }
}
