#include "gtest/gtest.h"
#include "headerlist.hpp"

TEST(prog_test, logger_test)
{
  Logger::SetLevel(LogLevel::trace);
  Logger::GetLogger(LogLevel::trace) << "trace\n";
  Logger::GetLogger(LogLevel::debug) << "debug\n";
  Logger::GetLogger(LogLevel::info) << "info\n";
  Logger::GetLogger(LogLevel::warning) << "warning\n";
  Logger::GetLogger(LogLevel::fatal) << "fatal\n";
}

TEST(prog_test, logger1_test)
{
  Logger::SetLevel(LogLevel::info);
  Logger::GetLogger(LogLevel::trace) << "trace\n";
  Logger::GetLogger(LogLevel::debug) << "debug\n";
  Logger::GetLogger(LogLevel::info) << "info\n";
  Logger::GetLogger(LogLevel::warning) << "warning\n";
  Logger::GetLogger(LogLevel::fatal) << "fatal\n";
}

TEST(prog_test, logger2_test)
{
  Logger::SetLevel(LogLevel::fatal);
  Logger::GetLogger(LogLevel::trace) << "trace\n";
  Logger::GetLogger(LogLevel::debug) << "debug\n";
  Logger::GetLogger(LogLevel::info) << "info\n";
  Logger::GetLogger(LogLevel::warning) << "warning\n";
  Logger::GetLogger(LogLevel::fatal) << "fatal\n";
}

TEST(prog_test, logger3_test)
{
  Logger::SetLevel(LogLevel::info);
  Logger::GetLogger(LogLevel::info) << 5 << "\n";
  Logger::GetLogger(LogLevel::info) << std::vector<int>{2, 3, 4} << "\n";;
  Logger::GetLogger(LogLevel::info) << std::vector<Bullet>{Bullet({2, 2}, {3, 3}, 10), Bullet()} << "\n";;
}

TEST(prog_test, logger4_test)
{
  Logger::SetLevel(LogLevel::info);
  Logger::Log(LogLevel::trace, "Trace");
  Logger::Log(LogLevel::fatal, "Fatal");
}
