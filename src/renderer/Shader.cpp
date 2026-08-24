#include "Shader.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>

bool Shader::loadFromFiles(const QString& vertexPath, const QString& fragmentPath) {
    mProgram.removeAllShaders();

    const QString vertexSource = parseShaderSource(vertexPath);
    if (vertexSource.isEmpty()) {
        qWarning() << "Vertex shader source is empty:" << vertexPath;
        return false;
    }

    if (!mProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource)) {
        qWarning() << "Failed to compile vertex shader:" << vertexPath << mProgram.log();
        return false;
    }

    if (fragmentPath.isEmpty()) {
        return true;
    }

    const QString fragmentSource = parseShaderSource(fragmentPath);
    if (fragmentSource.isEmpty()) {
        qWarning() << "Fragment shader source is empty:" << fragmentPath;
        return false;
    }

    if (!mProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource)) {
        qWarning() << "Failed to compile fragment shader:" << fragmentPath << mProgram.log();
        return false;
    }

    if (!mProgram.link()) {
        qWarning() << "Failed to link shader program:" << mProgram.log();
        return false;
    }

    return true;
}

void Shader::bind() {
    mProgram.bind();
}

void Shader::release() {
    mProgram.release();
}

QOpenGLShaderProgram* Shader::program() {
    return &mProgram;
}

QString Shader::parseShaderSource(const QString& sourceFilePath) const {
    QFile file(sourceFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open shader file:" << sourceFilePath;
        return {};
    }

    QTextStream stream(&file);
    return stream.readAll();
}
