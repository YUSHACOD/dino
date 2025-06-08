#ifndef BIRD_DINO
#define BIRD_DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "../drawable.hpp"
#include "../game/obstacle.hpp"
#include "../utils.hpp"

#define BirdStateCount 2
const std::string BirdResourcePaths[] = {
    "./resources/images/bird/b_wing_down.png",
    "./resources/images/bird/b_wing_up.png"};

const float BirdAnimationSpeed = 0.1;
const float ObstaclePositions[] = {500, 525, 580};

class BirdAsset {
  private:
  public:
    std::vector<std::unique_ptr<Drawable>> drawables;
    float width;
    float height;

    BirdAsset();
    ~BirdAsset();

    void draw(raylib::Vector2 pos, int state) {
        this->drawables[state]->draw(pos);
    }
};

BirdAsset::BirdAsset() {
    this->drawables.reserve(BirdStateCount);

    for (int i = 0; i < BirdStateCount; i += 1) {
        this->drawables.emplace_back(
            std::make_unique<Drawable>(BirdResourcePaths[i], ""));
    }

    this->width = this->drawables[0]->texture.width;
    this->height = this->drawables[0]->texture.height;
}

BirdAsset::~BirdAsset() {}

class Bird {
  private:
  public:
    raylib::Vector2 pos;
    int state;
    float state_change_time;

    Bird(float max_width, int obstacle_idx);
    ~Bird();

    Circle getCircle(BirdAsset &asset) {
        const raylib::Vector2 adjustedPos =
            adjustPosHeight(this->pos, asset.height);

        const raylib::Vector2 center =
            adjustPosCircle(adjustedPos, asset.width, asset.height);

        const float radius =
            (asset.width >= asset.height) ? (asset.height) : (asset.width);

        return Circle{.center = center, .radius = radius};
    }

    void incrementState() { this->state = (this->state + 1) % BirdStateCount; }

    void update(float scroll_speed, float frameTime) {
        this->state_change_time += frameTime;

        if (this->state_change_time >= BirdAnimationSpeed) {
            this->incrementState();
            this->state_change_time = 0.0;
        }

        this->pos.x -= scroll_speed;
    }

    void draw(BirdAsset &asset) {
        const raylib::Vector2 adjustedPos =
            adjustPosHeight(this->pos, asset.height);

        asset.draw(this->pos, this->state);
    }
};

Bird::Bird(float max_width, int obstacle_idx)
    : pos(max_width, ObstaclePositions[obstacle_idx]) {
    this->state = 0;
    this->state_change_time = 0;
}

Bird::~Bird() {}

#endif