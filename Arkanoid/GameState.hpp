#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.hpp"
#include "Platform.hpp"
#include "Ball.hpp"


namespace rykvlv {
    class GameState : public State{
    public:
        GameState(std::shared_ptr<GameData> data);
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        std::shared_ptr<GameData> _data;

        sf::Sprite _background;
        Platform platform;
        Ball ball;

    };
}
