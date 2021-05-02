#pragma once

#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>
#include <QOpenGLShaderProgram>
#include <QGLFunctions>
#include <QOpenGLFunctions_3_3_Core>

struct VertexData {
    QVector3D vertex;
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

class Figure : public QObject, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

signals:
    void changed();

public:
    Figure();
    ~Figure() override;

    QVector<Edge> edges;

    QMatrix4x4 model() const;

    void initialize();
    void paint();

    void rotate(float angle, const QVector3D& vector);
    void scale(QVector3D vector);
    void translate(QVector3D vector);
    void translateIdentity();

    void markNeedsPaint();
    void markVertexChanged();

private:
    QMatrix4x4 _modelRotation;
    QMatrix4x4 _modelTranslate;
    QMatrix4x4 _modelScale;

    // VBO - vertices data buffer
    GLuint _vbo = 0;
    // VEO - array of elements (indicies in VBO)
    GLuint _veo = 0;
    // VAO - configuration of vertices
    GLuint _vao = 0;

    QVector<VertexData> _verticesBuffer;
    QVector<int> _indicesBuffer;

    bool _verticesChanged = true;

    void allocateBuffers();
};

