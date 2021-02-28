#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "State.h"
#include "Game.hpp"
#include "Platform.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include "DEFINITIONS.h"

namespace rykvlv {
    class GameState : public State{
    public:
        GameState(std::shared_ptr<GameData> data);
        void Init();
        
        void HandleInput();
        void Update();
        void Draw();
        
    private:
        std::shared_ptr<GameData> _data;

        sf::Sprite _background;
        sf::Sprite _heart;
        sf::Texture _brickTexture;
        Platform platform;
        Ball ball;
        
        sf::Color _colorOne;
        sf::Color _colorTwo;
        sf::Color _colorThree;
        
        std::vector<Brick> _bricks;
        
        sf::Text _scoreText;
        sf::Text _levelText;
        sf::Text _lifesText;
        
        bool _isMerged;
        int _level;
        
        template<class T1, class T2> bool _isInteracting(T1&, T2&);
        void _checkCollision(Platform& platform, Ball& ball);
        void _checkCollision(Brick& brick, Ball& ball);
        void _mergeBall();
        void _initLevel(int level);
    };
}
