#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.hpp"


namespace rykvlv {
    class SettingsState : public State{
    public:
        SettingsState(std::shared_ptr<GameData> data);
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        std::shared_ptr<GameData> _data;

        sf::Sprite _background;

    };
}
