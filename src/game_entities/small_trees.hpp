#ifndef SMALL_TREES_DINO
#define SMALL_TREES_DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "../drawable.hpp"
#include "../game/obstacle.hpp"
#include "../utils.hpp"

#define SmallTreeCount 6
const std::string SmallTreeResourcePaths[] = {
    "./resources/images/small_tree/small_tree_1.png",
    "./resources/images/small_tree/small_tree_2.png",
    "./resources/images/small_tree/small_tree_3.png",
    "./resources/images/small_tree/small_tree_4.png",
    "./resources/images/small_tree/small_tree_5.png",
    "./resources/images/small_tree/small_tree_6.png"};

class SmallTreeAsset : public Asset {
  private:
  public:
    std::vector<std::unique_ptr<Drawable>> drawables;
    float width;
    float height;

    SmallTreeAsset();
    ~SmallTreeAsset();

    void draw(raylib::Vector2 pos, int state) {
        this->drawables[state]->draw(pos);
    }
};

SmallTreeAsset::SmallTreeAsset() {
    this->drawables.reserve(SmallTreeCount);

    for (int i = 0; i < SmallTreeCount; i += 1) {
        this->drawables.emplace_back(
            std::make_unique<Drawable>(SmallTreeResourcePaths[i], ""));
    }

    this->width = this->drawables[0]->texture.width;
    this->height = this->drawables[0]->texture.height;
}

SmallTreeAsset::~SmallTreeAsset() {}

class SmallTree: public Obstacle {
  private:
  public:
    raylib::Vector2 pos;
    int state;

    SmallTree(float width, float height, int state);
    ~SmallTree();
    
    static int getRandomState() {
        return GetRandomValue(0, SmallTreeCount - 1);
    }

    int getState() {
        return this->state;
    }
    
    raylib::Vector2 getPos() {
        return this->pos;
    }
    
    ObstacleType getType() {
        return ObstacleType::SmallTree;
    }

    void update(float scrollSpeed, float elapsedTime) { this->pos.x -= scrollSpeed; }

    void draw(Asset &asset) {
        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, asset.getWidth(this->state),
                           asset.getHeight(this->state));

        Circle c = this->getCircle(asset);
        DrawCircleV(c.center, c.radius, SKYBLUE);
        asset.draw(adjustedPos, this->state);
    }

    Circle getCircle(Asset &asset) {
        const float width = asset.getWidth(this->state);
        const float height = asset.getHeight(this->state);
        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, width, height);

        const raylib::Vector2 center =
            adjustPosCircle(adjustedPos, width, height);

        const float diameter = (width >= height) ? (height) : (width);

        return Circle{.center = center, .radius = diameter / 2};
    }
};

SmallTree::SmallTree(float width, float height, int state)
    : pos(width, height) {
    this->state = state;
}

SmallTree::~SmallTree() {}

#endif