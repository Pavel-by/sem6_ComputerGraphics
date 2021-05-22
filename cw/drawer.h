#pragma once

#include "cube.h"
#include "figure.h"
#include "viewmatrixwrapper.h"

#include <figurewrapper.h>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include <light/lightconfig.h>

class Drawer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Drawer(QWidget *parent = nullptr);
    ~Drawer() override;

    QMatrix4x4 projPerspective;

    void addFigure(Figure *figure);
    bool removeFigure(Figure *figure);

    FigureWrapper& figureWrapper();
    ViewMatrixWrapper& viewWrapper();

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
    QList<Figure*> _figures;
    ViewMatrixWrapper _viewWrapper;
    FigureWrapper _figureWrapper;
    QList<LightConfig*> _lights;

    QOpenGLFunctions_3_3_Compatibility* getFuncs();
};

