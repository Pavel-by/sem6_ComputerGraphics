#pragma once

#include "cube.h"
#include "figure.h"
#include "viewmatrixwrapper.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

class Drawer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    Drawer(QWidget *parent = nullptr);
    ~Drawer() override;

    QMatrix4x4 projPerspective;

private slots:
    void depenceChanged();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void paint();
    void setupLight();

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QVector<Figure*> _figures;
    ViewMatrixWrapper _viewWrapper;
    QVector4D _lightPosition;
    QVector4D _lightDirection;
    QVector3D _lightSpotDirection;
};

