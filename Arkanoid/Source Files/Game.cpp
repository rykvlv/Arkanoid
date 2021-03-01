#include "Game.hpp"
#include "DEFINITIONS.h"
#include "MainMenuState.hpp"


namespace rykvlv{
    Game::Game(std::string title){
        try{
        _data->LoadData();
        } catch(nlohmann::json::exception ex){
            _data->SaveData();
        }
        _data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
#ifdef __APPLE__
        if(!icon.loadFromFile(resourcePath() + ICON_FILEPATH)) return;
#else
        if(!icon.loadFromFile(ICON_FILEPATH)) return;
#endif
        
        _data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        switch(_data->resolution){
            case 1:
                _data->window.setSize(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT));
                break;
            case 2:
                _data->window.setSize(sf::Vector2u(SCREEN_WIDTH_2, SCREEN_HEIGHT_2));
                break;
            case 3:
                _data->window.setSize(sf::Vector2u(SCREEN_WIDTH_3, SCREEN_HEIGHT_3));
                break;
        }
        _data->window.setFramerateLimit(60);
        _data->machine.AddState(std::unique_ptr<State>(new MainMenuState(this->_data)));
        this->Run();
    }

    void Game::Run(){
        float newTime, frameTime, interpolation;
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;
        
        while(this->_data->window.isOpen()){
            this->_data->machine.ProccessStateChanges();
            newTime = this->_clock.getElapsedTime().asSeconds();
            frameTime =  newTime - currentTime;
            if (frameTime > 0.25f){
                frameTime = 0.25f;
            }
            currentTime = newTime;
            accumulator += frameTime;
            while (accumulator >= dt) {
                this->_data->machine.GetActiveState()->HandleInput();
                this->_data->machine.GetActiveState()->Update();
                accumulator -= dt;
            }
            interpolation = accumulator / dt;
            this->_data->machine.GetActiveState()->Draw();
        }
    }

    void GameData::LoadData(){
#ifdef __APPLE__
        std::ifstream in(resourcePath() + "data.json");
#else
        std::ifstream in("data.json");
#endif
        nlohmann::json j = nlohmann::json::parse(in);
        in.close();
        if (j["controller"] == "mouse") {
            isMouse = true;
        } else {
            isMouse = false;
        }
        
        if (j["sound"] == "on"){
            isSoundOn = true;
        } else {
            isSoundOn = false;
        }
        
        if (j["resolution"] == 1) {
            resolution = 1;
        } else if (j["resolution"] == 2) {
            resolution = 2;
        } else if (j["resolution"] == 3) {
            resolution = 3;
        }
        
        this->highscore = j["highscore"];
    }

    void GameData::SaveData(){
#ifdef __APPLE__
        std::ofstream out(resourcePath() + "data.json");
#else
        std::ofstream out(resourcePath() + "data.json");
#endif
        nlohmann::json j;
        if (isMouse) {
            j["controller"] = "mouse";
        } else {
            j["controller"] = "keyboard";
        }
        if (isSoundOn) {
            j["sound"] = "on";
        } else {
            j["sound"] = "off";
        }
        
        if (resolution == 1) {
            j["resolution"] = 1;
            window.setSize(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT));
        } else if (resolution == 2) {
            j["resolution"] = 2;
            window.setSize(sf::Vector2u(SCREEN_WIDTH_2, SCREEN_HEIGHT_2));
        } else if (resolution == 3) {
            j["resolution"] = 3;
            window.setSize(sf::Vector2u(SCREEN_WIDTH_3, SCREEN_HEIGHT_3));
        }
        
        j["highscore"] = highscore;
        
        out << j;
        out.close();
    }

    void GameData::FindHighscore(){
        if (this->highscore < this->score)
            highscore = score;
    }
}

