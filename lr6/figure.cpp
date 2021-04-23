#include "figure.h"
#include <iostream>

Figure::Figure():QObject()
{

}

Figure::Figure(const Figure& other) {
    *this = other;
}

Figure::~Figure() {}

void Figure::initialize3d(QOpenGLShaderProgram* program) {
    _vao3d.create();
    _vao3d.bind();

    _verticesBufferGL3d.create();
    _verticesBufferGL3d.bind();

    int offset = 0;
    program->enableAttributeArray("vertex");
    program->setAttributeBuffer("vertex", GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    program->enableAttributeArray("color");
    program->setAttributeBuffer("color", GL_FLOAT, offset, 4, sizeof(VertexData));

    offset += sizeof(QVector4D);
    program->enableAttributeArray("normal");
    program->setAttributeBuffer("normal", GL_FLOAT, offset, 3, sizeof(VertexData));

    _indicesBufferGL3d.create();
    _indicesBufferGL3d.bind();

    _vao3d.release();

    for (Figure& f : children) {
        f.initialize3d(program);
    }
}

void Figure::paint3d(QOpenGLShaderProgram* program) {
    allocateBuffers3d();
    program->setUniformValue("color", color);
    program->setUniformValue("model", model);
    _vao3d.bind();
    glDrawElements(GL_TRIANGLES, _indicesBuffer3d.size(), GL_UNSIGNED_INT, 0);
    _vao3d.release();

    for (Figure& f : children) {
        f.model = model;
        f.paint3d(program);
    }
}

void Figure::allocateBuffers3d() {
    if (!_verticesChanged3d)
        return;

    _verticesChanged3d = false;

    int verticesCount = 0;
    int indicesCount = 0;

    for (const Edge& edge : edges) {
        verticesCount += edge.vertices.size();
        indicesCount += (edge.vertices.size() - 2) * 3;
    }

    _verticesBuffer3d.resize(verticesCount);
    _indicesBuffer3d.resize(indicesCount);

    int vertexPosition = 0, indexPosition = 0;

    for (const Edge& edge : edges) {
        for (int i = 2; i < edge.vertices.size(); i++) {
            _indicesBuffer3d[indexPosition++] = vertexPosition;
            _indicesBuffer3d[indexPosition++] = vertexPosition + i - 1;
            _indicesBuffer3d[indexPosition++] = vertexPosition + i;
        }
        QVector3D normal = edge.normal();
        for (const QVector3D& vertex : edge.vertices) {
            _verticesBuffer3d[vertexPosition++] = {
                vertex,
                color,
                normal
            };
        }
    }

    _verticesBufferGL3d.bind();
    _verticesBufferGL3d.allocate(_verticesBuffer3d.constData(), _verticesBuffer3d.size() * sizeof(VertexData));
    _indicesBufferGL3d.bind();
    _indicesBufferGL3d.allocate(_indicesBuffer3d.constData(), _indicesBuffer3d.size() * sizeof(GLuint));
}

void Figure::initializeEdges(QOpenGLShaderProgram* program) {
    _vaoEdges.create();
    _vaoEdges.bind();

    _verticesBufferGLEdges.create();
    _verticesBufferGLEdges.bind();

    program->enableAttributeArray("vertex");
    program->setAttributeBuffer("vertex", GL_FLOAT, 0, 3, 0);

    _indicesBufferGLEdges.create();
    _indicesBufferGLEdges.bind();

    _vaoEdges.release();

    for (Figure& f : children) {
        f.initializeEdges(program);
    }
}

void Figure::paintEdges(QOpenGLShaderProgram* program) {
    allocateBuffersEdges();
    program->setUniformValue("color", color);
    program->setUniformValue("model", model);
    _vaoEdges.bind();
    glDrawElements(GL_LINES, _indicesBufferEdges.size(), GL_UNSIGNED_INT, 0);
    _vaoEdges.release();

    for (Figure& f : children) {
        f.model = model;
        f.paint3d(program);
    }
}

void Figure::allocateBuffersEdges() {
    if (!_verticesChangedEdges)
        return;

    _verticesChangedEdges = false;

    int verticesCount = 0;
    int indicesCount = 0;

    for (const Edge& edge : edges) {
        verticesCount += edge.vertices.size();
        indicesCount += edge.vertices.size() * 2;
    }

    _verticesBufferEdges.resize(verticesCount);
    _indicesBufferEdges.resize(indicesCount);

    int vertexPosition = 0, indexPosition = 0;

    for (const Edge& edge : edges) {
        for (int i = 0; i < edge.vertices.size(); i++) {
            int cur = i, next = (i + 1) % edge.vertices.size();
            _indicesBufferEdges[indexPosition++] = vertexPosition + cur;
            _indicesBufferEdges[indexPosition++] = vertexPosition + next;
        }
        QVector3D normal = edge.normal();
        for (const QVector3D& vertex : edge.vertices) {
            _verticesBufferEdges[vertexPosition++] = vertex;
        }
    }

    _verticesBufferGLEdges.bind();
    _verticesBufferGLEdges.allocate(_verticesBufferEdges.constData(), _verticesBufferEdges.size() * sizeof(VertexData));
    _indicesBufferGLEdges.bind();
    _indicesBufferGLEdges.allocate(_indicesBufferEdges.constData(), _indicesBufferEdges.size() * sizeof(GLuint));
}

void Figure::markNeedsPaint() {
    emit changed();
}

void Figure::markVertexChanged() {
    _verticesChanged3d = true;
    _verticesChangedEdges = true;
}

Figure& Figure::operator=(const Figure& other) {
    children = other.children;
    edges = other.edges;
    model = other.model;
    color = other.color;
    _verticesChanged3d = true;
    _verticesChangedEdges = true;
    return *this;
}

void Figure::rotate(float angle, const QVector3D& vector) {
    QVector3D t = model * center;
    model.translate(-t);
    model.rotate(angle, vector);
    model.translate(t);
}

void Figure::scale(QVector3D vector) {
    QVector3D t = model * center;
    model.translate(-t);
    model.scale(vector);
    model.translate(t);
}
