#pragma once
#include <iostream>
#include "singleton.hpp"
enum LogLevel
{
  trace,
  debug,
  info,
  warning,
  error,
  fatal
};

class Logger : public Singleton<Logger>
{
public:
  static Logger & GetLogger(LogLevel level)
  {
    static Logger logger;
    if (level >= m_Level)
    {
      m_Output = true;
      std::cout << "[" << GetLabel(m_Level) << "] ";
    }
    else m_Output = false;
    return logger;
  }

  static void SetLevel(LogLevel const & type)
  {
    m_Level = type;
  }

  static std::string GetLabel(LogLevel const & type)
  {
    std::string label;
    switch(type)
    {
      case LogLevel::trace:
        label = "trace";
        break;
      case LogLevel::debug:
        label = "debug";
        break;
      case LogLevel::info:
        label = "info";
        break;
      case LogLevel::warning:
        label = "warning";
        break;
      case LogLevel::error:
        label = "error";
        break;
      case LogLevel::fatal:
        label = "fatal";
        break;
      default:
        throw std::invalid_argument("Wrong LogLevel\n");
    }
    return label;
  }

  static Logger & Log(LogLevel const & logLevel,
                  std::string const & message)
  {
    static Logger logger;
    if (logLevel >= m_Level)
    {
      std::cout << message << std::endl;
    }
    return logger;
  }

  static LogLevel GetLogLevel()
  {
    return m_Level;
  }

  template<class T>
  Logger & operator << (T const & obj)
  {
    if (m_Output)
    {
      std::cout << obj;
    }

    return *this;
  }

  template<typename T, template<typename, typename...> class C, typename... Args>
  Logger & operator << (C<T, Args...> const & objs)
  {
    if (m_Output)
    {
      for (auto & obj : objs)
      {
        std::cout << obj << " ";
      }
    }
    return *this;
  }

private:
  friend class Singleton<Logger>;

  Logger() = default;

  static LogLevel m_Level;

  static bool m_Output;
};

LogLevel Logger::m_Level = LogLevel::info;

bool Logger::m_Output = false;
