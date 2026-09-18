#include "imgui.h"
#include "math/vector.hpp"
#include "physics/rigidbody.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"

int main() {
  const int screenWidth = 1200;
  const int screenHeight = 900;
  InitWindow(screenWidth, screenHeight, "winder");
  SetTargetFPS(60);

  rlImGuiSetup(true);

  float t = GetTime();
  RigidBody2 ballObj(math::Vector2<float>{10, (float)screenHeight / 2},
                     math::Vector2<float>{0, 0}, math::Vector2<float>{0, 0}, t);

  RigidBody2 ballObj2(math::Vector2<float>{20, (float)screenHeight / 2},
                      math::Vector2<float>{0, 0}, math::Vector2<float>{0, 0},
                      t);

  float ak = 50000.0;
  float vk = 0.001;

  while (!WindowShouldClose()) {
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

    Vector2 mousePos = GetMousePosition();
    math::Vector2<float> accel =
        math::Vector2<float>{mousePos.x, mousePos.y} - ballObj.position;
    // accel = Vector2Normalize(accel);
    accel /= ak;
    accel -= vk * ballObj.velocity;
    ballObj.acceleration = accel;
    math::Vector2<float> accel2 = ballObj.position - ballObj2.position;
    accel2 /= ak;
    accel2 -= vk * ballObj2.velocity;
    ballObj2.acceleration = accel2;
    ballObj.time_step(GetTime());
    ballObj2.time_step(GetTime());

    rlImGuiEnd();

    DrawCircleV(Vector2{ballObj.position.x, ballObj.position.y}, 50, BLACK);
    DrawCircleV(Vector2{ballObj2.position.x, ballObj2.position.y}, 50, BLACK);
    EndDrawing();
  }
  CloseWindow();

  return 0;
}
