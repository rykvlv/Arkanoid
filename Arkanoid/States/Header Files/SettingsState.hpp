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
        void Update();
        void Draw();
        
    private:
        std::shared_ptr<GameData> _data;
        
        sf::Sprite _background;
        
        int _pointerPosition;
        
        sf::Text _pointerText;
        sf::Text _controllerText;
        sf::Text _soundText;
        sf::Text _resolutionText;
        sf::Text _backText;

    };
}
