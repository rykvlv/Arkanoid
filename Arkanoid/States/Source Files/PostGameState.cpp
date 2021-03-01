#include "PostGameState.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"

namespace rykvlv {
    PostGameState::PostGameState(std::shared_ptr<GameData> data) : _data(data){
        
    }

    void PostGameState::Init(){
        _background.setTexture(this->_data->assets.GetTexture("Main Menu Texture"));
        _statusText.setFont(this->_data->assets.GetFont("Font"));
        _statusText.setCharacterSize(200);
        _statusText.setPosition(570, 90);
        _scoreText.setCharacterSize(90);
        _scoreText.setPosition(844, 490);
        _scoreText.setString("Score:\t" + std::to_string(this->_data->score));
        _scoreText.setFont(this->_data->assets.GetFont("Font"));
        if (this->_data->lifes != 0){
            _statusText.setString("You won!");
            this->_data->FindHighscore();
            this->_data->SaveData();
        } else {
            _statusText.setString("You lost...");
        }
        _highscoreText.setCharacterSize(90);
        _highscoreText.setPosition(700, 410);
        _highscoreText.setString("Highcore:\t" + std::to_string(this->_data->highscore));
        _highscoreText.setFont(this->_data->assets.GetFont("Font"));
        
        _playAgainText.setCharacterSize(70);
        _playAgainText.setFont(this->_data->assets.GetFont("Font"));
        _playAgainText.setPosition(870, 660);
        _playAgainText.setString("play again");
        
        _mainMenuText.setCharacterSize(70);
        _mainMenuText.setFont(this->_data->assets.GetFont("Font"));
        _mainMenuText.setPosition(850, 740);
        _mainMenuText.setString("main menu");
        
        _pointer.setCharacterSize(70);
        _pointer.setFont(_data->assets.GetFont("Font"));
        _pointer.setString(">");
        
        _pointerPosition = 1;
    }

    void PostGameState::HandleInput(){
        sf::Event event;
        
        while (_data->window.pollEvent(event)){
            if (sf::Event::Closed == event.type){
                _data->window.close();
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Down && _pointerPosition < 2){
                _pointerPosition++;
                _pointer.setPosition(840, 735);
            } else if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Up && _pointerPosition > 1){
                _pointerPosition--;
                _pointer.setPosition(840, 655);
            }
            
            if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Enter){
                switch(_pointerPosition){
                    case 1:
                        this->_data->machine.AddState(std::unique_ptr<State>(new GameState(this->_data)));
                        
                        break;
                    case 2:
                        _data->machine.AddState(std::unique_ptr<State>(new MainMenuState(this->_data)));
                        break;
                }
            }
        }
        
        
    }

    void PostGameState::Update(){
        switch(_pointerPosition){
            case 1:
                _pointer.setPosition(800, 655);
                break;
            case 2:
                _pointer.setPosition(800, 735);
                break;
        }
    }

    void PostGameState::Draw(){
        this->_data->window.clear();
        this->_data->window.draw(_background);
        this->_data->window.draw(_statusText);
        this->_data->window.draw(_highscoreText);
        this->_data->window.draw(_scoreText);
        this->_data->window.draw(_playAgainText);
        this->_data->window.draw(_mainMenuText);
        this->_data->window.draw(_pointer);
        this->_data->window.display();
    }
}
