#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

#include <solvers/rk_solver.hpp>


float funcy(float t, float x){
    return 200 * t;
}

int main(){
    const int screenWidth = 1200;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "winder");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    float t = GetTime();
    Vector2 ballPos = {10, (float)screenHeight/2};

    while(!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(YELLOW);

      rlImGuiBegin();

      solvers::rk4::RK4Solver kutta(0, 10, GetTime(), 0.01, funcy);
      ballPos.x = kutta.solve();

      ImGui::GetIO().IniFilename = nullptr;
      ImGui::Begin("ball position");
      ImGui::Text("%f", ballPos.x);
      ImGui::End();

      rlImGuiEnd();

      DrawCircleV(ballPos, 50, BLACK);
      EndDrawing();
    }
    CloseWindow();

    return 0;


}
