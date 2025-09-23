#include "IndexBuffer.h"

namespace RenderEngine
{
  IndexBuffer::IndexBuffer(): m_id(0), m_count(0) {} //FIXME might be an issue, check in future.
  IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_id); }

  IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
  {
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
    m_count = indexBuffer.m_count;
    indexBuffer.m_count = 0;
    return *this;
  }

  IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
  {
    m_id = indexBuffer.m_id;
    indexBuffer.m_id = 0;
    m_count = indexBuffer.m_count;
    indexBuffer.m_count = 0;
  }

  void IndexBuffer::init(const void* data, const unsigned int count)
  {
    m_count = count;
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    //FIXME hardcoded usage mode and target should be passed as a variable
  }

  void IndexBuffer::bind() const  { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); } //FIXME remove hardcoding
  void IndexBuffer::unbind()      { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); } //FIXME remove hardcoding
  unsigned int IndexBuffer::getCount() const { return m_count; }
}