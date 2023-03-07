#include "Game.h"

void Game::play() { initPlayScene(); }
void Game::menu() { initMenuScene(); }

Game::Game(QWidget *parent) : QGraphicsView(parent) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(RESOLUTION_X, RESOLUTION_Y);
    setWindowTitle(GAME_NAME);

    _scene = new QGraphicsScene();
    _game_manager = std::make_unique <GameManager>(_scene);

    setScene(_scene.get());
    initMenuScene();
}

void Game::initMenuScene() {
    initMenuSceneButtons();
    addMenuSceneItems();
}

void Game::addMenuSceneItems() {
    _scene->clear();
    _scene->addItem(_button_quit.get());
    _scene->addItem(_button_play.get());
    _scene->setSceneRect(0, 0, RESOLUTION_X, RESOLUTION_Y);
    setStyleSheet("background-image: url(:/background/menu);");
}

void Game::initMenuSceneButtons() {
    initButton(_button_play, "Play", BUTTON_PLAY_POSITION);
    initButton(_button_quit, "Quit", BUTTON_QUIT_POSITION);
    connect(_button_play.get(), SIGNAL(clicked()), this, SLOT(play()));
    connect(_button_quit.get(), SIGNAL(clicked()), this, SLOT(close()));
}

void Game::initPlayScene() {
    initPlaySceneButtons();
    addPlaySceneItems();
}

void Game::addPlaySceneItems() {
    _scene->clear();
    _scene->setSceneRect(0, 0, RESOLUTION_X, RESOLUTION_Y);
    setStyleSheet("background-image: url(:/background/game);");

    _game_manager->printRandomCard();

    _scene->addItem(_button_menu.get());
}

void Game::initPlaySceneButtons() {
    initButton(_button_menu, "Menu", BUTTON_MENU_POSITION);
    connect(_button_menu.get(), SIGNAL(clicked()), this, SLOT(menu()));
}

void Game::initButton(QPointer<Button> &button,
                      const char *button_text,
                      const int button_height) {
    button = new Button(button_text);
    int button_width = this->width() / 2.0f - button->boundingRect().width() / 2.0f;
    button->setPos(button_width, button_height);
}
