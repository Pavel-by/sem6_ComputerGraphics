#pragma once

#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>
#include <QOpenGLShaderProgram>

struct VertexData {
    QVector3D vertex;
    QVector4D color;
    QVector3D normal;
};

struct Edge {
    QVector<QVector3D> vertices;

    QVector3D normal() const {
        assert(vertices.size() >= 3);
        QVector3D v1 = vertices[2] - vertices[1],
                v2 = vertices[0] - vertices[1];
        return QVector3D::crossProduct(v1, v2);
    }
};

class Figure : public QObject
{
    Q_OBJECT

signals:
    void changed();

public:
    Figure();
    Figure(const Figure& other);
    ~Figure() override;

    QVector3D center;
    QVector<Edge> edges;
    QVector4D color = QVector4D(1.0f, 0.0f, 0.0f, 1.0f);
    QVector<Figure> children;

    QMatrix4x4 model() const;

    void initialize3d(QOpenGLShaderProgram* program);
    void paint3d(QOpenGLShaderProgram* program);

    void initializeEdges(QOpenGLShaderProgram* program);
    void paintEdges(QOpenGLShaderProgram* program);

    void rotate(float angle, const QVector3D& vector);
    void scale(QVector3D vector);
    void translate(QVector3D vector);

    void markNeedsPaint();
    void markVertexChanged();

    Figure& operator=(const Figure& other);

private:
    QMatrix4x4 _modelRotation;
    QMatrix4x4 _modelTranslate;
    QMatrix4x4 _modelScale;

    QOpenGLVertexArrayObject _vao3d;
    QOpenGLVertexArrayObject _vaoEdges;

    QOpenGLBuffer _verticesBufferGL3d = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer _indicesBufferGL3d = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLBuffer _verticesBufferGLEdges = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer _indicesBufferGLEdges = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    QVector<VertexData> _verticesBuffer3d;
    QVector<int> _indicesBuffer3d;

    QVector<QVector3D> _verticesBufferEdges;
    QVector<int> _indicesBufferEdges;

    bool _verticesChanged3d = true;
    bool _verticesChangedEdges = true;

    void allocateBuffers3d();
    void allocateBuffersEdges();
};

