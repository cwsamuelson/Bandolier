#include <glad/glad.h>
#include <stdexcept>
#include <logger.hh>
#include <fstream>
#include <errors.hh>

#include "open_gl_shader.hh"
#include "../../../vendor/glm/glm/ext.hpp"

namespace Bandolier{

OpenGlShader::OpenGlShader(const std::string& filePath)
{
  auto lastSlashIndex = filePath.find_last_of("/\\");
  auto lastDotIndex = filePath.rfind('.');

  auto nameStartIndex = lastSlashIndex == std::string::npos ? 0 : lastSlashIndex + 1;
  auto nameEndIndex = lastDotIndex == std::string::npos ? filePath.size() : lastDotIndex;

  mName = filePath.substr(nameStartIndex, nameEndIndex - nameStartIndex);

  Compile(PreProcess(ReadFile(filePath)));
}

OpenGlShader::OpenGlShader(std::string name, const std::string& vertexSource, const std::string& fragmentSource)
  : mName(std::move(name))
{
  std::unordered_map<GLenum, std::string> sources{
    {GL_VERTEX_SHADER, vertexSource},
    {GL_FRAGMENT_SHADER, fragmentSource},
  };

  Compile(sources);
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

std::string
OpenGlShader::Name() const
{
  return mName;
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

static GLenum ShaderTypeFromString(const std::string& type)
{
  if(type == "vertex")
  {
    return GL_VERTEX_SHADER;
  }
  else if(type == "fragment" || type == "pixel" || type == "color")
  {
    return GL_FRAGMENT_SHADER;
  }
  else if(type == "geometry")
  {
    return GL_GEOMETRY_SHADER;
  }
  else
  {
    //throw;
  }
  //return GL_TESS_CONTROL_SHADER;
  //return GL_COMPUTE_SHADER;
  //return GL_TESS_EVALUATION_SHADER;
}

std::string
OpenGlShader::ReadFile(const std::string& filePath)
{
  std::string result;
  std::ifstream input(filePath, std::ios::binary);
  if(input)
  {
    input.seekg(0, std::ios::end);
    result.resize(input.tellg());
    input.seekg(0, std::ios::beg);
    input.read(result.data(), result.size());
  }
  else
  {
    //throw;
  }

  return result;
}

std::unordered_map<GLenum, std::string>
OpenGlShader::PreProcess(const std::string& source)
{
  std::unordered_map<GLenum, std::string> sources;

  std::string_view typeToken = "#type";
  auto pos = source.find(typeToken, 0);

  while(pos != std::string::npos)
  {
    auto eol = source.find_first_of("\r\n", pos);
    BNDLR_ASSERT(eol != std::string::npos, "Shader syntax error");
    auto begin = pos + typeToken.size() + 1;
    auto type = source.substr(begin, eol - begin);
    BNDLR_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

    auto nextPos = source.find_first_not_of("\r\n", eol);
    pos = source.find(typeToken, nextPos);
    sources[ShaderTypeFromString(type)] = source.substr(nextPos, pos - (nextPos == std::string::npos ? source.size() - 1 :  nextPos));
  }

  return sources;
}

void
OpenGlShader::Compile(const std::unordered_map<GLenum, std::string>& sources)
{
  GLuint program = glCreateProgram();
  std::vector<GLuint> shaderIDs;

  for(auto [shaderType, shaderSource] : sources)
  {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* source = shaderSource.c_str();

    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

      glDeleteShader(shader);

      logging::core()->error("Shader compilation failure!\n{0}", infoLog.data());

      throw std::runtime_error("Error compiling shader");
    }

    glAttachShader(program, shader);
    shaderIDs.push_back(shader);
  }

  mID = program;

  glLinkProgram(mID);

  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
  if(isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

    glDeleteProgram(program);

    for(auto ID : shaderIDs)
    {
      glDeleteShader(ID);
    }

    logging::core()->error("Shader program failed linking!\n{0}", infoLog.data());

    throw std::runtime_error("Error linking shader program");
  }

  for(auto ID : shaderIDs)
  {
    glDetachShader(mID, ID);
  }
}

}

