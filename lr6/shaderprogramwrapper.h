#include <QOpenGLShaderProgram>

#pragma once


class ShaderProgramWrapper
{
public:
    ShaderProgramWrapper();
    ShaderProgramWrapper(const QString& vertexShaderPath, const QString& fragmentShaderPath);
    ShaderProgramWrapper(const ShaderProgramWrapper& other);
    ~ShaderProgramWrapper();

    bool initialize();
    bool bind();
    void release();
    void clear();

    QOpenGLShaderProgram * program();

    ShaderProgramWrapper& operator=(const ShaderProgramWrapper& other);

private:
    QOpenGLShaderProgram *_program = nullptr;
    QString _vertexShaderPath;
    QString _fragmentShaderPath;
};

