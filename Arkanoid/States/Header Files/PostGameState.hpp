#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.hpp"
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
        sf::Text _statusText;
        sf::Text _playAgainText;
        sf::Text _mainMenuText;
        sf::Text _highscoreText;
        sf::Text _scoreText;
        sf::Text _pointer;
        
        int _pointerPosition;
    };
}
