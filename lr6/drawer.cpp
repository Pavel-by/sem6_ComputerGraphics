#include "arrow.h"
#include "cube.h"
#include "drawer.h"
#include "stuff.h"
#include <QMatrix3x3>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>
#include "config.h"

// --------------- temp code --------------------
const QVector3D lightPosition = QVector3D(5.0f, 10.0f, 40.0f);
const QVector3D lightColor = QVector3D(1.0f, 1.0f, 1.0f);
// --------------- temp code end ----------------

Drawer::Drawer(QWidget *parent) : QOpenGLWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    QObject::connect(&_viewWrapper, SIGNAL(changed()), this, SLOT(depenceChanged()));
    QObject::connect(&_figureWrapper, SIGNAL(changed()), this, SLOT(depenceChanged()));
    QObject::connect(Config::instance, SIGNAL(changed()), this, SLOT(depenceChanged()));

    _figures = {
        Stuff(),
    };

    for (Figure& f : _figures) {
        QObject::connect(&f, SIGNAL(changed()), this, SLOT(depenceChanged()));
    }

    Config::instance->figure = &_figures[0];
    _figureWrapper.figure = &_figures[0];
    _figureWrapper.viewWrapper = &_viewWrapper;
}

Drawer::~Drawer() {
}

void Drawer::depenceChanged() {
    update();
}

void Drawer::initializeGL() {
    _programWrapper3d.initialize();
    _programWrapper3d.bind();

    for (Figure& figure : _figures) {
        figure.initialize3d(_programWrapper3d.program());
    }
    _programWrapper3d.release();

    _programWrapperEdges.initialize();
    _programWrapperEdges.bind();

    for (Figure& figure : _figures) {
        figure.initializeEdges(_programWrapperEdges.program());
    }
    _programWrapperEdges.release();
}

void Drawer::resizeGL(int w, int h) {
    float ratio = static_cast<float>(w) / h;
    projPerspective = QMatrix4x4();
    projPerspective.perspective(45.0f, ratio, 0.1f, 100.0f);
    projOrtho = QMatrix4x4();
    projOrtho.ortho(-4.0f, 4.0f, -4.0f / ratio, 4.0f / ratio, 0.0f, 100.0f);
}

void Drawer::paintGL() {
    if (Config::instance->is3D)
        paint3d();
    else
        paintEdges();
}

void Drawer::paint3d() {
    if (!_programWrapper3d.bind()) {
        std::cout << "Can not paint: shaders program is not binded" << std::endl;
        return;
    }
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QOpenGLShaderProgram* program = _programWrapper3d.program();

    program->setUniformValue("proj", projPerspective);
    program->setUniformValue("view", _viewWrapper.matrix());
    program->setUniformValue("lightPosition", lightPosition);
    program->setUniformValue("lightColor", lightColor);

    for (Figure& figure : _figures) {
        figure.paint3d(program);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}

void Drawer::paintEdges() {
    if (!_programWrapperEdges.bind()) {
        std::cout << "Can not paint: shaders program is not binded" << std::endl;
        return;
    }
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QOpenGLShaderProgram* program = _programWrapperEdges.program();

    program->setUniformValue("proj", projPerspective);
    program->setUniformValue("view", _viewWrapper.matrix());


    for (Figure& figure : _figures) {
        figure.paintEdges(program);
    }
}

void Drawer::mouseMoveEvent(QMouseEvent* event) {
    event->setAccepted(false);
    _viewWrapper.mouseMoveEvent(event);
    _figureWrapper.mouseMoveEvent(event);
    event->accept();
}

void Drawer::mousePressEvent(QMouseEvent* event) {
    event->setAccepted(false);
    _viewWrapper.mousePressEvent(event);
    _figureWrapper.mousePressEvent(event);
    event->accept();
}

void Drawer::mouseReleaseEvent(QMouseEvent *event) {
    event->setAccepted(false);
    _viewWrapper.mouseReleaseEvent(event);
    _figureWrapper.mouseReleaseEvent(event);
    event->accept();
}

void Drawer::keyPressEvent(QKeyEvent *event) {
    _viewWrapper.keyPressEvent(event);
}

void Drawer::keyReleaseEvent(QKeyEvent *event) {
    _viewWrapper.keyReleaseEvent(event);
}
