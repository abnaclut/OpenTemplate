#include "VertexBuffer.h"

namespace RenderEngine
{
  VertexBuffer::VertexBuffer(): m_id(0) {}
  VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_id); } //FIXME remove magic number

  VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
  {
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
    return *this;
  }

  VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
  {
    m_id = vertexBuffer.m_id;
    vertexBuffer.m_id = 0;
  }

  void VertexBuffer::init(const void* data, const unsigned int size)
  {
    //FIXME pass flags by vars
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  void VertexBuffer::update(const void* data, const unsigned int size) const
  {
    //FIXME pass flags by vars
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  }
//FIXME pass flags by vars
  void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
  void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
}