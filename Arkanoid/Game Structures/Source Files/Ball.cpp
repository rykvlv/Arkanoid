#include "Ball.hpp"
#include "DEFINITIONS.h"

namespace rykvlv{
    Ball::Ball(){
        Ball::shape.setFillColor(sf::Color::Yellow);
        Ball::shape.setRadius(BALL_RADIUS);
        Ball::shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    }

    void Ball::update(){
        shape.move(velocity);
        if (left() < 0) velocity.x = BALL_VELOCITY;
        if (right() > SCREEN_WIDTH) velocity.x = -BALL_VELOCITY;
        if (bottom() < 130) velocity.y = BALL_VELOCITY;
    }

    float Ball::x(){
            return Ball::shape.getPosition().x;
        }

    float Ball::y(){
            return Ball::shape.getPosition().y;
        }

    float Ball::left(){
            return x() - BALL_RADIUS;
        }

    float Ball::right(){
            return x() + BALL_RADIUS;
        }

    float Ball::top(){
            return y() - BALL_RADIUS;
    }

    float Ball::bottom(){
        return y() + BALL_RADIUS;
    }
}
