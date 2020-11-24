#ifndef TEST_LOGGER_HH
#define TEST_LOGGER_HH

#include <string>
#include <memory>
#include <unordered_map>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Bandolier {
using logger_ptr = std::shared_ptr<spdlog::logger>;

class logging {
private:
  inline static const std::string default_pattern = "%^[%T] %n: %v%$";

public:
  static logger_ptr make_logger(const std::string& name,
                                const std::string& pattern,
                                spdlog::level::level_enum lvl);
  inline static logger_ptr make_logger(const std::string& name){ return make_logger(name, default_pattern, spdlog::level::trace); }
  inline static logger_ptr make_logger(const std::string& name, const std::string& pattern){ return make_logger(name, pattern, spdlog::level::trace); }
  inline static logger_ptr make_logger(const std::string& name, spdlog::level::level_enum lvl){ return make_logger(name, default_pattern, spdlog::level::trace); }

private:
  inline static std::unordered_map<std::string, logger_ptr> sLoggers;

  inline static auto mCoreLogger = make_logger("Bandolier");
  inline static auto mAppLogger = make_logger("APP");

public:
  static logger_ptr core();

  static logger_ptr client();

  static logger_ptr logger(const std::string& name);
};

}

#endif //TEST_LOGGER_HH
