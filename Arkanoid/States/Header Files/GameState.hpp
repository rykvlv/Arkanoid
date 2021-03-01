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
        void Pause();
        void Resume();
        
    private:
        std::shared_ptr<GameData> _data;

        sf::RectangleShape _background;
        sf::RectangleShape _pauseBackground;
        sf::Sprite _heart;
        sf::Sprite _bonusSprite;
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
        
        sf::Text _resumeText;
        sf::Text _mainMenuText;
        sf::Text _pointer;
        
        bool _isMerged;
        bool _isPaused;
        bool _isBonusInit;
        int _level;
        int _bonusID;
        int _pointerPosition;
        
        float _tempVelocityXvalue;
        float _tempVelocityYvalue;
        
        template<class T1, class T2> bool _isInteracting(T1&, T2&);
        void _checkCollision(Platform& platform, Ball& ball);
        void _checkCollision(Brick& brick, Ball& ball);
        void _checkCollision(Platform& platform, sf::Sprite& bonus);
        void _mergeBall();
        void _initLevel(int level);
        void _initBonus(float x, float y);
    };
}
