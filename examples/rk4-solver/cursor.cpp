#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"
#include "imgui.h"

class Object {
  public: 
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float time;

    Object(Vector2 pos, Vector2 vel, float t) : position(pos), velocity(vel), time(t), acceleration(Vector2{0, 0}){
    }

    void calculate(float t) {
      velocity = velocity + acceleration * (t-time);
      position = position + velocity * (t-time);
    }
};

int main(){
    const int screenWidth = 1200;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "winder");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    float t = GetTime();
    Object ballObj(Vector2{10, (float)screenHeight/2}, Vector2{0, 0}, t);

    float ak = 50000.0;
    float vk = 0.001;

    while(!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(YELLOW);

      rlImGuiBegin();

      ImGui::GetIO().IniFilename = nullptr;
      ImGui::Begin("ball");
      ImGui::Text("xpos: %f", ballObj.position.x);
      ImGui::Text("xvel: %f", ballObj.velocity.x);
      ImGui::Text("xaccel: %f", ballObj.acceleration.x);
      ImGui::End();

      ImGui::Begin("constants");
      ImGui::SliderFloat("accel", &ak, 10000.0, 10000000.0);
      ImGui::SliderFloat("vel", &vk, 0.0, 0.5);
      ImGui::End();

      Vector2 accel = GetMousePosition() - ballObj.position;
      // accel = Vector2Normalize(accel);
      accel /= ak;
      accel -= vk*ballObj.velocity;
      ballObj.acceleration = accel;

      ballObj.calculate(GetTime());

      rlImGuiEnd();

      DrawCircleV(ballObj.position, 50, BLACK);
      EndDrawing();
    }
    CloseWindow();

    return 0;


}
