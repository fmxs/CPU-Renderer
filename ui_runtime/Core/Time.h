#pragma once
namespace Core {
    struct Time {
      static void Tick();
      static double Now();
      static double Delta();
      static double FpsAvg();
    };
}
