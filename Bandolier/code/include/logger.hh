#ifndef TEST_LOGGER_HH
#define TEST_LOGGER_HH

#include <string>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Bandolier {
using logger_ptr = std::shared_ptr<spdlog::logger>;

class logging
{
private:
  static
  logger_ptr
  make_logger(const std::string& name);

  inline static auto mCoreLogger = make_logger("Bandolier");
  inline static auto mAppLogger = make_logger("APP");

public:
  static
  logger_ptr
  core();

  static
  logger_ptr
  client();
};

}

#endif //TEST_LOGGER_HH
