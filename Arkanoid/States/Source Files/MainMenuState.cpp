#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"

namespace rykvlv{
    MainMenuState::MainMenuState(std::shared_ptr<GameData> data) : _data(data){
        
    }

    void MainMenuState::Init(){
#ifdef __APPLE__
        _data->assets.LoadTexture("Main Menu Texture", resourcePath() + MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.LoadFont("Font", resourcePath() + FONT_FILEPATH);
#else
        _data->assets.LoadTexture("Main Menu Texture", MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.LoadFont("Font", FONT_FILEPATH);
#endif
        _background.setTexture(this->_data->assets.GetTexture("Main Menu Texture"));
        _pointer.setFont(this->_data->assets.GetFont("Font"));
        _pointer.setCharacterSize(70);
        _pointer.setString(">");
        _mainText.setFont(this->_data->assets.GetFont("Font"));
        _mainText.setCharacterSize(200);
        _mainText.setPosition(570, 90);
        _mainText.setString("Arkanoid");
        _playGameText.setFont(this->_data->assets.GetFont("Font"));
        _playGameText.setCharacterSize(70);
        _playGameText.setPosition(840, 450);
        _playGameText.setString("start game");
        _settngsText.setFont(this->_data->assets.GetFont("Font"));
        _settngsText.setCharacterSize(70);
        _settngsText.setPosition(890, 520);
        _settngsText.setString("settings");
        
        _pointerPosition = 1;
    }

    void MainMenuState::HandleInput(){
        sf::Event event;
        
        while (_data->window.pollEvent(event)){
            if (sf::Event::Closed == event.type){
                _data->window.close();
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Down && _pointerPosition < 2){
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

    void MainMenuState::Update(){
        switch (_pointerPosition) {
            case 1:
                _pointer.setPosition(777, 451);
                break;
            case 2:
                _pointer.setPosition(777, 522);
                break;
        }
    }

    void MainMenuState::Draw(){
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_mainText);
        _data->window.draw(_playGameText);
        _data->window.draw(_settngsText);
        _data->window.draw(_pointer);
        _data->window.display();
        
    }
}
