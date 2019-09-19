#ifndef TEST_LOGGER_HH
#define TEST_LOGGER_HH

#include <string>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Bandolier {
using logger_ptr = std::shared_ptr<spdlog::logger>;

namespace detail
{
  logger_ptr
  make_logger(const std::string& name);
}

class logging
{
private:
  inline static auto mCoreLogger = detail::make_logger("Bandolier");
  inline static auto mAppLogger = detail::make_logger("APP");

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
