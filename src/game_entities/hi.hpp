#ifndef HI_DINO
#define HI_DINO

#include <raylib-cpp.hpp>

#include "../drawable.hpp"
#include "../utils.hpp"

const std::string HiResourcePath = "./resources/images/misc/hi.png";
const raylib::Vector2 HiScoreTitlePos = raylib::Vector2(1300, 37);

class HiScoreTitle {
  private:
  public:
    Drawable drawable;
    float width;
    float height;

    HiScoreTitle();
    ~HiScoreTitle();

    void draw(raylib::Vector2 pos) { this->drawable.draw(pos); }

    void draw() {
        const raylib::Vector2 adjustedPos =
            adjustPosMiddle(HiScoreTitlePos, this->width, this->height);
        this->drawable.draw(adjustedPos);
    }
};

HiScoreTitle::HiScoreTitle() : drawable(HiResourcePath, "") {
    this->width = (float)this->drawable.texture.width;
    this->height = (float)this->drawable.texture.height;
}

HiScoreTitle::~HiScoreTitle() {}

#endif