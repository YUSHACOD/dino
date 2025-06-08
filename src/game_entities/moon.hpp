#ifndef MOON_DINO
#define MOON_DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "../drawable.hpp"

#define MoonStates 7
const std::string MoonResourcePaths[] = {"./resources/images/moons/moon_1.png",
                                         "./resources/images/moons/moon_2.png",
                                         "./resources/images/moons/moon_3.png",
                                         "./resources/images/moons/moon_4.png",
                                         "./resources/images/moons/moon_5.png",
                                         "./resources/images/moons/moon_6.png",
                                         "./resources/images/moons/moon_7.png"};

const raylib::Vector2 MoonPos(1291, 103);

class Moon {
  private:
    void incrementState() { this->state = (this->state + 1) % MoonStates; }

    void decrementState() { this->state = (this->state - 1) % MoonStates; }

  public:
    std::vector<std::unique_ptr<Drawable>> drawables;
    int state = 0;
    float width = 0;
    float height = 0;

    Moon();
    ~Moon();

    void update(bool reverse) {
        if (reverse) {
            this->decrementState();
        } else {
            this->incrementState();
        }
    }

    void draw() { this->drawables[this->state]->draw(MoonPos); }

    void draw(raylib::Vector2 pos) { this->drawables[this->state]->draw(pos); }
};

Moon::Moon() {
    this->drawables.reserve(MoonStates);

    for (int i = 0; i < MoonStates; i += 1) {
        this->drawables.emplace_back(
            std::make_unique<Drawable>(MoonResourcePaths[i], ""));
    }

    this->width = (float)this->drawables[0]->texture.width;
    this->height = (float)this->drawables[0]->texture.height;
}

Moon::~Moon() {}

#endif