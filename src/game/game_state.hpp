#ifndef GAME_STATE_DINO
#define GAME_STATE_DINO

#include <raylib-cpp.hpp>
#include <memory>

#include "dino.hpp"

class GameState {
  private:
    // Actors
    // ----------------------------
    Dino dino;
    long long hiScore;
    long long currentScore;
    // ----------------------------
  public:
    GameState();
    ~GameState();
    
    // Updates
    // ------------------------------------------------------------
    void update() {}
    // ------------------------------------------------------------
    
    // Draw 
    // ------------------------------------------------------------
    void draw() {}
    // ------------------------------------------------------------
};

GameState::GameState() {}

GameState::~GameState() {}

#endif