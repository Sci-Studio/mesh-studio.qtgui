#pragma once

#include "geometry/Mesh.hpp"

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <vector>

class MeshRenderer {
  public:
    MeshRenderer();
    ~MeshRenderer();
    bool initialize();
    void destroy();
    void draw();
    void release();

  public:
    void uploadMeshVertices(const geometry::Mesh& mesh);

  private:
    bool mInitialized = false;
    std::vector<float> mMeshVertices;
    QOpenGLVertexArrayObject mVao;
    QOpenGLBuffer mPointVbo{QOpenGLBuffer::VertexBuffer};
};
