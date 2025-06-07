#include <raylib-cpp.hpp>
#include <iostream>
#include <filesystem>

#include "drawable.hpp"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1920;
    int screenHeight = 1080;

    raylib::Color textColor(BLACK);
    raylib::Window w(screenWidth, screenHeight, "Dino");
    w.ToggleFullscreen();
    
    // Test Ground
    //--------------------------------------------------------------------------------------
    Drawable test("resources/images/dinos/dino_idle.png", "");
    raylib::Vector2 pos(190, 200);
    //--------------------------------------------------------------------------------------
    

    // Frame Rate
    //--------------------------------------------------------------------------------------
    SetTargetFPS(60);

    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!w.ShouldClose()) {
        // Update
        //--------------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------

        // Draw
        //--------------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(WHITE);
        textColor.DrawText("THE DINO WILL RISE!", 190, 200,
                           20);
        test.draw(pos);

        EndDrawing();
        //--------------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------

    // End
    //--------------------------------------------------------------------------------------
    w.Close();

    std::filesystem::path current = std::filesystem::current_path();
    std::cout << "Current path: " << current << '\n';
    return 0;
}
