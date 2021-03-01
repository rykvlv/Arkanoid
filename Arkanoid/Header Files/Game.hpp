#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

namespace rykvlv{
    struct GameData{
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        int score;
        int lifes;
        int highscore;
        bool isSoundOn;
        bool isMouse;
        int resolution;
        
        void LoadData();
        void SaveData();
        void FindHighscore();
    };

    class Game{
    public:
        Game(std::string title);
    private:
        const float dt = 1.0f/60.0f;
        sf::Clock _clock;
        
        sf::Image icon;
        
        std::shared_ptr<GameData> _data = std::make_shared<GameData>();
        
        void Run();
    };
}
