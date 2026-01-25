#pragma once
#include "../Includes/includes.h"

#ifndef GLAD_INCLUDED
#include "../../external/glad/include/glad/glad.h"
#define GLAD_INCLUDED
#endif

namespace RenderEngine
{
  class VertexBuffer
  {
  public:
    VertexBuffer();
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;
    VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;
    void init(const void* data, unsigned int size);
    void update(const void* data, unsigned int size) const;
    void bind() const;
    static void unbind();
  private:
    GLuint m_id;
  };
}