#pragma once

#include <cstdio>
#include <format>
#include <string>
#include <utility>

#if defined(_WIN32)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__linux__) || defined(__APPLE__)
#define DEBUG_BREAK() __builtin_trap()
#else
#define DEBUG_BREAK() ((void)0)
#endif

enum TextColor {
  TEXT_COLOR_BLACK,
  TEXT_COLOR_RED,
  TEXT_COLOR_YELLOW,
  TEXT_COLOR_GREEN,
  TEXT_COLOR_BLUE,
  TEXT_COLOR_COUNT
};

template <typename... Args>
void logMessage(const char* prefix,
                TextColor textColor,
                std::format_string<Args...> fmt,
                Args&&... args) {
  static const char* colors[TEXT_COLOR_COUNT] = {
      "\x1b[30m",
      "\x1b[31m",
      "\x1b[33m",
      "\x1b[32m",
      "\x1b[34m",
  };

  const auto msg = std::format(fmt, std::forward<Args>(args)...);
  std::printf("%s%s%s\x1b[0m\n", colors[textColor], prefix, msg.c_str());
}

#define K_TRACE(...) logMessage("[TRACE]: ", TEXT_COLOR_BLUE, __VA_ARGS__)
#define K_WARN(...) logMessage("[WARN]: ", TEXT_COLOR_YELLOW, __VA_ARGS__)
#define K_ERROR(...) logMessage("[ERROR]: ", TEXT_COLOR_RED, __VA_ARGS__)

#define K_ASSERT(cond, ...)                                                                        \
  do {                                                                                             \
    if (!(cond)) {                                                                                 \
      K_ERROR(__VA_ARGS__);                                                                        \
      DEBUG_BREAK();                                                                               \
    }                                                                                              \
  } while (0)
