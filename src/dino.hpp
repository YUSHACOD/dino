#ifndef DINO
#define DINO

#include <memory>
#include <raylib-cpp.hpp>

#include "./drawable.hpp"
#include "./game/obstacle.hpp"
#include "./utils.hpp"

#define DinoResourceCount 8
const std::string DinoResourcePaths[] = {
    "./resources/images/dinos/dino_idle.png",
    "./resources/images/dinos/dino_run1.png",
    "./resources/images/dinos/dino_run2.png",
    "./resources/images/dinos/dino_crawl1.png",
    "./resources/images/dinos/dino_crawl2.png",
    "./resources/images/dinos/dino_shocked1.png",
    "./resources/images/dinos/dino_shocked2.png",
    "./resources/images/dinos/dino_blind.png"};

const float GroundPos = 620;
const raylib::Vector2 DinoPos(960, GroundPos);
const float DinoAnimationSpeed = 0.1;

const raylib::Vector2 Gravity(0, 2000);
const raylib::Vector2 JumpVelocity(0, -900);

enum class DinoState { Idle, Running, Crawling, Shocked, Blind };

class Dino {
  private:
  public:
    raylib::Vector2 pos;
    std::vector<std::unique_ptr<Drawable>> drawables;
    raylib::Vector2 velocity;
    float state_change_time;
    bool isJumping;
    DinoState state;
    int state_idx;
    float width;
    float height;

    Dino();
    ~Dino();

    int getUpdateIndex() {
        switch (this->state) {
            case DinoState::Idle:
                return 0;
            case DinoState::Running:
                return 1;
            case DinoState::Crawling:
                return 3;
            case DinoState::Shocked:
                return 5;
            case DinoState::Blind:
                return 7;
            default:
                return 0;
        }
    }

    void changeState(DinoState state) {
        this->state = state;
        this->state_idx = this->getUpdateIndex();

        this->width = (float)this->drawables[this->state_idx]->texture.width;
        this->height = (float)this->drawables[this->state_idx]->texture.height;
    }

    void incrementState() {
        switch (this->state) {
            case DinoState::Idle:
                this->state_idx = 0;
                break;

            case DinoState::Running:
                this->state_idx = (this->state_idx == 1) ? (2) : (1);
                break;

            case DinoState::Crawling:
                this->state_idx = (this->state_idx == 3) ? (4) : (3);
                break;

            case DinoState::Shocked:
                this->state_idx = (this->state_idx == 5) ? (6) : (5);
                break;

            case DinoState::Blind:
                this->state_idx = 7;
                break;

            default:
                break;
        }
    }

    Circle getCircle() {
        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, this->width, this->height);

        const raylib::Vector2 center =
            adjustPosCircle(adjustedPos, this->width, this->height);

        const float radius =
            (this->width >= this->height) ? (this->height) : (this->width);

        return Circle{.center = center, .radius = radius};
    }

    void update(float timeElapsed) {

        if ((this->state != DinoState::Idle || this->isJumping) &&
            (this->state != DinoState::Shocked)) {

            // State Change
            // -------------------------------------------
            this->state_change_time += timeElapsed;
            if (this->state_change_time >= DinoAnimationSpeed) {
                this->incrementState();
                this->state_change_time = 0.0;
            }
            // -------------------------------------------

            // Position Update
            // -------------------------------------------
            // Gravity
            const raylib::Vector2 displace = displacement(this->velocity, Gravity, timeElapsed);
            
            // New Velocity
            this->velocity = newVelocity(this->velocity, Gravity,  timeElapsed);
            this->pos = this->pos.Add(displace);
            // -------------------------------------------

            // Ground Collision
            // -------------------------------------------
            if (this->pos.y >= DinoPos.y) {
                this->pos.y = DinoPos.y;
                this->velocity.x = 0;
                this->velocity.y = 0;
                this->isJumping = false;
                
                if ((this->state != DinoState::Running) && (this->state != DinoState::Crawling)) {
                    this->changeState(DinoState::Running);
                }
            }
            // -------------------------------------------

            // Jump
            // -------------------------------------------
            if ((raylib::Keyboard::IsKeyPressed(KeyboardKey::KEY_SPACE)) && !this->isJumping) {
                this->isJumping = true;
                this->velocity = JumpVelocity;
            }
            
            if ((this->pos.y != DinoPos.y) && (this->state != DinoState::Idle)) {
                this->changeState(DinoState::Idle);
            }
            // -------------------------------------------

            // Crawling
            // -------------------------------------------
            if (!this->isJumping) {
                if (raylib::Keyboard::IsKeyDown(KeyboardKey::KEY_DOWN)){
                    if (this->state != DinoState::Crawling) {
                        this->changeState(DinoState::Crawling);
                    }
                }
                
                if (raylib::Keyboard::IsKeyReleased(KeyboardKey::KEY_DOWN) && (this->state == DinoState::Crawling)) {
                    this->changeState(DinoState::Running);
                }
            }
            // -------------------------------------------
        }
    }

    void draw(raylib::Vector2 pos) {
        this->drawables[this->state_idx]->draw(pos);
    }

    void draw() {
        const raylib::Vector2 adjustedPos =
            adjustPosWidth(this->pos, this->width, this->height);

        this->draw(adjustedPos);
    }
};

Dino::Dino() : pos(DinoPos), velocity(0, 0) {
    this->drawables.reserve(DinoResourceCount);
    this->state_change_time = 0;
    this->isJumping = false;
    this->state = DinoState::Idle;
    this->state_idx = 0;

    for (int i = 0; i < DinoResourceCount; i += 1) {
        this->drawables.emplace_back(
            std::make_unique<Drawable>(DinoResourcePaths[i], ""));
    }

    this->width = this->drawables[0]->texture.width;
    this->height = this->drawables[0]->texture.height;
}

Dino::~Dino() {}

#endif