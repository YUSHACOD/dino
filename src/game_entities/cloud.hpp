#ifndef CLOUD_DINO
#define CLOUD_DINO

#include <raylib-cpp.hpp>

#include "../drawable.hpp"

const std::string CloudResourcePath = "./resources/images/sky/cloud.png";

#define CloudPositionCount 9
const raylib::Vector2 CloudPositions[] = {
    raylib::Vector2(80, 400),   raylib::Vector2(280, 280),
    raylib::Vector2(140, 180),  raylib::Vector2(700, 200),
    raylib::Vector2(525, 40),   raylib::Vector2(1060, 150),
    raylib::Vector2(1370, 300), raylib::Vector2(1760, 150),
    raylib::Vector2(1600, 75)};

class Cloud {
  private:

  public:
    Drawable drawable;
    float height;
    float width;

    Cloud();

    ~Cloud();
    
    void draw(raylib::Vector2 pos) {
        this->draw(pos);
    }
    
    void draw() {
        for (int i = 0; i < CloudPositionCount; i += 1) {
            this->drawable.draw(CloudPositions[i]);
        }
    }
};

Cloud::Cloud() : drawable(CloudResourcePath, "") {
    this->width = (float)this->drawable.texture.width;
    this->height = (float)this->drawable.texture.height;
}

Cloud::~Cloud() {}

#endif