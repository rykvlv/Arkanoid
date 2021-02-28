#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "ResourcePath.hpp"

namespace rykvlv{
    struct GameData{
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
        int score;
        int lifes;
        bool isSoundOn = true;
        bool isMouse = true;
    };

    class Game{
    public:
        Game(int width, int height, std::string title);
    private:
        const float dt = 1.0f/60.0f;
        sf::Clock _clock;
        
        std::shared_ptr<GameData> _data = std::make_shared<GameData>();
        
        void Run();
    };
}
