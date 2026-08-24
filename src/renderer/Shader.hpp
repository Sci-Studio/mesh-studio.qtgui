#pragma once

#include <QOpenGLShaderProgram>
#include <QString>

class Shader {
  public:
    bool loadFromFiles(const QString& vertexPath, const QString& fragmentPath = QString());
    void bind();
    void release();
    QOpenGLShaderProgram* program();

  private:
    QString parseShaderSource(const QString& sourceFilePath) const;
    QOpenGLShaderProgram mProgram;
};
