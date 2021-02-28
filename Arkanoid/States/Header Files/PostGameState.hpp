#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.hpp"
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.h"


namespace rykvlv {
    class PostGameState : public State{
    public:
        PostGameState(std::shared_ptr<GameData> data);
        void Init();
        
        void HandleInput();
        void Update();
        void Draw();
        
    private:
        std::shared_ptr<GameData> _data;

        sf::Sprite _background;
    };
}
