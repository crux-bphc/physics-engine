#include <iostream>
#include <string>
#include "eqn-solver/eqn-solver.hpp"
#include "raylib.h"
#include <cmath>

double funcy(double t, double x){
    return 100 * std::cos(t);
}


int main(){
    const int screenWidth = 1200;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "winder");
    SetTargetFPS(60);
    Vector2 ballPos = {(double)screenWidth/2, (double)screenHeight/2};

    RenderTexture2D canvas = LoadRenderTexture(1200, 900); //this is for persistence

    BeginTextureMode(canvas);
    ClearBackground(YELLOW);
    EndTextureMode();

    while(!WindowShouldClose()){
	rk4::RK4Solver rk4er(0, (float)screenWidth/2, GetTime(), 0.01, funcy); 
	ballPos.x = rk4er.solve();

	BeginTextureMode(canvas); 
	DrawCircleV({(float)GetTime()*10,(float)screenWidth - ballPos.x}, 4.0, BLACK); //coordinates begin from top left in raylib because idk, also i stretched out the x axis because the t values were too close together  
	EndTextureMode();

	BeginDrawing();
	ClearBackground(YELLOW);
	DrawTextureRec(canvas.texture, { 0, 0, (float)canvas.texture.width, (float)-canvas.texture.height }, { 0, 0 }, WHITE);

	DrawText(("x coordinate (plotted on y) against t: " + std::to_string(ballPos.x)).c_str(), 190, 200, 20, BLACK);
	EndDrawing();

    }
    CloseWindow();

    return 0;


}
