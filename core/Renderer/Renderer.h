#pragma once
#ifndef OT_RENDERER_H
#define OT_RENDERER_H

#include "../Includes/includes.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

namespace RenderEngine
{
  class Renderer
  {
  public:
    static void draw(const VertexArray& vertexArray,
                     const IndexBuffer& indexBuffer,
                     const ShaderProgram& shader);
    static void setClearColor(float r,
                              float g,
                              float b,
                              float a);
    static void setDepthTest(bool enable);
    static void clear();
    static void setViewport(unsigned int width,
                            unsigned int height,
                            unsigned int leftOffset = 0,
                            unsigned int bottomOffset = 0);
    static std::string getRendererStr(); //FIXME move to specific submodule?
    static std::string getVersionStr(); //FIXME move to specific submodule?
  };
}
#endif // OT_RENDERER_H