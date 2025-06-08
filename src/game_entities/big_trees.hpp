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

class BigTreeAsset : public Asset {
  private:
  public:
    std::vector<std::unique_ptr<Drawable>> drawables;

    BigTreeAsset();
    ~BigTreeAsset();

    float getWidth(int state) {
        return (float)this->drawables[state]->texture.width;
    }

    float getHeight(int state) {
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

class BigTree : public Obstacle {
  private:
  public:
    raylib::Vector2 pos;
    int state;
    BigTree(float width, float height, int state);
    ~BigTree();

    static int getRandomState() { return GetRandomValue(0, BigTreeCount - 1); }

    void update(float scrollSpeed, float elapsedTime) {
        this->pos.x -= scrollSpeed;
    }

    void draw(Asset &asset) {
        const float width = asset.getWidth(this->state);
        const float height = asset.getHeight(this->state);

        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, width, height);

        asset.draw(adjustedPos, this->state);
    }

    Circle getCircle(Asset &asset) {
        const float width = asset.getWidth(this->state);
        const float height = asset.getHeight(this->state);

        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, width, height);

        const raylib::Vector2 center =
            adjustPosCircle(adjustedPos, width, height);

        const float radius = (width >= height) ? (height) : (width);

        return Circle{.center = center, .radius = radius};
    }
};

BigTree::BigTree(float width, float height, int state) : pos(width, height) {
    this->state = state;
}

BigTree::~BigTree() {}

#endif