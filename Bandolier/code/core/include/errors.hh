#ifndef BANDOLIER_ERRORS_HH
#define BANDOLIER_ERRORS_HH

#include <stdexcept>
#include <string>

#include "logger.hh"
#include <error_handling.hh>

namespace Bandolier::ErrorHandling {

//! @TODO add support for formatted messages
// Currently since the exception constructor does not support formatted messages, we cannot handle this successfully
#define BNDLR_LOG_ERROR(...) ::Bandolier::logging::core()->error((__VA_ARGS__));
#define BNDLR_LOG_WARN(...) ::Bandolier::logging::core()->warn((__VA_ARGS__));
#define BNDLR_LOG_TRACE(...) ::Bandolier::logging::core()->trace((__VA_ARGS__));

#define BNDLR_FAIL(...) GSW_WRAP(BNDLR_LOG_ERROR(__VA_ARGS__); GSW_THROW(__VA_ARGS__))
#define BNDLR_ASSERT(expression, ...) GSW_VERIFY_AND(expression, BNDLR_LOG_ERROR(__VA_ARGS__), __VA_ARGS__)
#define BNDLR_CHECK(expression, ...) GSW_CHECK_AND(expression, BNDLR_LOG_WARN(__VA_ARGS__), __VA_ARGS__)
#define BNDLR_TRACK(expression, ...) GSW_CHECK_AND(expression, BNDLR_LOG_TRACE(__VA_ARGS__), __VA_ARGS__)

#define VERIFY_AND_LOG(cond, ...) GSW_VERIFY_AND(cond, ::Bandolier::logging::core()->error(FMT format(__VA_ARGS__));, __VA_ARGS__);

}

#endif //BANDOLIER_ERRORS_HH

