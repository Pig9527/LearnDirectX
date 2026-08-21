#pragma once
#include "pheader.h"
namespace gfx
{

  enum class LogLevel
  {
    Debug,
    Info,
    Warn,
    Error,
    Fatal
  };

  class Log
  {
  public:
    static Log &Get()
    {
      static Log log;
      return log;
    }

  private:
    Log();
    ~Log();
    Log(const Log& rhs) = delete;
    Log& operator=(const Log& rhs) = delete;

    std::string getLogLevel(LogLevel level);
    std::string getTimeStamp();
  };
} // namespace gfx
