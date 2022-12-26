#ifndef LOG_HPP
#define LOG_HPP

#ifndef __EMSCRIPTEN__
#define FMT_HEADER_ONLY
#define FMT_CONSTEVAL
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#else
#include <iostream>
#define FMT_HEADER_ONLY
#define FMT_CONSTEVAL
#include <fmt/format-inl.h>
using namespace std;
#endif

namespace odra {
/////////////////////////////////////////////////
/// @fn l
/// @brief Returns the logger
///        This will be logging to the logs. It uses spdlog to log to file
/// @return Returns the logger.
/////////////////////////////////////////////////
#ifndef __EMSCRIPTEN__
inline spdlog::logger &l() {
  // create color multi threaded logger
  static auto console = spdlog::stdout_color_mt("console");
  static auto err_logger = spdlog::stderr_color_mt("stderr");
  static bool initialized = false;
  if (!initialized) {
//    spdlog::set_pattern("*** [%l] [%H:%M:%S %z] [thread %t] %^%v %$ ***");
    spdlog::set_pattern("*** [%l] [thread %t] %^%v %$ ***");
    initialized = true;
  }

  return *spdlog::get("console");
}
#endif

template<typename T>
inline static void info(const T &msg) {
#ifndef __EMSCRIPTEN__
  l().info(msg);
#else
  cout << fmt::format(msg) << endl;
#endif
}

template<typename FormatString, typename... Args>
inline void info(FormatString &fmt, const Args &... args) {
#ifndef __EMSCRIPTEN__
  l().info(fmt, args...);
#else
  cout << fmt::format(fmt, args...) << endl;
#endif
}

template<typename T>
inline static void warn(const T &msg) {
#ifndef __EMSCRIPTEN__
  l().warn(msg);
#else
  cout << fmt::format(msg) << endl;
#endif
}

template<typename FormatString, typename... Args>
inline void warn(const FormatString &fmt, const Args &... args) {
#ifndef __EMSCRIPTEN__
  l().warn(fmt, args...);
#else
  cout << fmt::format(fmt, args...) << endl;
#endif
}

template<typename T>
inline static void debug(const T &msg) {
#ifndef __EMSCRIPTEN__
  l().debug(msg);
#else
  cout << fmt::format(msg) << endl;
#endif
}

template<typename FormatString, typename... Args>
inline void debug(const FormatString &fmt, const Args &... args) {
#ifndef __EMSCRIPTEN__
  l().debug(fmt, args...);
#else
  cout << fmt::format(fmt, args...) << endl;
#endif
}

template<typename T>
inline static void error(const T &msg) {
#ifndef __EMSCRIPTEN__
  l().error(msg);
#else
  cout << fmt::format(msg) << endl;
#endif
}

template<typename FormatString, typename... Args>
inline void error(const FormatString &fmt, const Args &... args) {
#ifndef __EMSCRIPTEN__
  l().error(fmt, args...);
#else
  cout << fmt::format(fmt, args...) << endl;
#endif
}

template<typename T>
inline static void critical(const T &msg) {
#ifndef __EMSCRIPTEN__
  l().critical(msg);
#else
  cout << fmt::format(msg) << endl;
#endif
}

template<typename FormatString, typename... Args>
inline void critical(const FormatString &fmt, const Args &... args) {
#ifndef __EMSCRIPTEN__
  l().critical(fmt, args...);
#else
  cout << fmt::format(fmt, args...) << endl;
#endif
}
}

#endif // LOG_HPP
