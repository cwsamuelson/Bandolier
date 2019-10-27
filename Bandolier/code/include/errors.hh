#ifndef BANDOLIER_ERRORS_HH
#define BANDOLIER_ERRORS_HH

#include <stdexcept>
#include <string>

#include "logger.hh"

namespace Bandolier::ErrorHandling{

//! @TODO add support for formatted messages
// Currently since the exception constructor does not support formatted messages, we cannot handle this successfully
#define BNDLR_LOG_ERROR(message) ::Bandolier::logging::core()->error((message));
#define BNDLR_LOG_WARN(message) ::Bandolier::logging::core()->warn((message));
#define BNDLR_LOG_TRACE(message) ::Bandolier::logging::core()->warn((message));

#define BNDLR_WRAPPER(stuff) do{stuff}while(false);
#define BNDLR_CHECKER(condition, log, error) BNDLR_WRAPPER(if(!(condition)){log;error;})
#define BNDLR_THROW(expression, message) throw ::Bandolier::ErrorHandling::Exception(#expression, message, __FILE__, __LINE__);

#define BNDLR_ASSERT(expression, message) BNDLR_CHECKER(expression, BNDLR_LOG_ERROR(message), BNDLR_THROW(expression, message))
#define BNDLR_CHECK(expression, message) BNDLR_CHECKER(expression, BNDLR_LOG_WARN(message), )
#define BNDLR_CHECK_RV(expression, message, ret) BNDLR_CHECKER(expression, BNDLR_LOG_WARN(message), return ret;)
#define BNDLR_TRACK(expression, message) BNDLR_CHECKER(expression, BNDLR_LOG_TRACE(message), )

class Exception : public std::exception
{
private:
  std::string mMessage;

public:
  Exception(const std::string& expression, const std::string& message, const std::string& fileName, unsigned int lineNumber)
    : mMessage(std::string("\"" + message + "\"" + " occurred when executing the expression: " + expression + " at " + fileName + ":" + std::to_string(lineNumber))
  {}

  [[nodiscard]]
  const char*
  what() const noexcept override
  {
    return mMessage.c_str();
  }
};

}

#endif //BANDOLIER_ERRORS_HH

