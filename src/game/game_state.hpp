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

const float ObstacleDefaultHeight = 620;

const raylib::Vector2 HiScorePos(1350, 37);
const raylib::Vector2 CurrScorePos(1640, 37);

const int ScoreUpdateFrequency = 2;
const int SpeedUpdateFrequency = 128;

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

    void updateScoreSpeed() {
        this->updateCount += 1;
        
        if ((this->updateCount % ScoreUpdateFrequency) == 0) {
            this->currentScore += 1;
        }
        
        if ((this->updateCount % SpeedUpdateFrequency) == 0) {
            this->updateCount = 0;

            if (reverse) {
                this->ground.scrollSpeed -= 0.25;
            } else {
                this->ground.scrollSpeed += 0.25;
            }
            this->moon.update(this->reverse);
        }
        
        if (this->hiScore > this->currentScore) {
            this->hiScore = this->currentScore;
        }
    }

    void updateCollision() {
        Circle obstacleCircle;
        switch (this->obstacle->getType()) {
            case ObstacleType::Bird:
                obstacleCircle = this->obstacle->getCircle(this->birdAsset);
                break;

            case ObstacleType::BigTree:
                obstacleCircle = this->obstacle->getCircle(this->bigTreeAsset);
                break;

            case ObstacleType::SmallTree:
                obstacleCircle =
                    this->obstacle->getCircle(this->smallTreeAsset);
                break;

            default:
                obstacleCircle = this->obstacle->getCircle(this->birdAsset);
                break;
        }

        const Circle dinoCircle = this->dino.getCircle();

        bool collision =
            CheckCollisionCircles(dinoCircle.center, dinoCircle.radius,
                                  obstacleCircle.center, obstacleCircle.radius);
        
        if (collision) {
            this->dino.changeState(DinoState::Shocked);
            this->gameEnded = true;
        }
    }

    // fn updateObstacles(self : *DinoGameState) void {
    //     switch (self.obstacle) {
    //         Obstacles.Bird => {
    //             self.obstacle_actor.Bird.updateAnimation(
    //                 self.ground.scroll_speed);

    //             const left_bound =
    //                 self.obstacle_actor.Bird.pos.x < -self.bird_asset.width;
    //             const right_bound =
    //                 self.obstacle_actor.Bird.pos.x > self.screen_dimension.x;

    //             const start_position =
    //                 if (Direction == 1) self.screen_dimension.x else -
    //                 self.bird_asset.width;

    //             if (left_bound or right_bound) {
    //                 self.obstacle = obstacle.getRandomObstacle();
    //                 self.obstacle_actor = obstacle.getObstacleActor(
    //                     self.obstacle, start_position, GroundPos, );
    //             }
    //         }
    //         , Obstacles.BigTree => {
    //             self.obstacle_actor.BigTree.updateAnimation(
    //                 self.ground.scroll_speed);

    //             const left_bound = self.obstacle_actor.BigTree.pos.x <
    //                                -self.big_trees_asset.width(
    //                                    self.obstacle_actor.BigTree.state);

    //             const right_bound =
    //                 self.obstacle_actor.BigTree.pos.x > self.screen_dimension.x;

    //             const start_position =
    //                 if (Direction == 1) self.screen_dimension.x else -
    //                 self.big_trees_asset.width(
    //                     self.obstacle_actor.BigTree.state);

    //             if (left_bound or right_bound) {
    //                 self.obstacle = obstacle.getRandomObstacle();
    //                 self.obstacle_actor = obstacle.getObstacleActor(
    //                     self.obstacle, start_position, GroundPos, );
    //             }
    //         }
    //         , Obstacles.SmallTree => {
    //             self.obstacle_actor.SmallTree.updateAnimation(
    //                 self.ground.scroll_speed);

    //             const left_bound = self.obstacle_actor.SmallTree.pos.x <
    //                                -self.small_trees_asset.width;
    //             const right_bound = self.obstacle_actor.SmallTree.pos.x >
    //                                 self.screen_dimension.x;

    //             const start_position =
    //                 if (Direction == 1) self.screen_dimension.x else -
    //                 self.small_trees_asset.width;

    //             if (left_bound or right_bound) {
    //                 self.obstacle = obstacle.getRandomObstacle();
    //                 self.obstacle_actor = obstacle.getObstacleActor(
    //                     self.obstacle, start_position, GroundPos, );
    //             }
    //         }
    //         ,
    //     }
    // }
    void updateObstacles() {
    }
    // ------------------------------------------------------------

    // Draw
    // ------------------------------------------------------------
    void draw() {
        this->drawScenery();

        this->dino.draw();

        this->ground.draw();
        this->drawObstacle();

        if (this->gameEnded) {
            this->gameOverTitle.draw();
        }

        this->hiTitle.draw();
        this->nums.drawScore(this->hiScore, HiScorePos);
        this->nums.drawScore(this->currentScore, CurrScorePos);
    }

    void drawScenery() {
        this->cloud.draw();
        this->stars.draw();
        this->moon.draw();
    }

    void drawObstacle() {
        switch (this->obstacle->getType()) {
            case ObstacleType::Bird:
                this->obstacle->draw(this->birdAsset);
                break;

            case ObstacleType::BigTree:
                this->obstacle->draw(this->bigTreeAsset);
                break;

            case ObstacleType::SmallTree:
                this->obstacle->draw(this->smallTreeAsset);
                break;

            default:
                this->obstacle->draw(this->birdAsset);
                break;
        }
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

    this->obstacle =
        getRandomObstacle((float)screenDimensions.x, ObstacleDefaultHeight);
}

GameState::~GameState() {}

#endif