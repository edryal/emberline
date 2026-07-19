#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "emberline - basic window");

    // ESC is the default, but we'll most probably need that key for closing menus
    SetExitKey(KEY_NULL);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawText("Welcome back partner!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
