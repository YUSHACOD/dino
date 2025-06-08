#ifndef OBSTACLE_DINO
#define OBSTACLE_DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "../drawable.hpp"
#include "../game_entities/big_trees.hpp"
#include "../game_entities/bird.hpp"
#include "../game_entities/small_trees.hpp"

typedef struct Circle {
    raylib::Vector2 center;
    float radius;
};

enum class ObstacleType { Bird, SmallTree, BigTree };

ObstacleType getRandomObstacleType() {
    int obstacle_idx = GetRandomValue(0, 2);

    switch (obstacle_idx) {
        case 0:
            return ObstacleType::Bird;

        case 1:
            return ObstacleType::BigTree;

        case 2:
            return ObstacleType::SmallTree;

        default:
            return ObstacleType::Bird;
    }
}

class Obstacle {
  private:
  public:
    virtual ~Obstacle();
    virtual Circle getCircle(Asset &asset);
    virtual void update(float scrollSpeed, float elapsedTime);
    virtual void draw(Asset &asset);
};

std::unique_ptr<Obstacle> getRandomObstacle(float width, float height) {
    const ObstacleType o = getRandomObstacleType();

    switch (o) {
        case ObstacleType::Bird:
            int idx = Bird::getRandomState();
            return std::make_unique<Obstacle>(new Bird(width, idx));

        case ObstacleType::BigTree:
            int idx = BigTree::getRandomState();
            return std::make_unique<Obstacle>(new BigTree(width, height, idx));

        case ObstacleType::SmallTree:
            int idx = SmallTree::getRandomState();
            return std::make_unique<Obstacle>(
                new SmallTree(width, height, idx));

        default:
            int idx = Bird::getRandomState();
            return std::make_unique<Obstacle>(new Bird(width, idx));
    }
}

#endif