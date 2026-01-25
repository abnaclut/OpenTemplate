#pragma once
#include <vector>

#ifndef GLAD_INCLUDED
#include "../../external/glad/include/glad/glad.h"
#define GLAD_INCLUDED
#endif

namespace RenderEngine
{

  struct VertexBufferLayoutElement
  {
    GLint count;
    GLenum type;
    GLboolean normalized;
    unsigned int size;
  };
  class VertexBufferLayout
  {
  public:
    VertexBufferLayout();
    void reserveElements(size_t count);
    [[nodiscard]] unsigned int getStride() const { return m_stride; }
    void addElementLayoutFloat(unsigned int count, bool normalized);
    [[nodiscard]] const std::vector<VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElements; }
  private:
    std::vector<VertexBufferLayoutElement> m_layoutElements;
    unsigned int m_stride;
  };
}