#pragma once

#include <QOpenGLShaderProgram>
#include <QString>

class Shader {
  public:
    static bool loadFromFiles(const QString& vertexPath, const QString& fragmentPath,
                              QOpenGLShaderProgram& program);

  private:
    static QString parseShaderSource(const QString& sourceFilePath);
};
