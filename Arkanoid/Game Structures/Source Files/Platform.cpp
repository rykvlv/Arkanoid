#include "Platform.hpp"
#include "DEFINITIONS.h"

namespace rykvlv{
    Platform::Platform(){
        Platform::shape.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);
        Platform::shape.setFillColor(sf::Color::Black);
        Platform::shape.setSize({PLATFORM_WIDTH, PLATFORM_HEIGHT});
        Platform::shape.setOrigin(PLATFORM_WIDTH / 2, PLATFORM_HEIGHT / 2);
        Platform::velocity = {0 ,0};
    }

    void Platform::update(){
        Platform::shape.move(velocity);
    }

    float Platform::x(){
        return Platform::shape.getPosition().x;
    }

    float Platform::y(){
        return Platform::shape.getPosition().y;
    }

    float Platform::left(){
        return x() - shape.getSize().x / 2;
    }

    float Platform::right(){
        return x() + shape.getSize().x / 2;
    }

    float Platform::top(){
        return y() - shape.getSize().y / 2;
    }

    float Platform::bottom(){
        return y() + shape.getSize().y / 2;
    }
}


