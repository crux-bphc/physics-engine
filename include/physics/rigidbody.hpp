#include <math/vector.hpp>

class RigidBody2 {
public:
  math::Vector2<float> position, velocity, acceleration;
  float time;

  RigidBody2(math::Vector2<float> pos, math::Vector2<float> vel,
             math::Vector2<float> accel, float t)
      : position(pos), velocity(vel), acceleration(accel), time(t) {}

  void time_step(float t) {
    velocity = velocity + acceleration * (t - time);
    position = position + velocity * (t - time);
  }
};
