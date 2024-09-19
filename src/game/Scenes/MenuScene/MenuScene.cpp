#include "MenuScene.h"
#include "../GameScene/GameScene.h"
#include "../../../engine/SceneManager/SceneManager.h"

MenuScene::MenuScene() : selectedButton(0) {}

MenuScene::~MenuScene() {}

void MenuScene::inicializar() {

    gRecursos->loadTexture("menu", "../assets/textures/menu.png");
    gRecursos->loadTexture("butao", "../assets/textures/butao.png");
    gRecursos->loadSons("menu", "../assets/musics/loop.mp3");

    background.setTexture(gRecursos->getTexture("menu"));
    background.setPosition(0, 0);

    for (int i = 0; i < 2; i++) {
        button[i].setTexture(gRecursos->getTexture("butao"));
        button[i].setPosition(495, i * 53 + 10 + 364);
        button[i].setTextureRect(sf::IntRect(0, i * 43, 290, 43));
    }

    music.setBuffer(gRecursos->getSom("menu"));
    music.play();
    music.setLoop(true);

    selecionarBotao(0);
}

void MenuScene::executar() {
    // Lógica adicional, se necessário
}

void MenuScene::renderizar() {
    janela->addDrawable(background, 0);
    for (int i = 0; i < 2; i++) {
        janela->addDrawable(button[i], 1);
    }
    janela->render();
}

void MenuScene::processarEventos(const sf::Event &evento) {
    std::cout << "Processando eventos" << std::endl;
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Up) {
            selecionarBotao((selectedButton + 1) % 2);
        } else if (evento.key.code == sf::Keyboard::Down) {
            selecionarBotao((selectedButton + 1) % 2);
        } else if (evento.key.code == sf::Keyboard::Enter) {
            if (selectedButton == 0) {
                // Trocar para a cena do jogo
                std::cout << "Entrando no game" << std::endl;
                SceneManager::getInstance()->mudarCena(std::make_unique<GameScene>());
            } else if (selectedButton == 1) {
                std::cout << "Entrando nos créditos" << std::endl;
                // Trocar para a cena de créditos
                // SceneManager::getInstance()->mudarCena(std::make_unique<CreditsScene>());
            }
        }
    }
}

void MenuScene::finalizar() {
    music.stop();
}

void MenuScene::selecionarBotao(int index) {
    selectedButton = index;
    for (int i = 0; i < 2; i++) {
        if (i == selectedButton) {
            button[i].setColor(sf::Color::Red); // Destacar o botão selecionado
        } else {
            button[i].setColor(sf::Color::White); // Botões não selecionados em branco
        }
    }
}
