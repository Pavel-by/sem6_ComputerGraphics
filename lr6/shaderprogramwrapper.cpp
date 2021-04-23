#include "shaderprogramwrapper.h"
#include <iostream>

ShaderProgramWrapper::ShaderProgramWrapper() {}

ShaderProgramWrapper::ShaderProgramWrapper(const QString& vertexShaderPath, const QString& fragmentShaderPath)
    : _vertexShaderPath(vertexShaderPath),
      _fragmentShaderPath(fragmentShaderPath)
{}

ShaderProgramWrapper::ShaderProgramWrapper(const ShaderProgramWrapper& other) {
    *this = other;
}

ShaderProgramWrapper::~ShaderProgramWrapper() {
    clear();
}

bool ShaderProgramWrapper::initialize() {
    if (_program != nullptr) {
        std::cout << "Trying to reinitialize shader program; initialization skipped" << std::endl;
        return true;
    }

    _program = new QOpenGLShaderProgram();

    if (!_vertexShaderPath.isEmpty() && !_program->addShaderFromSourceFile(QOpenGLShader::Vertex, _vertexShaderPath)) {
        std::cout << "Cannot compile vertex shader" << std::endl;
        clear();
        return false;
    }

    if (!_fragmentShaderPath.isEmpty() && !_program->addShaderFromSourceFile(QOpenGLShader::Fragment, _fragmentShaderPath)) {
        std::cout << "Cannot compile fragment shader" << std::endl;
        clear();
        return false;
    }

    if (!_program->link()) {
        std::cout << "Cannot link shaders program" << std::endl;
        clear();
        return false;
    }

    return true;
}

bool ShaderProgramWrapper::bind() {
    if (_program == nullptr) {
        std::cout << "Trying to bind unitialized shaders program" << std::endl;
        return false;
    }

    assert(_program->isLinked());
    return _program->bind();
}

void ShaderProgramWrapper::release() {
    if (_program != nullptr)
        _program->release();
}

void ShaderProgramWrapper::clear() {
    delete _program;
    _program = nullptr;
}

QOpenGLShaderProgram* ShaderProgramWrapper::program() {
    return _program;
}

ShaderProgramWrapper& ShaderProgramWrapper::operator=(const ShaderProgramWrapper& other) {
    clear();
    _program = other._program;
    _vertexShaderPath = other._vertexShaderPath;
    _fragmentShaderPath = other._fragmentShaderPath;
    return *this;
}
