#include "GameState.hpp"
#include "DEFINITIONS.h"

namespace rykvlv{
    GameState::GameState(std::shared_ptr<GameData> data) : _data(data){
        
    }

    void GameState::Init(){
        this->_data->assets.LoadTexture("Game Background Texture", resourcePath() + GAME_BACKGROUND_FILEPATH);
        _background.setTexture(this->_data->assets.GetTexture("Game Background Texture"));
        this->ball.shape.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
        this->ball.velocity.x = BALL_VELOCITY;
        this->ball.velocity.y = -BALL_VELOCITY;
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
        }
    }

    void GameState::Update(float dt){
        platform.update();
        ball.update();
    }

    void GameState::Draw(float dt){
        this->_data->window.clear();
        this->_data->window.draw(_background);
        this->_data->window.draw(platform.shape);
        this->_data->window.draw(ball.shape);
        this->_data->window.display();
    }
}
