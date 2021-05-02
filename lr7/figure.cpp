#include "figure.h"
#include <iostream>

Figure::Figure():QObject()
{

}

Figure::~Figure() {
    if (_vao) glDeleteVertexArrays(1, &_vao);
    if (_vbo) glDeleteBuffers(1, &_vbo);
    if (_veo) glDeleteBuffers(1, &_veo);
}

void Figure::initialize() {
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_veo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _veo);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(VertexData), 0);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(VertexData), reinterpret_cast<GLvoid*>(sizeof(QVector3D)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Figure::paint() {
    allocateBuffers();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indicesBuffer.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Figure::allocateBuffers() {
    if (!_verticesChanged)
        return;

    _verticesChanged = false;

    int verticesCount = 0;
    int indicesCount = 0;

    for (const Edge& edge : edges) {
        verticesCount += edge.vertices.size();
        indicesCount += (edge.vertices.size() - 2) * 3;
    }

    _verticesBuffer.resize(verticesCount);
    _indicesBuffer.resize(indicesCount);

    int vertexPosition = 0, indexPosition = 0;
    QMatrix4x4 normalMatrix = model().inverted().transposed();

    for (const Edge& edge : edges) {
        for (int i = 2; i < edge.vertices.size(); i++) {
            _indicesBuffer[indexPosition++] = vertexPosition;
            _indicesBuffer[indexPosition++] = vertexPosition + i - 1;
            _indicesBuffer[indexPosition++] = vertexPosition + i;
        }
        QVector3D normal = edge.normal();
        for (const QVector3D& vertex : edge.vertices) {
            _verticesBuffer[vertexPosition++] = {
                vertex,
                -normal
                //(normalMatrix * normal).normalized()
            };
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _verticesBuffer.size() * sizeof(VertexData), _verticesBuffer.constData(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _veo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesBuffer.size() * sizeof(GLuint), _indicesBuffer.constData(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Figure::translateIdentity() {
    _modelTranslate = QMatrix4x4();
}

void Figure::markNeedsPaint() {
    emit changed();
}

void Figure::markVertexChanged() {
    _verticesChanged = true;
}

void Figure::rotate(float angle, const QVector3D& vector) {
    _modelRotation.rotate(angle, vector);
    markVertexChanged();
}

void Figure::scale(QVector3D vector) {
    _modelScale.scale(vector);
    markVertexChanged();
}

void Figure::translate(QVector3D vector) {
    _modelTranslate.translate(_modelRotation * vector);
}

QMatrix4x4 Figure::model() const {
    return _modelTranslate * _modelRotation * _modelScale;
}

