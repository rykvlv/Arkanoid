#include "SettingsState.hpp"
#include "MainMenuState.hpp"

namespace rykvlv{
    SettingsState::SettingsState(std::shared_ptr<GameData> data) : _data(data){
        
    }

    void SettingsState::Init(){
        this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Texture"));
        this->_controllerText.setFont(this->_data->assets.GetFont("Font"));
        this->_soundText.setFont(this->_data->assets.GetFont("Font"));
        this->_resolutionText.setFont(this->_data->assets.GetFont("Font"));
        
        _controllerText.setString("Controller: ");
        _soundText.setString("Sound: ");
        
    }

    void SettingsState::HandleInput(){
        sf::Event event;
        
        while (this->_data->window.pollEvent(event)){
            if (sf::Event::Closed == event.type){
                this->_data->window.close();
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Escape) {
                this->_data->machine.AddState(std::unique_ptr<State>(new MainMenuState(this->_data)));
            }
        }
    }

    void SettingsState::Update(){
        
    }

    void SettingsState::Draw(){
        this->_data->window.clear();
        this->_data->window.draw(_background);
        this->_data->window.display();
    }
}
