#include <iostream>
#include <string>
#include <solvers/rksolver.hpp>
#include "raylib.h"

double funcy(double t, double x){
    return 5 * t;
}

int main(){
    const int screenWidth = 1200;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "winder");
    SetTargetFPS(60);
    double t = GetTime();
    Vector2 ballPos = {10, (double)screenHeight/2};

    while(!WindowShouldClose()){
	BeginDrawing();
	ClearBackground(YELLOW);
	solver::euler::EulerSolver oiler(0, 10, GetTime(), 0.01, funcy);
	ballPos.x = oiler.solve();
	DrawCircleV(ballPos, 50, BLACK);
	EndDrawing();

    }
    CloseWindow();

    return 0;


}
