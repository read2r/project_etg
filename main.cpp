#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "player.h"

int main()
{
    // window
    const int windowWidth = 800;
    const int windowHeight = 600;
    const char* windowTitle = "Project_ETG";
    InitWindow(windowWidth, windowHeight, windowTitle);

    Player player {windowWidth, windowHeight};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        player.tick(deltaTime);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}