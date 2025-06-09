#ifndef UTILS_DINO
#define UTILS_DINO

#include <raylib-cpp.hpp>

#include "drawable.hpp"

raylib::Vector2 adjustPosMiddle(raylib::Vector2 pos, float width,
                                float height) {
    const float x = pos.x - (width / 2);
    const float y = pos.y - (height / 2);
    return raylib::Vector2(x, y);
}

raylib::Vector2 adjustPosWidth(raylib::Vector2 pos, float width, float height) {
    const float x = pos.x - (width / 2);
    const float y = pos.y - height;
    return raylib::Vector2(x, y);
}

raylib::Vector2 adjustPosHeight(raylib::Vector2 pos, float height) {
    const float y = pos.y - (height / 2);
    return raylib::Vector2(pos.x, y);
}

raylib::Vector2 adjustPosCircle(raylib::Vector2 pos, float width,
                                float height) {
    const float x = pos.x + (width / 2);
    const float y = pos.y + (height / 2);
    return raylib::Vector2(x, y);
}

void updateWithMousePos(raylib::Vector2 &pos) {
    if (raylib::Mouse::IsButtonDown(MOUSE_BUTTON_LEFT)) {
        const raylib::Vector2 mouse_pos = raylib::Mouse::GetPosition();
        TraceLog(LOG_INFO, "mouse pos %s", mouse_pos.ToString());

        pos.x += mouse_pos.x;
        pos.y += mouse_pos.y;
    }
}

int mod(int a, int b) {
    int result = a % b;
    return (result < 0) ? (result + b) : (result);
}

// Physics helpers
//----------------------------------------------------------------------------------
raylib::Vector2 newVelocity(raylib::Vector2 current_vel, raylib::Vector2 accl,
                            float time_elapsed) {
    float x = current_vel.x + accl.x * time_elapsed;
    float y = current_vel.y + accl.y * time_elapsed;

    return raylib::Vector2(x, y);
}

raylib::Vector2 displacement(raylib::Vector2 current_vel, raylib::Vector2 accl,
                             float time_elapsed) {
    const float time_elapsed_2 = time_elapsed * time_elapsed;

    float x = (current_vel.x * time_elapsed) + (0.5 * accl.x * time_elapsed_2);
    float y = (current_vel.y * time_elapsed) + (0.5 * accl.y * time_elapsed_2);

    return raylib::Vector2(x, y);
}
//----------------------------------------------------------------------------------

#endif