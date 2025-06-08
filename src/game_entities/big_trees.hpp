#ifndef BIG_TREES
#define BIG_TREES

#include <memory>
#include <raylib-cpp.hpp>

#include "../drawable.hpp"
#include "../game/obstacle.hpp"
#include "../utils.hpp"

#define BigTreeCount 5
const std::string BigTreeResourcePaths[] = {
    "./resources/images/big_tree/big_tree_1.png",
    "./resources/images/big_tree/big_tree_2.png",
    "./resources/images/big_tree/big_tree_3.png",
    "./resources/images/big_tree/big_tree_4.png",
    "./resources/images/big_tree/big_tree_5.png"};

class BigTreeAsset {
  private:
  public:
    std::vector<std::unique_ptr<Drawable>> drawables;

    BigTreeAsset();
    ~BigTreeAsset();

    float width(int state) {
        return (float)this->drawables[state]->texture.width;
    }

    float height(int state) {
        return (float)this->drawables[state]->texture.height;
    }

    void draw(raylib::Vector2 pos, int state) {
        this->drawables[state]->draw(pos);
    }
};

BigTreeAsset::BigTreeAsset() {
    this->drawables.reserve(BigTreeCount);

    for (int i = 0; i < BigTreeCount; i += 1) {
        this->drawables.emplace_back(
            std::make_unique<Drawable>(BigTreeResourcePaths[i], ""));
    }
}

BigTreeAsset::~BigTreeAsset() {}

class BigTree {
  private:
  public:
    raylib::Vector2 pos;
    int state;
    BigTree(float ground_height, float width, int state);
    ~BigTree();

    void update(float scroll_speed) { this->pos.x -= scroll_speed; }

    void draw(BigTreeAsset &asset) {
        const float width = asset.width(this->state);
        const float height = asset.height(this->state);

        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, width, height);

        asset.draw(adjustedPos, this->state);
    }

    Circle getCircle(BigTreeAsset &asset) {
        const float width = asset.width(this->state);
        const float height = asset.height(this->state);

        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, width, height);

        const raylib::Vector2 center =
            adjustPosCircle(adjustedPos, width, height);

        const float radius = (width >= height) ? (height) : (width);

        return Circle{.center = center, .radius = radius};
    }
};

BigTree::BigTree(float ground_height, float width, int state)
    : pos(width, ground_height) {
    this->state = state;
}

BigTree::~BigTree() {}

#endif