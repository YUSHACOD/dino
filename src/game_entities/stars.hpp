#ifndef STARS_DINO
#define STARS_DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "../drawable.hpp"

#define StarStateCount 3
const std::string StarResourcePaths[] = {"./resources/images/sky/star_1.png",
                                         "./resources/images/sky/star_2.png",
                                         "./resources/images/sky/star_3.png"};

#define StarPositionCount 9
const raylib::Vector2 StarPositions[] = {
    raylib::Vector2(364, 185),  raylib::Vector2(1199, 252),
    raylib::Vector2(1017, 36),  raylib::Vector2(717, 87),
    raylib::Vector2(571, 333),  raylib::Vector2(40, 153),
    raylib::Vector2(1501, 216), raylib::Vector2(1743, 406),
    raylib::Vector2(1813, 95),
};

const int StarStates[] = {0, 2, 1, 1, 0, 2, 1, 2, 0};

class Stars {
  private:
  public:
    std::vector<std::unique_ptr<Drawable>> drawables;
    float width;
    float height;

    Stars();
    ~Stars();

    void draw() {
        for (int i = 0; i < StarPositionCount; i += 1) {
            drawables[StarStates[i]]->draw(StarPositions[i]);
        }
    }
};

Stars::Stars() {
    this->drawables.reserve(StarStateCount);

    for (int i = 0; i < StarStateCount; i += 1) {
        this->drawables.emplace_back(
            std::make_unique<Drawable>(StarResourcePaths[i], ""));
    }

    this->width = (float)drawables[0]->texture.width;
    this->height = (float)drawables[0]->texture.height;
}

Stars::~Stars() {}

#endif