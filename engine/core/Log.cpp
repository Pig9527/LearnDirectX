#include "Log.h"
namespace gfx
{
  std::string Log::getLogLevel(LogLevel level)
  {
    switch (level)
    {
      case LogLevel::Debug: return "DEBUG";
      case LogLevel::Info:  return "INFO";
      case LogLevel::Warn:  return "WARNING";
      case LogLevel::Error: return "ERROR";
      case LogLevel::Fatal: return "FATAL";
      default:              return "UNKNOWN";
    }
  }
  std::string Log::getTimeStamp()
  {
    // auto now = std::chrono::steady_clock::now();
    // auto time_t = std::chrono::system_clock::to_time_t(now);

    // std::tm tm;
    // localtime_s(&tm,&time_t);

    // std::stringstream ss;
    // ss<<std::put_time()


    return std::string("");
  }
}
