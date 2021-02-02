#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"
#include <thread>
#include <chrono>
#include <iostream>

namespace rykvlv{
    MainMenuState::MainMenuState(std::shared_ptr<GameData> data) : _data(data){
        
    }

    void MainMenuState::Init(){
        _data->assets.LoadTexture("Main Menu Texture", resourcePath() + MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Pointer Texture", resourcePath() + POINTER_TEXTURE_FILEPATH);
        
        _data->assets.LoadFont("Font", resourcePath() + FONT_FILEPATH);
        
        _background.setTexture(this->_data->assets.GetTexture("Main Menu Texture"));
        _pointer.setTexture(this->_data->assets.GetTexture("Pointer Texture"));
      
        _mainText.setFont(this->_data->assets.GetFont("Font"));
        _mainText.setCharacterSize(120);
        _mainText.setPosition(550, 290);
        _mainText.setString("Arkanoid");
        _playGameText.setFont(this->_data->assets.GetFont("Font"));
        _playGameText.setCharacterSize(70);
        _playGameText.setPosition(640, 450);
        _playGameText.setString("start game");
        _settngsText.setFont(this->_data->assets.GetFont("Font"));
        _settngsText.setCharacterSize(70);
        _settngsText.setPosition(690, 520);
        _settngsText.setString("settings");
        
        _pointerPosition = 1;
    }

    void MainMenuState::HandleInput(){
        sf::Event event;
        
        while (_data->window.pollEvent(event)){
            if (sf::Event::Closed == event.type){
                _data->window.close();
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Down && _pointerPosition <2){
                _pointerPosition++;
            } else if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Up && _pointerPosition > 1){
                _pointerPosition--;
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Enter) {
                switch(_pointerPosition){
                    case 1:
                        _data->machine.AddState(std::unique_ptr<State>(new GameState(this->_data)));
                        break;
                    case 2:
                        _data->machine.AddState(std::unique_ptr<State>(new SettingsState(this->_data)));
                        break;
                }
            }
        }
    }

    void MainMenuState::Update(float dt){
        if (_pointerPosition == 1) {
            _pointer.setPosition(577, 476);
        } else if (_pointerPosition == 2){
            _pointer.setPosition(577, 545);
        }
    }

    void MainMenuState::Draw(float dt){
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_mainText);
        _data->window.draw(_playGameText);
        _data->window.draw(_settngsText);
        _data->window.draw(_pointer);
        _data->window.display();
        
    }
}
