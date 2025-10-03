#pragma once

#include <glad/glad.h>

namespace RenderEngine
{
  class IndexBuffer
  {
  public:
    IndexBuffer();
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
    IndexBuffer(IndexBuffer&& indexBuffer) noexcept;
    void init(const void* data, unsigned int count);
    void bind() const;
    static void unbind();
    [[nodiscard]] unsigned int getCount() const;
  private:
    GLuint m_id;
    unsigned int m_count;
  };
}