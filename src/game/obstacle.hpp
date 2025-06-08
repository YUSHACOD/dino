#ifndef OBSTACLE_DINO
#define OBSTACLE_DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "../drawable.hpp"

typedef struct Circle {
    raylib::Vector2 center;
    float radius;
} Circle;

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
    virtual Circle getCircle(Asset &asset) {
        return Circle{.center = raylib::Vector2(0, 0), .radius = 0};
    };
    virtual void update(float scrollSpeed, float elapsedTime) {};
    virtual void draw(Asset &asset) {};
};

Obstacle::~Obstacle() = default;

#endif