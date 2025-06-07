#ifndef GAME_OVER_DINO
#define GAME_OVER_DINO

#include <raylib-cpp.hpp>

#include "../drawable.hpp"

const std::string GameOverResourcePath =
    "./resources/images/misc/game_over.png";

const raylib::Vector2 GameOverTitlePos = raylib::Vector2(960, 250);

class GameOver {
  private:
  public:
    Drawable drawable;
    float width;
    float height;

    GameOver();
    ~GameOver();
    
    void draw() {
        this->drawable.draw(GameOverTitlePos);
    }
    
    void draw(raylib::Vector2 pos) {
        this->drawable.draw(pos);
    }
};

GameOver::GameOver() : drawable(GameOverResourcePath, "") {
    this->width = (float)this->drawable.texture.width;
    this->height = (float)this->drawable.texture.height;
}

GameOver::~GameOver() {}

#endif
