#include "raylib.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    int launchScreenWidth = 1000;
    int launchScreenHeight = 800;
    InitWindow(launchScreenWidth, launchScreenHeight, "emberline - basic window");

    int minGameWidth = 400;
    int minGameHeight = 400;
    SetWindowMinSize(minGameWidth, minGameHeight);

    int maxGameWidth = GetScreenWidth();
    int maxGameHeight = GetScreenHeight();
    SetWindowMaxSize(maxGameWidth, maxGameHeight);

    SetTargetFPS(60);

    Vector3 playerPos = {0.0f, 1.0f, 0.0f};

    Camera3D camera = {};

    // behind and above the player
    camera.position = {playerPos.x, playerPos.y + 3.0f, playerPos.z - 8.0f};
    camera.target = playerPos;

    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // we want to move the camera with our mouse
    DisableCursor();

    // ESC is the default, but we'll most probably need that key for closing menus
    SetExitKey(KEY_NULL);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            playerPos.x += 1 * GetFrameTime() * 5;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            playerPos.x -= 1 * GetFrameTime() * 5;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            playerPos.z -= 1 * GetFrameTime() * 5;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            playerPos.z += 1 * GetFrameTime() * 5;

        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        camera.target = playerPos;

        BeginDrawing();
        {
            ClearBackground(DARKPURPLE);
            BeginMode3D(camera);
            {
                DrawCube(playerPos, 2, 2, 2, WHITE);
                DrawGrid(10, 1.0f);
            }
            EndMode3D();
            DrawText("Welcome back partner!", 190, 200, 20, LIGHTGRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
