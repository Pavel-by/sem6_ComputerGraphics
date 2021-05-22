#pragma once

#include <QMatrix4x4>
#include <QObject>
#include <QVector3D>
#include <QVector>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_3_3_Compatibility>

#include <light/materialconfig.h>

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

class Figure : public QObject
{
    Q_OBJECT

signals:
    void changed();

public:
    Figure();
    ~Figure() override;

    QVector<Edge> edges;
    QList<MaterialConfig*> materials;

    QMatrix4x4 model() const;

    void attach(QOpenGLContext *context);
    void paint();
    void detach();
    bool isAttached();

    void rotate(float angle, const QVector3D& vector);
    void scale(QVector3D vector);
    void translate(QVector3D vector);
    void setTranslate(QVector3D vector);
    void clearModel();

    void markNeedsPaint();
    void markVertexChanged();

    void split(float density);

private:
    QOpenGLContext *context = nullptr;

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
    QOpenGLFunctions_3_3_Compatibility *getFuncs();
};

