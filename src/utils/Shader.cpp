#include "Shader.hpp"

#include <QFile>

bool Shader::loadFromFiles(const QString& vertexPath, const QString& fragmentPath,
                           QOpenGLShaderProgram& program) {
    program.removeAllShaders();

    const QString vertexSource = parseShaderSource(vertexPath);
    if (vertexSource.isEmpty()) {
        qWarning() << "Vertex shader source is empty:" << vertexPath;
        return false;
    }

    if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource)) {
        qWarning() << "Failed to compile vertex shader:" << vertexPath << program.log();
        return false;
    }

    if (fragmentPath.isEmpty()) {
        qWarning() << "Fragment shader path is empty.";
        return false;
    }

    const QString fragmentSource = parseShaderSource(fragmentPath);
    if (fragmentSource.isEmpty()) {
        qWarning() << "Fragment shader source is empty:" << fragmentPath;
        return false;
    }

    if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource)) {
        qWarning() << "Failed to compile fragment shader:" << fragmentPath << program.log();
        return false;
    }

    if (!program.link()) {
        qWarning() << "Failed to link shader program:" << program.log();
        return false;
    }

    return true;
}

QString Shader::parseShaderSource(const QString& sourceFilePath) {
    QFile file(sourceFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open shader file:" << sourceFilePath;
        return {};
    }

    QTextStream stream(&file);
    return stream.readAll();
}
