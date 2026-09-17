#include "math/vector.hpp"

int main() {
  math::Vector2<float> a{1, 1};
  math::Vector2<float> b{2, -1};

  std::cout << (a + b).normalize() << std::endl;
  std::cout << dot(a, b) << std::endl;
  std::cout << (a + b).length() << std::endl;
  std::cout << ((a+b)/3).length() << std::endl;
  std::cout << 1.232*a << std::endl;
}
