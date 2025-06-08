#ifndef GAME_STATE_DINO
#define GAME_STATE_DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "../dino.hpp"
#include "../game_entities/big_trees.hpp"
#include "../game_entities/bird.hpp"
#include "../game_entities/cloud.hpp"
#include "../game_entities/game_over.hpp"
#include "../game_entities/ground.hpp"
#include "../game_entities/hi.hpp"
#include "../game_entities/moon.hpp"
#include "../game_entities/nums.hpp"
#include "../game_entities/small_trees.hpp"
#include "../game_entities/stars.hpp"

const raylib::Vector2 HiScorePos(1350, 37);
const raylib::Vector2 CurrScorePos(1640, 37);

std::unique_ptr<Obstacle> getRandomObstacle(float width, float height) {
    const ObstacleType o = getRandomObstacleType();
    int idx = 0;

    switch (o) {
        case ObstacleType::Bird:
            idx = Bird::getRandomState();
            return std::make_unique<Bird>(width, idx);

        case ObstacleType::BigTree:
            idx = BigTree::getRandomState();
            return std::make_unique<BigTree>(width, height, idx);

        case ObstacleType::SmallTree:
            idx = SmallTree::getRandomState();
            return std::make_unique<SmallTree>(width, height, idx);
        
        default:
            idx = Bird::getRandomState();
            return std::make_unique<Bird>(width, idx);
    }
}

class GameState {
  private:
    // Main Game entities
    // ----------------------------
    Dino dino;
    long long hiScore;
    long long currentScore;
    Ground ground;
    Moon moon;
    std::unique_ptr<Obstacle> obstacle;
    // ----------------------------

    // Assets
    // ----------------------------
    Cloud cloud;
    Stars stars;
    Nums nums;
    BirdAsset birdAsset;
    SmallTreeAsset smallTreeAsset;
    BigTreeAsset bigTreeAsset;
    // ----------------------------

    // Text Assets
    // ----------------------------
    HiScoreTitle hiTitle;
    GameOver gameOverTitle;
    // ----------------------------

    // Other fields
    // ----------------------------
    raylib::Vector2 screenDimensions;
    bool gameStarted;
    bool gameEnded;
    bool reverse;
    int updateCount;
    // ----------------------------

  public:
    GameState(bool reverse, raylib::Vector2 screenDimensions);
    ~GameState();

    // Updates
    // ------------------------------------------------------------
    void update() {}
    // ------------------------------------------------------------

    // Draw
    // ------------------------------------------------------------
    void draw() {
        this->cloud.draw();
        this->stars.draw();
    }
    // ------------------------------------------------------------
};

GameState::GameState(bool reverse, raylib::Vector2 screenDimensions)
    : ground(reverse) {
    this->hiScore = 0;
    this->currentScore = 0;
    this->gameStarted = false;
    this->gameEnded = false;
    this->screenDimensions = screenDimensions;
    this->reverse = reverse;
    this->updateCount = 0;

    this->obstacle = getRandomObstacle((float)screenDimensions.x, GroundPos);
}

GameState::~GameState() {}

#endif