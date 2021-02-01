#include <sstream>
#include <iostream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.h"

namespace rykvlv{
    SplashState::SplashState(std::shared_ptr<GameData> data) : _data(data){
        
    }

    void SplashState::Init(){
        _data->assets.LoadTexture("Splash State Background", resourcePath() + SPLASH_SCENE_BACKGROUND_FILEPATH);
        _background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
    }

    void SplashState::HandleInput(){
        sf::Event event;
        
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->window.close();
            }
        }
    }

    void SplashState::Update(float dt){
        if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
            std::cout << "Going to main menu" << std::endl;
            this->_data->machine.AddState(std::unique_ptr<State>(new MainMenuState(this->_data)));
        }
    }

    void SplashState::Draw(float dt){
        _data->window.clear();
//        _data->window.draw(_background);
        _data->window.display();
    }
}
