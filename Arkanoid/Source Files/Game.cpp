#include "Game.hpp"
#include "SplashState.hpp"

namespace rykvlv{
    Game::Game(int width, int height, std::string title){
        _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
        _data->window.setFramerateLimit(60);
        _data->machine.AddState(std::unique_ptr<State>(new SplashState(this->_data)));
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
}

