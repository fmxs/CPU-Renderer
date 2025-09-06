#pragma once
#include <cstdio>
#include <cstdarg>
namespace Core {
    inline void LogImpl(const char* level, const char* fmt, ...) {
      std::va_list ap; va_start(ap, fmt);
      std::fprintf(stderr, "[%s] ", level);
      std::vfprintf(stderr, fmt, ap);
      std::fprintf(stderr, "\n");
      va_end(ap);
    }
}
#define LOGI(...) ::Core::LogImpl("I", __VA_ARGS__)
#define LOGW(...) ::Core::LogImpl("W", __VA_ARGS__)
#define LOGE(...) ::Core::LogImpl("E", __VA_ARGS__)
