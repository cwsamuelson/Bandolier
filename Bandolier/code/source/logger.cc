#include "logger.hh"

namespace Bandolier {

logger_ptr
detail::make_logger(const std::string& name)
{
  auto lgr = spdlog::stdout_color_mt(name);

  lgr->set_pattern("%^[%T] %n: %v%$");
  lgr->set_level(spdlog::level::trace);

  return lgr;
}

logger_ptr
logging::core()
{
  return mCoreLogger;
}

logger_ptr
logging::client()
{
  return mAppLogger;
}

}
