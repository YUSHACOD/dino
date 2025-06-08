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

#define ObstaclePostionCount 3
const float ObstaclePositions[] = {500, 525, 580};

class BirdAsset : public Asset {
  private:
  public:
    std::vector<std::unique_ptr<Drawable>> drawables;
    float width;
    float height;

    BirdAsset();
    ~BirdAsset();

    float getWidth(int state) { return width; }

    float getHeight(int state) { return height; }

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

class Bird : public Obstacle {
  private:
  public:
    raylib::Vector2 pos;
    int state;
    float state_change_time;

    Bird(float max_width, int obstacle_idx);
    ~Bird();

    static int getRandomState() {
        return GetRandomValue(0, ObstaclePostionCount - 1);
    }

    Circle getCircle(Asset &asset) {
        const float width = asset.getWidth(this->state);
        const float height = asset.getHeight(this->state);

        const raylib::Vector2 adjustedPos = adjustPosHeight(this->pos, height);

        const raylib::Vector2 center =
            adjustPosCircle(adjustedPos, width, height);

        const float radius = (width >= height) ? (height) : (width);

        return Circle{.center = center, .radius = radius};
    }

    void incrementState() { this->state = (this->state + 1) % BirdStateCount; }

    void update(float scrollSpeed, float elapsedTime) {
        this->state_change_time += elapsedTime;

        if (this->state_change_time >= BirdAnimationSpeed) {
            this->incrementState();
            this->state_change_time = 0.0;
        }

        this->pos.x -= scrollSpeed;
    }

    void draw(Asset &asset) {
        const raylib::Vector2 adjustedPos =
            adjustPosHeight(this->pos, asset.getHeight(this->state));

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