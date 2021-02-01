#include <sstream>
#include <iostream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.h"

namespace rykvlv{
    MainMenuState::MainMenuState(std::shared_ptr<GameData> data) : _data(data){

    }

    void MainMenuState::Init(){
        _data->assets.LoadTexture("Main Menu State Background", resourcePath() + MAIN_MENU_SCENE_BACKGROUND_FILEPATH);
        _background.setTexture(this->_data->assets.GetTexture("Main Menu State Background"));
        
        _data->assets.LoadTexture("Pointer Texture", resourcePath() + POINTER_TEXTURE_FILEPATH);
        _pointer.setTexture(this->_data->assets.GetTexture("Pointer Texture"));
    }

    void MainMenuState::HandleInput(){
        sf::Event event;
        
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->window.close();
            }
        }
    }

    void MainMenuState::Update(float dt){
        if (_clock.getElapsedTime().asSeconds(); > MAIN_MENU_STATE_SHOW_TIME){
            
            std::cout << "Go To Main Menu" << std::endl;
        }
    }

    void MainMenuState::Draw(float dt){
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.display();
    }
}
