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

class SmallTreeAsset {
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

class SmallTree {
  private:
  public:
    raylib::Vector2 pos;
    int state;

    SmallTree(float ground_height, float width, int state);
    ~SmallTree();

    void update(float scroll_speed) { this->pos.x -= scroll_speed; }

    void draw(SmallTreeAsset &asset) {
        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, asset.width, asset.height);

        asset.draw(adjustedPos, this->state);
    }

    Circle getCircle(SmallTreeAsset &asset) {
        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, asset.width, asset.height);

        const raylib::Vector2 center =
            adjustPosCircle(adjustedPos, asset.width, asset.height);

        const float radius =
            (asset.width >= asset.height) ? (asset.height) : (asset.width);

        return Circle{.center = center, .radius = radius};
    }
};

SmallTree::SmallTree(float ground_height, float width, int state)
    : pos(width, ground_height) {
    this->state = state;
}

SmallTree::~SmallTree() {}

#endif