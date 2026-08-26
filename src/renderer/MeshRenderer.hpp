#pragma once

#include "Shader.hpp"
#include "geometry/Mesh.hpp"

#include <QOpenGLBuffer>
#include <vector>

class MeshRenderer {
  public:
    MeshRenderer();
    ~MeshRenderer();
    bool initialize();
    void destroy();
    void draw(Shader& shader);
    void release();

  public:
    void uploadMeshVertices(const geometry::Mesh& mesh);

  private:
    bool mInitialized = false;
    std::vector<float> mMeshVertices;
    QOpenGLBuffer mPointVbo{QOpenGLBuffer::VertexBuffer};
};
