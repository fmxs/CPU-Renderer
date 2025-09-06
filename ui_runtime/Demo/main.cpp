#include "../App/UApplication.h"
#include "../Core/Log.h"

int main(){
  UApplication app;
  if(!app.Init(1280, 720, "UI-Kit Step1")) return -1;
  app.Run();
  app.Shutdown();
  return 0;
}
