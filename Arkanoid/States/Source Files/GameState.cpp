#include "GameState.hpp"
#include "PostGameState.hpp"
#include <iostream>

namespace rykvlv{
    GameState::GameState(std::shared_ptr<GameData> data) : _data(data){
        this->_colorOne = sf::Color(45, 52, 54);
        this->_colorTwo = sf::Color(99, 110, 114);
        this->_colorThree = sf::Color(178, 190, 195);
    }

    void GameState::Init(){
#ifdef __APPLE__
        this->_data->assets.LoadTexture("Heart Texture", resourcePath() + HEART_FILEPATH);
#else
        this->_data->assets.LoadTexture("Heart Texture", HEART_FILEPATH);
#endif
        this->_scoreText.setFont(this->_data->assets.GetFont("Font"));
        this->_levelText.setFont(this->_data->assets.GetFont("Font"));
        this->_lifesText.setFont(this->_data->assets.GetFont("Font"));
        this->_background.setFillColor(sf::Color(109, 195, 142));
        this->_background.setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
        this->_pauseBackground.setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
        this->_pauseBackground.setFillColor(sf::Color(178, 190, 195, 200));
        this->_heart.setTexture(this->_data->assets.GetTexture("Heart Texture"));
        this->_scoreText.setCharacterSize(70);
        this->_levelText.setCharacterSize(70);
        this->_lifesText.setCharacterSize(70);
        this->_scoreText.setPosition(0, 0);
        this->_levelText.setPosition(850, 0);
        this->_lifesText.setPosition(1720, 0);
        this->_heart.setPosition(1820, 15);
        this->_mergeBall();
        this->_data->lifes = 3;
        this->_data->score = 0;
        this->_level = 1;
        this->_initLevel(_level);
        this->_isPaused = false;
        this->_isBonusInit = false;
        this->_tempVelocityXvalue = 0.0f;
        this->_tempVelocityYvalue = 0.0f;
        this->_data->score = 0;
        
        this->_resumeText.setCharacterSize(70);
        this->_resumeText.setFont(this->_data->assets.GetFont("Font"));
        this->_resumeText.setString("resume");
        this->_resumeText.setPosition(840, 400);
        
        this->_mainMenuText.setCharacterSize(70);
        this->_mainMenuText.setFont(this->_data->assets.GetFont("Font"));
        this->_mainMenuText.setString("main menu");
        this->_mainMenuText.setPosition(800, 470);
        
        this->_pointer.setCharacterSize(70);
        this->_pointer.setFont(this->_data->assets.GetFont("Font"));
        this->_pointer.setString(">");
        this->_pointer.setPosition(730, 395);
        
        this->_pointerPosition = 1;
    }

    void GameState::HandleInput(){
        sf::Event event;
        
        while(_data->window.pollEvent(event)){
            if (sf::Event::Closed == event.type){
                _data->window.close();
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Escape) {
                if (_isPaused)
                    this->Resume();
                else
                    this->Pause();
            }
            
            if (!_isPaused){
                if(!_data->isMouse){
                    if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Left && platform.left() > 0){
                        platform.velocity.x = -PLATFORM_VELOCITY;
                    } else if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Right && platform.right() < SCREEN_WIDTH){
                        platform.velocity.x = PLATFORM_VELOCITY;
                    } else if (platform.left() < 0){
                        platform.shape.setPosition(PLATFORM_WIDTH / 2, SCREEN_HEIGHT - 50);
                        platform.velocity.x = 0;
                    } else if(platform.right() > SCREEN_WIDTH){
                        platform.shape.setPosition(SCREEN_WIDTH - PLATFORM_WIDTH / 2, SCREEN_HEIGHT - 50);
                        platform.velocity.x = 0;
                    }else {
                        platform.velocity.x = 0;
                    }
                } else {
                    platform.shape.setPosition(sf::Mouse::getPosition(this->_data->window).x * SCREEN_WIDTH/(this->_data->window.getSize().x), SCREEN_HEIGHT - 50);
                    
                }
            
                if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Space && _isMerged) {
                    _isMerged = false;
                    ball.velocity.y = -BALL_VELOCITY;
                    ball.velocity.x = 0;
                }
            } else {
                if (sf::Event::KeyPressed == event.type && sf::Keyboard::Down == event.key.code && _pointerPosition < 2){
                    _pointerPosition++;
                } else if (sf::Event::KeyPressed == event.type && sf::Keyboard::Up == event.key.code && _pointerPosition > 1){
                    _pointerPosition--;
                }
                
                if (sf::Event::KeyPressed == event.type && sf::Keyboard::Enter == event.key.code){
                    switch (_pointerPosition){
                        case 1:
                            Resume();
                            break;
                        case 2:
                            this->_data->machine.AddState(std::unique_ptr<State>(new MainMenuState(this->_data)));
                            break;
                    }
                }
            }
        }
    }

    void GameState::Update(){
        srand(time(NULL));
        if (_isMerged){
            ball.shape.setPosition(platform.x(), platform.y() - 2 * BALL_RADIUS);
        }
        platform.update();
        ball.update();
        
        if(_isBonusInit){
            _bonusSprite.move(0, 3.0f);
        }
        
        _checkCollision(platform, ball);
        _checkCollision(platform, _bonusSprite);
        for (int i = 0; i < _bricks.size(); i++){
            _checkCollision(_bricks[i], this->ball);
            if(_bricks[i].isDestroyed){
                if (_bricks[i].shape.getFillColor() == _colorOne){
                    this->_data->score += 10;
                } else if (_bricks[i].shape.getFillColor() == _colorTwo){
                    this->_data->score += 20;
                } else if (_bricks[i].shape.getFillColor() == _colorThree){
                    this->_data->score += 30;
                }
                if (rand()%100 <= 10 && _isBonusInit == false){
                    _initBonus(_bricks[i].shape.getPosition().x, _bricks[i].shape.getPosition().y);
                }
                _bricks.erase(_bricks.begin() + i);
            }
        }
        
        _scoreText.setString("Score: " + std::to_string(this->_data->score));
        _levelText.setString("Level: " + std::to_string(_level));
        _lifesText.setString(std::to_string(this->_data->lifes) + "x");
        
        if (ball.y() > SCREEN_HEIGHT){
            this->_data->lifes--;
            this->_mergeBall();
        }
        
        if (_bricks.empty()){
            if (_level != 2){
                _level++;
                this->_mergeBall();
                this->_initLevel(this->_level);
            } else {
                this->_data->machine.AddState(std::unique_ptr<State>(new PostGameState(this->_data)));
            }
        }
        
        if (this->_data->lifes == 0)
            this->_data->machine.AddState(std::unique_ptr<State>(new PostGameState(this->_data)));
        
        if (_isPaused){
            switch(_pointerPosition){
                case 1:
                    this->_pointer.setPosition(730, 395);
                    break;
                case 2:
                    this->_pointer.setPosition(730, 475);
                    break;
            }
        }
    }

    void GameState::Pause(){
        this->_tempVelocityXvalue = ball.velocity.x;
        this->_tempVelocityYvalue = ball.velocity.y;
        ball.velocity.x = 0;
        ball.velocity.y = 0;
        this->_isPaused = true;
    }

    void GameState::Resume(){
        ball.velocity.x = this->_tempVelocityXvalue;
        ball.velocity.y = this->_tempVelocityYvalue;
        this->_isPaused = false;
        this->_pointerPosition = 1;
    }

    void GameState::_initBonus(float x, float y){
        _bonusSprite.setPosition(x, y);
        _isBonusInit = true;
        switch(rand()%3){
            case 0:
                _bonusSprite.setTexture(this->_data->assets.GetTexture("Heart Texture"));
                _bonusID = 1;
                break;
            case 1:
                _bonusSprite.setTexture(this->_data->assets.GetTexture("Heart Texture"));
                _bonusID = 1;
                break;
            case 2:
                _bonusSprite.setTexture(this->_data->assets.GetTexture("Heart Texture"));
                _bonusID = 1;
                break;
        }
    }

    void GameState::Draw(){
        this->_data->window.clear();
        this->_data->window.draw(_background);
        this->_data->window.draw(platform.shape);
        this->_data->window.draw(ball.shape);
        for (auto& brick : _bricks) this->_data->window.draw(brick.shape);
        this->_data->window.draw(_scoreText);
        this->_data->window.draw(_levelText);
        this->_data->window.draw(_lifesText);
        this->_data->window.draw(_bonusSprite);
        this->_data->window.draw(_heart);
        if(_isPaused){
            this->_data->window.draw(_pauseBackground);
            this->_data->window.draw(_resumeText);
            this->_data->window.draw(_mainMenuText);
            this->_data->window.draw(_pointer);
        }
        this->_data->window.display();
    }

    template<class T1, class T2> inline bool GameState::_isInteracting(T1& object1, T2& object2){
        return object1.right() > object2.left() && object1.left() < object2.right() && object1.bottom() > object2.top() && object1.top() < object2.bottom();

    }

    void GameState::_checkCollision(Platform &platform, Ball &ball){
        if (!_isInteracting(platform, ball)) return;
        else ball.velocity.y = -BALL_VELOCITY;
        if (ball.x() <= platform.x() * 2.f / 5.f) ball.velocity.x = -BALL_VELOCITY;
        else if (ball.x() < platform.x() - 6.f && ball.x() > platform.x() / 2.f) ball.velocity.x = -BALL_VELOCITY / 2;
        else if (ball.x() > platform.x() + 6.f && ball.x() < platform.x() * 2.f) ball.velocity.x = BALL_VELOCITY / 2;
        else if (ball.x() >= platform.x() * 2.f / 5.f * 4.f) ball.velocity.x = BALL_VELOCITY;
        else ball.velocity.x = 0;
    }

    void GameState::_checkCollision(Brick& brick, Ball& ball){
        if (!_isInteracting(brick, ball)) return;
        brick.isDestroyed = true;

        float overlapLeft{ ball.right() - brick.left() };
        float overlapRight{ brick.right() - ball.left() };
        float overlapTop{ ball.bottom() - brick.top() };
        float overlapBottom{ brick.bottom() - ball.top() };

        bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
        bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

        float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
        float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

        if (abs(minOverlapX) < abs(minOverlapY))
            ball.velocity.x = ballFromLeft ? -BALL_VELOCITY : BALL_VELOCITY;
        else
            ball.velocity.y = ballFromTop ? -BALL_VELOCITY : BALL_VELOCITY;
    }

    void GameState::_checkCollision(Platform &platform, sf::Sprite &bonus){
        if (bonus.getPosition().x < platform.right() && bonus.getPosition().x > platform.left() && bonus.getPosition().y > platform.top() && bonus.getPosition().y < platform.bottom()){
            switch(_bonusID){
                case 1:
                    this->_data->lifes++;
                    break;
            }
            _isBonusInit = false;
            bonus.setPosition(-100, -100);
        } else if (bonus.getPosition().y > SCREEN_HEIGHT){
            _isBonusInit = false;
        }
    }

    void GameState::_mergeBall(){
        this->_isMerged = true;
        ball.shape.setPosition(platform.x(), platform.y() - 2 * BALL_RADIUS);
        ball.velocity.x = 0;
        ball.velocity.y = 0;
    }

    void GameState::_initLevel(int level){
        if (level == 1){
            for (int iX = 0; iX < 15; iX++) {
                for (int iY = 0; iY < 2; iY++) {
                    _bricks.emplace_back(33 + (iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 70, _colorOne);
                }
            }
            for (int iX = 0; iX < 15; iX++) {
                for (int iY = 0; iY < 6 / 3; iY++) {
                    _bricks.emplace_back(33 + (iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 156, _colorTwo);
                }
            }
            for (int iX = 0; iX < 15; iX++) {
                for (int iY = 0; iY < 6 / 3; iY++) {
                    _bricks.emplace_back(33 + (iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 242, _colorThree);
                }
            }
        } else if (level == 2){
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 70, _colorOne);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 244, _colorTwo);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 418, _colorThree);
                }
            }
            
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 1365, (iY + 2) * (BRICK_HEIGHT + 3) + 70, _colorOne);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 1365, (iY + 2) * (BRICK_HEIGHT + 3) + 244, _colorTwo);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 1365, (iY + 2) * (BRICK_HEIGHT + 3) + 418, _colorThree);
                }
            }
            
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 660, (iY + 2) * (BRICK_HEIGHT + 3) + 70, _colorOne);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 660, (iY + 2) * (BRICK_HEIGHT + 3) + 244, _colorTwo);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 660, (iY + 2) * (BRICK_HEIGHT + 3) + 418, _colorThree);
                }
            }
        }
    }
}
