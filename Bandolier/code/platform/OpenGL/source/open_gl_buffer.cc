#include <glad/glad.h>

#include "open_gl_buffer.hh"

namespace Bandolier {

OpenGlVertexBuffer::OpenGlVertexBuffer(const float* vertices, uint32_t size) {
  glCreateBuffers(1, &mID);
  glBindBuffer(GL_ARRAY_BUFFER, mID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGlVertexBuffer::~OpenGlVertexBuffer() {
  glDeleteBuffers(1, &mID);
}

void OpenGlVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void OpenGlVertexBuffer::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/***************
**INDEX BUFFER**
****************/

OpenGlIndexBuffer::OpenGlIndexBuffer(const uint32_t* indices, uint32_t count)
        : mCount(count) {
  glCreateBuffers(1, &mID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGlIndexBuffer::~OpenGlIndexBuffer() {
  glDeleteBuffers(1, &mID);
}

void OpenGlIndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void OpenGlIndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
