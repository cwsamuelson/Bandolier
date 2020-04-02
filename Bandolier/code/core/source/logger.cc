#include "logger.hh"

namespace Bandolier {

logger_ptr logging::make_logger(const std::string& name, const std::string& pattern, spdlog::level::level_enum lvl) {
  auto lgr = spdlog::stdout_color_mt(name);

  lgr->set_pattern(pattern);
  lgr->set_level(lvl);

  sLoggers[name] = lgr;

  return lgr;
}

logger_ptr logging::core() {
  return mCoreLogger;
}

logger_ptr logging::client() {
  return mAppLogger;
}

logger_ptr logging::logger(const std::string& name) {
  return sLoggers.at(name);
}

}
