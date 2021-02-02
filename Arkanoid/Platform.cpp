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

    int Platform::x(){
        return Platform::shape.getPosition().x;
    }

    int Platform::y(){
        return Platform::shape.getPosition().y;
    }

    int Platform::left(){
        return x() - shape.getSize().x / 2;
    }

    int Platform::right(){
        return x() + shape.getSize().x / 2;
    }

    int Platform::top(){
        return y() - shape.getSize().y / 2;
    }

    int Platform::bottom(){
        return y() + shape.getSize().y / 2;
    }
}


