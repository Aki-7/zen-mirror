#pragma once

#include "common.h"

namespace zen::display_system::oculus {

struct ILogger {
  // logger singleton set by InitializeLogger;
  static std::unique_ptr<ILogger> instance;

  typedef enum Severity {
    DEBUG = 0,  // logs for debugging during development.
    INFO,       // logs that may be useful to some users.
    WARN,       // logs for recoverable failures.
    ERROR,      // logs for unrecoverable failures.
    FATAL,      // logs when aborting.
    SILENT,     // for internal use only.
  } Severity;

  DISABLE_MOVE_AND_COPY(ILogger);
  ILogger() = default;
  virtual ~ILogger() = default;

  virtual void Print(Severity severity, const char* pretty_function,
      const char* file, int line, const char* format, ...)
      __attribute__((__format__(printf, 6, 7))) = 0;
};

#define LOG_DEBUG(format, ...)                                            \
  ILogger::instance->Print(ILogger::DEBUG, __PRETTY_FUNCTION__, __FILE__, \
      __LINE__, format, ##__VA_ARGS__)

#define LOG_INFO(format, ...)                                            \
  ILogger::instance->Print(ILogger::INFO, __PRETTY_FUNCTION__, __FILE__, \
      __LINE__, format, ##__VA_ARGS__)

#define LOG_WARN(format, ...)                                            \
  ILogger::instance->Print(ILogger::WARN, __PRETTY_FUNCTION__, __FILE__, \
      __LINE__, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...)                                            \
  ILogger::instance->Print(ILogger::ERROR, __PRETTY_FUNCTION__, __FILE__, \
      __LINE__, format, ##__VA_ARGS__)

#define LOG_FATAL(format, ...)                                            \
  ILogger::instance->Print(ILogger::FATAL, __PRETTY_FUNCTION__, __FILE__, \
      __LINE__, format, ##__VA_ARGS__)

void InitializeLogger();

}  // namespace zen::display_system::oculus
