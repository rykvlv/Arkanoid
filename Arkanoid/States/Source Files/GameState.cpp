#include "GameState.hpp"
#include "PostGameState.hpp"
#include <thread>

namespace rykvlv{
    GameState::GameState(std::shared_ptr<GameData> data) : _data(data){
        this->_colorOne = sf::Color(45, 52, 54);
        this->_colorTwo = sf::Color(99, 110, 114);
        this->_colorThree = sf::Color(178, 190, 195);
    }

    void GameState::Init(){
        this->_data->assets.LoadTexture("Game Background Texture", resourcePath() + GAME_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Heart Texture", resourcePath() + HEART_FILEPATH);
        this->_data->assets.LoadTexture("Brick Texture", resourcePath() + BRICK_FILEPATH);
        this->_scoreText.setFont(this->_data->assets.GetFont("Font"));
        this->_levelText.setFont(this->_data->assets.GetFont("Font"));
        this->_lifesText.setFont(this->_data->assets.GetFont("Font"));
        this->_background.setTexture(this->_data->assets.GetTexture("Game Background Texture"));
        this->_heart.setTexture(this->_data->assets.GetTexture("Heart Texture"));
        this->_scoreText.setCharacterSize(70);
        this->_levelText.setCharacterSize(70);
        this->_lifesText.setCharacterSize(70);
        this->_scoreText.setPosition(0, 0);
        this->_levelText.setPosition(660, 0);
        this->_lifesText.setPosition(1400, 0);
        this->_heart.setPosition(1500, 15);
        this->_mergeBall();
        this->_data->lifes = 3;
        this->_data->score = 0;
        this->_level = 1;
        this->_initLevel(_level);
        this->_colorOne = sf::Color(45, 52, 54);
        this->_colorTwo = sf::Color(99, 110, 114);
        this->_colorThree = sf::Color(0, 255, 0);
    }

    void GameState::HandleInput(){
        sf::Event event;
        
        while(_data->window.pollEvent(event)){
            if (sf::Event::Closed == event.type){
                _data->window.close();
            }
            
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
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Space && _isMerged) {
                _isMerged = false;
                ball.velocity.y = -BALL_VELOCITY;
                ball.velocity.x = 0;
            }
        }
    }

    void GameState::Update(){
        if (_isMerged){
            ball.shape.setPosition(platform.x(), platform.y() - 2 * BALL_RADIUS);
        }
        platform.update();
        ball.update();
        
        _checkCollision(platform, ball);
        for (int i = 0; i < _bricks.size(); i++){
            _checkCollision(_bricks[i], this->ball);
            if(_bricks[i].isDestroyed)
                _bricks.erase(_bricks.begin() + i);
        }
        
        _scoreText.setString("Score: " + std::to_string(this->_data->score));
        _levelText.setString("Level: " + std::to_string(_level));
        _lifesText.setString(std::to_string(this->_data->lifes) + "x");
        
        if (ball.y() > SCREEN_HEIGHT){
            this->_data->lifes--;
            this->_mergeBall();
        }
        
        if (_bricks.empty()){
            _level++;
        
            this->_initLevel(this->_level);
        }
        
        if (this->_data->lifes == 0)
            this->_data->machine.AddState(std::unique_ptr<State>(new PostGameState(this->_data)));
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
        this->_data->window.draw(_heart);
        this->_data->window.display();
    }

    template<class T1, class T2> bool GameState::_isInteracting(T1& object1, T2& object2){
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

    void GameState::_mergeBall(){
        this->_isMerged = true;
        ball.shape.setPosition(platform.x(), platform.y() - 2 * BALL_RADIUS);
        ball.velocity.x = 0;
        ball.velocity.y = 0;
    }

    void GameState::_initLevel(int level){
        if (level == 1){
            for (int iX = 0; iX < 13; iX++) {
                for (int iY = 0; iY < 2; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 70, _colorOne);
                }
            }
            for (int iX = 0; iX < 13; iX++) {
                for (int iY = 0; iY < 6 / 3; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 156, _colorTwo);
                }
            }
            for (int iX = 0; iX < 13; iX++) {
                for (int iY = 0; iY < 6 / 3; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 242, _colorThree);
                }
            }
        } else if(level == 2){
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 70, sf::Color::Red);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 244, sf::Color::Green);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) - 58, (iY + 2) * (BRICK_HEIGHT + 3) + 418, sf::Color::Blue);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 1044, (iY + 2) * (BRICK_HEIGHT + 3) + 70, sf::Color::Red);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 1044, (iY + 2) * (BRICK_HEIGHT + 3) + 244, sf::Color::Green);
                }
            }
            for (int iX = 0; iX < 4; iX++) {
                for (int iY = 0; iY < 4; iY++) {
                    _bricks.emplace_back((iX + 1) * (BRICK_WIDTH + 3) + 1044, (iY + 2) * (BRICK_HEIGHT + 3) + 418, sf::Color::Blue);
                }
            }
        }
    }
}
