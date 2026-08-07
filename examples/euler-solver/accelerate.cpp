#include <iostream>
#include <string>
#include <solvers/rk_solver.hpp>
#include "raylib.h"

float funcy(float t, float x){
    return 5 * t;
}

int main(){
    const int screenWidth = 1200;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "winder");
    SetTargetFPS(60);
    float t = GetTime();
    Vector2 ballPos = {10, (float)screenHeight/2};

    while(!WindowShouldClose()){
	BeginDrawing();
	ClearBackground(YELLOW);
	solvers::euler::EulerSolver oiler(0, 10, GetTime(), 0.01, funcy);
	ballPos.x = oiler.solve();
	DrawCircleV(ballPos, 50, BLACK);
	EndDrawing();

    }
    CloseWindow();

    return 0;


}
