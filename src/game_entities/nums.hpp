#ifndef NUMS_DINO
#define NUMS_DINO

#include <iomanip>
#include <raylib-cpp.hpp>
#include <sstream>
#include <memory>

#include "../drawable.hpp"
#include "../utils.hpp"

#define NumCount 10
const std::string NumResourcePaths[] = {
    "./resources/images/nums/0.png", "./resources/images/nums/1.png",
    "./resources/images/nums/2.png", "./resources/images/nums/3.png",
    "./resources/images/nums/4.png", "./resources/images/nums/5.png",
    "./resources/images/nums/6.png", "./resources/images/nums/7.png",
    "./resources/images/nums/8.png", "./resources/images/nums/9.png"};

const int AsciiNumOffset = 48;
const float Spacing = 25;

class Nums {
  private:
  public:
    std::vector<std::unique_ptr<Drawable>> drawables;
    float width;
    float height;

    Nums();
    ~Nums();

    void draw(raylib::Vector2 pos, char c) {
        if (std::isdigit(c)) {
            const int idx = (int)c - AsciiNumOffset;

            this->drawables[idx]->draw(pos);
        } else {
            TraceLog(LOG_ERROR, "Risky Char Bastard: %c\n", c);
        }
    }

    void drawScore(long long score, raylib::Vector2 pos) {
        std::ostringstream oss;
        oss << std::setw(10) << std::setfill('0') << score;

        std::string score_string = oss.str();

        pos = adjustPosHeight(pos, this->height);

        for (int i = 0; i < score_string.size(); i += 1) {
            const raylib::Vector2 digitPos =
                raylib::Vector2(pos.x + (Spacing * (float)i), pos.y);

            this->draw(digitPos, score_string.at(i));
        }
    }
};

Nums::Nums() {
    this->drawables.reserve(NumCount);

    for (int i = 0; i < NumCount; i += 1) {
        this->drawables.emplace_back(std::make_unique<Drawable>(NumResourcePaths[i], ""));
    }

    this->width = (float)this->drawables[0]->texture.width;
    this->height = (float)this->drawables[0]->texture.height;
}

Nums::~Nums() {}

#endif