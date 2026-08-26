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
    void draw(const geometry::Mesh& mesh, Shader& shader);
    void release();

  public slots:
    void uploadMeshVertices(const geometry::Mesh& mesh);

  private:
    bool mInitialized = false;
    std::vector<float> mMeshVertices;
    QOpenGLBuffer mPointVbo{QOpenGLBuffer::VertexBuffer};
};
