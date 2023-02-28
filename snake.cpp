#include "snake.hpp"
#include "game.hpp"

SnakeGame s[100];
Fruit fruit;

Snake::Snake() {
    cols = 20;
    lines = 13;
    size = 64;
    width = size * cols;
    height = size * lines;
    direction = 0;
    num = 4;
    timer = 0.f;
    delay = 0.1f;
    fruit.x = fruit.y = 10;
    gameover = false;
    points = 0;

    window.create(sf::VideoMode(width, height), "Snake Game 1.0", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(0,0));

    if (!t1.loadFromFile("./assets/img/bg.png")) {
        std::cout << "Deu erro ao carregar a imagem bg.png" << std::endl;
    }

    if (!t2.loadFromFile("./assets/img/snake.png")) {
        std::cout << "Deu erro ao carregar a imagem snake.png" << std::endl;
    }
    
    if (!t3.loadFromFile("./assets/img/fruta.png")) {
        std::cout << "Deu erro ao carregar a imagem fruta.png" << std::endl;
    };

    sp1.setTexture(t1);
    sp2.setTexture(t2);
    sp3.setTexture(t3);
    spSnakeMov.setTexture(t2);

    if (!font_arial.loadFromFile("./assets/fonts/arial.ttf")){
        std::cout << "Não foi possível carregar a fonte Arial" << std::endl;
    }

    text_points.setFont(font_arial);
    text_points.setFillColor(sf::Color::White);
    text_points.setPosition(0,0);
    text_points.setString("Points : " + std::to_string(points));
}

void Snake::run_game() {
    while( window.isOpen()) {
        sf::Event event;

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (timer > delay) {
            timer = 0;
            collision();
        }

        if (gameover) {
            std::cout << "GAME OVER" << std::endl;
            window.clear(sf::Color::Black);
            window.display();
        } else {
            window.clear();

            //desenhando o fundo da tela
            for (int i{}; i < cols; ++i) {
                for (int j{}; j < lines; ++j){
                    sp1.setPosition(i * size, j * size);
                    window.draw(sp1);
                }
            }

            //desenhando a cobra
            for (int i{}; i < num; ++i) {
                sp2.setPosition(s[i].x * size, s[i].y *size);
                window.draw(sp2);
            }

            //desenhando a fruta 
            sp3.setPosition(fruit.x * size, fruit.y * size);
            window.draw(sp3);
            window.draw(text_points);

            window.display();
        }
    }
}

void Snake::collision() {
    move_snake();
    capture_fruit();
    reposicione_snake();
    intersects();//colision
    //criar condicao para fruta não aparecer no meio da cobra
}

void Snake::move_snake() {

    //movimentando a calda da Snake
    for (int i = num; i > 0; --i) {
        s[i].x = s[i-1].x;
        s[i].y = s[i-1].y;
    }

    //eventos de movimento da snake
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = 2;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction = 3;
    }

    switch (direction)
    {
    case 0:
        s[0].x += 1;
        break;
    case 1:
        s[0].x -= 1;
        break;
    case 2:
        s[0].y -= 1;
        break;
    case 3:
        s[0].y += 1;
        break;
    
    default:
        break;
    }
}

void Snake::reposicione_snake() {
    //quando a cobra passar do final do eixo X posiciona no inicio do eixo
    if (s[0].x > cols) {
        s[0].x = 0;
    }

    //quando a cobra passar do inicio do eixo x posiciona no final do eixo X
    if (s[0].x < 0) {
        s[0].x = cols;
    }

    //quando a cobra passar do final do eixo Y posiciona no inicio do eixo
    if (s[0].y > lines) {
        s[0].y = 0;
    }

    //quando a cobra passar do inicio do eixo Y posiciona no final do eixo X
    if (s[0].y < 0) {
        s[0].y = lines;
    }
}

void Snake::capture_fruit() {
    //quando pegar a fruta reposicionar a fruta em outro ponto da matriz
    if (s[0].x == fruit.x && s[0].y == fruit.y) {
        ++num;
        fruit.x = std::rand() % cols;
        fruit.y = std::rand() % lines;
        points += 10.f; 
        text_points.setString("Pontos: " + std::to_string(points));
    }
}

bool Snake::intersects() {
    //se tocar na mesma calda perde o jogo, loop se posicao zero tocar na calda
    for (int i{}; i < num; ++i) {
        spSnakeMov.setPosition(s[i].x, s[i].y);
        //sp2.setPosition(s[0].x * size, s[0].y *size);

        if (spSnakeMov.getGlobalBounds().intersects(sp2.getGlobalBounds())) {
            // gameover = true;

            std::cout << "CABECA DA COBRA: [" << s[0].x <<','<< s[0].y << ']' << std::endl;
            std::cout << "PARTE DA COBRA: " << s[i].x <<','<< s[i].y << ']' << std::endl;
             std::cout << "Bateu na calda da Snake, você perdeu o jogo" << std::endl;
        }
        
        /*
        if (s[0].x == s[i].x && s[0].y == s[i].y) {
                std::cout << "Bateu na calda da Snake, você perdeu o jogo" << std::endl;
                //gameover = true;
        }
        */
    }
}