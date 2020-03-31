#ifndef BANDOLIER_ERRORS_HH
#define BANDOLIER_ERRORS_HH

#include <stdexcept>
#include <string>

#include "logger.hh"
#include <error_handling.hh>

namespace Bandolier::ErrorHandling{

//! @TODO add support for formatted messages
// Currently since the exception constructor does not support formatted messages, we cannot handle this successfully
#define BNDLR_LOG_ERROR(message) ::Bandolier::logging::core()->error((message));
#define BNDLR_LOG_WARN(message) ::Bandolier::logging::core()->warn((message));
#define BNDLR_LOG_TRACE(message) ::Bandolier::logging::core()->trace((message));

#define BNDLR_ASSERT(expression, message) GSW_CHECK_AND(expression, BNDLR_LOG_ERROR(message), message)
#define BNDLR_CHECK(expression, message) GSW_CHECK_AND(expression, BNDLR_LOG_WARN(message), message)
#define BNDLR_CHECK_RV(expression, message, ret) GSW_CHECK_AND(expression, BNDLR_LOG_WARN(message), message)
#define BNDLR_TRACK(expression, message) GSW_CHECK_AND(expression, BNDLR_LOG_TRACE(message), message)

}

#endif //BANDOLIER_ERRORS_HH

