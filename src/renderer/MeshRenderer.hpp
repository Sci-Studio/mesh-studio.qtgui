#pragma once

#include "geometry/Mesh.hpp"
#include "Shader.hpp"

#include <QOpenGLBuffer>
#include <vector>

class MeshRenderer {
  public:
    MeshRenderer();
    ~MeshRenderer();
    bool initialize();
    void destroy();
    void draw(const geometry::Mesh& mesh, Shader& shader);
    void release();

  private:
    bool mInitialized = false;
    std::vector<float> mMeshVertices;
    void uploadMeshVertices(const geometry::Mesh& mesh);
    QOpenGLBuffer mPointVbo{QOpenGLBuffer::VertexBuffer};
};
