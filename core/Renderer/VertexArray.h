#pragma once
#ifndef OT_VERTEXARRAY_H
#define OT_VERTEXARRAY_H

#include "../Includes/includes.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace RenderEngine
{
  class VertexArray
  {
  public:
    VertexArray();
    ~VertexArray();
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&& vertexArray) noexcept;
    VertexArray(VertexArray&& vertexArray) noexcept;
    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
    void bind() const;
    static void unbind();
  private:
    GLuint m_id = 0;
    unsigned int m_elementsCount = 0;
  };
}
#endif // OT_VERTEXARRAY_H