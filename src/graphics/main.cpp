#include <raylib.h>

#include "math/vec.hpp"


#define WINDOW_TITLE "Window title"
constexpr cpe::Vector2<int> SCREEN_SIZE{800, 450};

int main(void)
{
    InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, WINDOW_TITLE);
    SetTargetFPS(60);

    Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); //ts defined in cmakeslists.txt

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        const int texture_x = SCREEN_SIZE.x / 2 - texture.width / 2;
        const int texture_y = SCREEN_SIZE.y / 2 - texture.height / 2;
        DrawTexture(texture, texture_x, texture_y, WHITE);

        const char* text = "CruX BPHC!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, SCREEN_SIZE.x / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}