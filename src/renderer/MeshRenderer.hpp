#pragma once

#include "Shader.hpp"
#include "geometry/Mesh.hpp"

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <vector>

class MeshRenderer {
  public:
    MeshRenderer();
    ~MeshRenderer();
    bool initialize(Shader& shader);
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
