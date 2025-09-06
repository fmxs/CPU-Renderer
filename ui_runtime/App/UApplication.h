#pragma once
#include <string>
struct GLFWwindow;

class UApplication {
public:
  bool Init(int w, int h, const std::string& title);
  void Run();
  void Shutdown();
private:
  GLFWwindow* Win = nullptr;
};
