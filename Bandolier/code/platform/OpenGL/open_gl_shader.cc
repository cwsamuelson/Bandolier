#include <glad/glad.h>
#include <stdexcept>
#include <logger.hh>

#include "open_gl_shader.hh"
#include "../../../vendor/glm/glm/ext.hpp"

namespace Bandolier{

OpenGlShader::OpenGlShader(const std::string& vertexSource, const std::string& fragmentSource)
{
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  const GLchar* source = vertexSource.c_str();

  glShaderSource(vertexShader, 1, &source, nullptr);

  glCompileShader(vertexShader);

  GLint isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());

    glDeleteShader(vertexShader);

    logging::core()->error("Vertex shader compilation failure!");
    logging::core()->error("{0}", infoLog.data());

    throw std::runtime_error("Error compiling vertex shader");
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  source = fragmentSource.c_str();

  glShaderSource(fragmentShader, 1, &source, 0);

  glCompileShader(fragmentShader);

  isCompiled = 0;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());

    glDeleteShader(fragmentShader);

    logging::core()->error("Fragment shader compilation failure!");
    logging::core()->error("{0}", infoLog.data());

    throw std::runtime_error("Error compiling fragment shader");
  }

  mID = glCreateProgram();
  GLuint program = mID;

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
  if(isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

    glDeleteProgram(program);

    logging::core()->error("Shader program failed linking");
    logging::core()->error("{0}", infoLog.data());

    throw std::runtime_error("Error linking shader program");  }

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
}

OpenGlShader::~OpenGlShader()
{
  glDeleteProgram(mID);
}

void
OpenGlShader::Bind() const
{
  glUseProgram(mID);
}

void
OpenGlShader::Unbind() const
{
glUseProgram(0);
}

void
OpenGlShader::SetUniform(const std::string& name, int value)
{
  glUniform1i(GetCached(name), value);
}

void
OpenGlShader::SetUniform(const std::string& name, float value)
{
  glUniform1f(GetCached(name), value);
}

void
OpenGlShader::SetUniform(const std::string& name, const glm::vec2& vector)
{
  glUniform2fv(GetCached(name), 1, glm::value_ptr(vector));
}

void
OpenGlShader::SetUniform(const std::string& name, const glm::vec3& vector)
{
  glUniform3fv(GetCached(name), 1, glm::value_ptr(vector));
}

void
OpenGlShader::SetUniform(const std::string& name, const glm::vec4& vector)
{
  glUniform4fv(GetCached(name), 1, glm::value_ptr(vector));
}

void
OpenGlShader::SetUniform(const std::string& name, const glm::mat2& matrix)
{
  glUniformMatrix2fv(GetCached(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void
OpenGlShader::SetUniform(const std::string& name, const glm::mat3& matrix)
{
  glUniformMatrix3fv(GetCached(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void
OpenGlShader::SetUniform(const std::string& name, const glm::mat4& matrix)
{
  glUniformMatrix4fv(GetCached(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

int
OpenGlShader::GetCached(const std::string& name)
{
  if(mUniformCache.count(name) > 0)
  {
    return mUniformCache.at(name);
  }
  else
  {
    int location = glGetUniformLocation(mID, name.c_str());
    mUniformCache.emplace(name, location);
    return location;
  }
}

}

