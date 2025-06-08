#ifndef GROUND_DINO
#define GROUND_DINO

#include <raylib-cpp.hpp>

#include "../drawable.hpp"

const std::string GroundResourcePath = "./resources/images/misc/ground.png";
const float ScrollSpeed = 6.0;

const float GroundHeight = 600;

class Ground {
  private:
  public:
    float width;
    float height;
    float width_start = 0.0;
    float scroll_speed;
    bool reverse;
    Drawable drawable;

    Ground(bool reverse);
    ~Ground();

    void draw(raylib::Vector2 pos) { this->drawable.draw(pos); }

    void updateGroundScroll() {
        this->width_start -= this->scroll_speed;

        const float ground_width = this->width;
        if (this->width_start <= -ground_width or
            this->width_start >= ground_width) {
            this->width_start = 0;
        }
    }

    void draw() {
        this->drawable.texture.Draw(
            raylib::Vector2(this->width_start, GroundHeight), 0.0, 1, WHITE);

        float width_start2 = 0;
        if (this->reverse) {
            width_start2 = this->width_start - this->width;
        } else {
            width_start2 = this->width_start + this->width;
        }
        this->drawable.texture.Draw(raylib::Vector2(width_start2, GroundHeight),
                                    0.0, 1, WHITE);
    }
};

Ground::Ground(bool reverse) : drawable(GroundResourcePath, "") {
    this->width = (float)this->drawable.texture.width;
    this->height = (float)this->drawable.texture.height;
    this->reverse = reverse;

    if (reverse) {
        this->scroll_speed = -1 * ScrollSpeed;
    } else {
        this->scroll_speed = ScrollSpeed;
    }
}

Ground::~Ground() {}

#endif