#include "PostGameState.hpp"

namespace rykvlv {
    PostGameState::PostGameState(std::shared_ptr<GameData> data) : _data(data){
        
    }

    void PostGameState::Init(){
        _background.setTexture(this->_data->assets.GetTexture("Main Menu Texture"));
    }

    void PostGameState::HandleInput(){
        
    }

    void PostGameState::Update(){
        
    }

    void PostGameState::Draw(){
        this->_data->window.clear();
        this->_data->window.display();
    }
}
