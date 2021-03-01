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
        
        this->_pointerText.setString(">");
        
        this->_data->isMouse ? _controllerText.setString("Controller:\tMouse") : _controllerText.setString("Controller:\tKeyboard");
        this->_data->isSoundOn ? _soundText.setString("Sound:\tOn") : _soundText.setString("Sound:\tOff");
        this->_resolutionText.setString("Resolution: ");
        
        this->_backText.setString("Back");
        
        this->_pointerText.setFont(this->_data->assets.GetFont("Font"));
        this->_pointerText.setCharacterSize(80);
        this->_pointerText.setPosition(60, 257);
        
        this->_controllerText.setFont(this->_data->assets.GetFont("Font"));
        this->_controllerText.setCharacterSize(80);
        this->_controllerText.setPosition(120, 260);
        
        this->_soundText.setFont(this->_data->assets.GetFont("Font"));
        this->_soundText.setCharacterSize(80);
        this->_soundText.setPosition(120, 340);
        
        this->_resolutionText.setFont(this->_data->assets.GetFont("Font"));
        this->_resolutionText.setCharacterSize(80);
        this->_resolutionText.setPosition(120, 420);
        
        this->_backText.setFont(this->_data->assets.GetFont("Font"));
        this->_backText.setCharacterSize(80);
        this->_backText.setPosition(120, 600);
        
        this->_pointerPosition = 1;
    }

    void SettingsState::HandleInput(){
        sf::Event event;
        
        while (this->_data->window.pollEvent(event)){
            if (sf::Event::Closed == event.type){
                this->_data->window.close();
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Escape) {
                this->_data->machine.AddState(std::unique_ptr<State>(new MainMenuState(this->_data)));
                this->_data->SaveData();
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Down && _pointerPosition < 4) {
                _pointerPosition++;
            } else if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Up && _pointerPosition > 1) {
                _pointerPosition--;
            }
            
            if (sf::Event::KeyPressed == event.type && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)) {
                switch (_pointerPosition) {
                    case 1:
                        this->_data->isMouse = !this->_data->isMouse;
                        break;
                        
                    case 2:
                        this->_data->isSoundOn = !this->_data->isSoundOn;
                        break;
                }
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Right && _data->resolution < 3 && _pointerPosition == 3){
                _data->resolution++;
            } else if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Left && _data->resolution > 1 && _pointerPosition == 3){
                _data->resolution--;
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Enter && _pointerPosition == 4) {
                this->_data->SaveData();
                this->_data->machine.AddState(std::unique_ptr<State>(new MainMenuState(this->_data)));
            }
        }
    }

    void SettingsState::Update(){
        this->_data->isMouse ? _controllerText.setString("Controller:\tMouse") : _controllerText.setString("Controller:\tKeyboard");
        this->_data->isSoundOn ? _soundText.setString("Sound:\tOn") : _soundText.setString("Sound:\tOff");
        switch (_pointerPosition) {
            case 1:
                _pointerText.setPosition(60, 256);
                break;
            case 2:
                _pointerText.setPosition(60, 336);
                break;
            case 3:
                _pointerText.setPosition(60, 416);
                break;
            case 4:
                _pointerText.setPosition(60, 596);
        }
        switch(_data->resolution){
            case 1:
                _resolutionText.setString("Resolution: 1920x1080");
                break;
            case 2:
                _resolutionText.setString("Resolution: 1280x720");
                break;
            case 3:
                _resolutionText.setString("Resolution: 960x540");
                break;
        }
    }

    void SettingsState::Draw(){
        this->_data->window.clear();
        this->_data->window.draw(_background);
        this->_data->window.draw(_controllerText);
        this->_data->window.draw(_soundText);
        this->_data->window.draw(_backText);
        this->_data->window.draw(_resolutionText);
        this->_data->window.draw(_pointerText);
        this->_data->window.display();
    }
}
