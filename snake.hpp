#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Snake {
    public:
        Snake();
        int cols, lines, size, width, height, direction, num, points;
        bool gameover;
        sf::RenderWindow window;
        sf::Texture t1, t2, t3;
        sf::Sprite sp1, sp2, sp3, spSnakeMov;
        sf::Clock clock;
        sf::Font font_arial;
        sf::Text text_points;
        float timer, delay;

        void run_game();
        void move_snake();
        void reposicione_snake();
        void collision();
        bool intersects();
        void capture_fruit();
};
