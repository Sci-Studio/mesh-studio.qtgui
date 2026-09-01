#pragma once

#include "geometry/Mesh.hpp"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <vector>

class MeshRenderer {
  public:
    MeshRenderer();
    ~MeshRenderer();
    bool initialize(QOpenGLShaderProgram& program);
    void destroy();
    void draw();
    void release();

  public:
    void uploadMeshVertices(const geometry::Mesh& mesh);

  private:
    bool mInitialized = false;
    std::vector<float> mMeshVertices;
    std::vector<float> mConstraintVertices;
    std::vector<float> mTriangulationVertices;
    QOpenGLVertexArrayObject mVao;
    QOpenGLVertexArrayObject mLineVao;
    QOpenGLVertexArrayObject mTriangulationVao;
    QOpenGLBuffer mPointVbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLBuffer mLineVbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLBuffer mTriangulationVbo{QOpenGLBuffer::VertexBuffer};
};
