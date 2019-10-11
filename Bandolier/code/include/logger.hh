#ifndef TEST_LOGGER_HH
#define TEST_LOGGER_HH

#include <string>
#include <memory>
#include <unordered_map>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Bandolier {
using logger_ptr = std::shared_ptr<spdlog::logger>;

class logging
{
public:
  static
  logger_ptr
  make_logger(const std::string& name);

private:
  inline static
  std::unordered_map<std::string, logger_ptr> sLoggers;

  inline static
  auto mCoreLogger = make_logger("Bandolier");
  inline static
  auto mAppLogger = make_logger("APP");

public:
  static
  logger_ptr
  core();

  static
  logger_ptr
  client();

  static
  logger_ptr
  logger(const std::string& name);
};

}

#endif //TEST_LOGGER_HH
