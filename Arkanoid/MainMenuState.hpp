#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.hpp"
#include "DEFINITIONS.h"

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
        
        sf::Font _font;
        
        sf::Sprite _background;
        sf::Sprite _pointer;
        
        sf::Text _mainText;
        sf::Text _playGameText;
        sf::Text _settngsText;
        
        short _pointerPosition;
    };
}
