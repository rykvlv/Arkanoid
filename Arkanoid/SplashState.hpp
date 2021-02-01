#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.hpp"

namespace rykvlv {
    class MainMenuState : public State{
    public:
        MainMenuState(std::shared_ptr<GameData> data);
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        std::shared_ptr<GameData> _data;
        
        sf::Clock _clock;
        sf::Sprite _background;
        sf::Sprite _pointer;
    };
}

