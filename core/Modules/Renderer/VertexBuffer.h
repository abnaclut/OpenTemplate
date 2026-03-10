#pragma once
#ifndef OT_VERTEXBUFFER_H
#define OT_VERTEXBUFFER_H

#include "../Includes/includes.h"

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
#endif // OT_VERTEXBUFFER_H