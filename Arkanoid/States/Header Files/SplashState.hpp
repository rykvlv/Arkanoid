#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.h"


namespace rykvlv {
    class SplashState : public State{
    public:
        SplashState(std::shared_ptr<GameData> data);
        void Init();
        
        void HandleInput();
        void Update();
        void Draw();
        
    private:
        std::shared_ptr<GameData> _data;
        
        sf::Clock _clock;
        sf::Sprite _background;

    };
}

