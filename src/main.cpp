#include "raylib.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

    int launchScreenWidth = 1000;
    int launchScreenHeight = 800;
    InitWindow(launchScreenWidth, launchScreenHeight, "emberline - basic window");

    int minGameWidth = 400;
    int minGameHeight = 400;
    SetWindowMinSize(minGameWidth, minGameHeight);

    // Uncapped is like 3-4k fps, yeah better to cap it
    SetTargetFPS(120);

    Vector3 playerPos = {0.0f, 1.0f, 0.0f};
    Vector3 playerSize = {3.0f, 3.0f, 3.0f};
    int movementSpeed = 5;

    RayCollision ray_collision = {};
    ray_collision.distance = 200.0f; 

    Camera3D camera = {};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // behind and above the player
    camera.position = {playerPos.x, playerPos.y + 3.0f, playerPos.z - 8.0f};
    camera.target = playerPos;

    // we want to move the camera with our mouse
    DisableCursor();

    // ESC is the default, but we'll most probably need that key for closing menus
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose()) {
        // GetScreenWidth() returns the current windowWidth, not the monitor max windowWidth
        DrawFPS(GetScreenWidth() - 100, 10);

        // TODO: once we add multiplayer, we'll need to have some kind of tick rate
        // so that physics is consistent for everyone even on different framerates
        //
        // GetFrameTime is delta time since we're looping over frames not seconds
        // we have to make sure that the speed is the same for people that play on
        // 30 fps vs 60 fps, since more fps would mean faster movementSpeed overtime
        if (IsKeyDown(KEY_W))
            playerPos.z -= movementSpeed * GetFrameTime();
        if (IsKeyDown(KEY_A))
            playerPos.x -= movementSpeed * GetFrameTime();
        if (IsKeyDown(KEY_S))
            playerPos.z += movementSpeed * GetFrameTime();
        if (IsKeyDown(KEY_D))
            playerPos.x += movementSpeed * GetFrameTime();

        // CAMERA_THIRD_PERSON comes with wasd and move input handling by default
        // So instead of the camera following the player, we can make make the
        // player follow the camera since it can move around by itself
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // The player position is basically where the camera is looking at
        playerPos = camera.target;

        BeginDrawing();
        {
            ClearBackground(DARKPURPLE);
            BeginMode3D(camera);
            {
                DrawCubeV({0.0f, 1.0f, 0.0f}, playerSize, RED);
                DrawCube(playerPos, 2, 2, 2, WHITE);
                DrawGrid(1000, 1.0f);
            }
            EndMode3D();
            DrawText("Welcome back partner!", 190, 200, 20, LIGHTGRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
