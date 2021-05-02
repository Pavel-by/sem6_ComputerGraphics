#include "cube.h"
#include "drawer.h"
#include <QMatrix3x3>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QWheelEvent>
#include <iostream>
#include "config.h"
#include "stuff.h"

Drawer::Drawer(QWidget *parent) : QOpenGLWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    QObject::connect(&_viewWrapper, SIGNAL(changed()), this, SLOT(depenceChanged()));
    QObject::connect(Config::instance, SIGNAL(changed()), this, SLOT(depenceChanged()));

    float minTranslate = -10, maxTranslate = 10;
    float minRotate = 0, maxRotate = 360;

    QRandomGenerator *generator = QRandomGenerator::global();

    Stuff* stuff = new Stuff();
    _figures.append(stuff);

    for (Figure* f : _figures) {
        QObject::connect(f, SIGNAL(changed()), this, SLOT(depenceChanged()));
    }

    /*for (int i = 0; i < 1; i++) {
        Figure *figure = new Cube();
        figure->translate(
                    QVector3D(
                        static_cast<float>(generator->generateDouble()) * (maxTranslate - minTranslate) + minTranslate,
                        static_cast<float>(generator->generateDouble()) * (maxTranslate - minTranslate) + minTranslate,
                        static_cast<float>(generator->generateDouble()) * (maxTranslate - minTranslate) + minTranslate
                        ));
        figure->rotate(
                    static_cast<float>(generator->generateDouble()) * (maxRotate - minRotate) + minRotate,
                    QVector3D(
                        static_cast<float>(generator->generateDouble()) * 2 - 1,
                        static_cast<float>(generator->generateDouble()) * 2 - 1,
                        static_cast<float>(generator->generateDouble()) * 2 - 1
                        ));
        QObject::connect(figure, SIGNAL(changed()), this, SLOT(depenceChanged()));
        _figures.append(figure);
    }*/
}

Drawer::~Drawer() {
}

void Drawer::depenceChanged() {
    update();
}

void Drawer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1, 1, 1, 1);
    for (Figure* figure : _figures) {
        figure->initialize();
    }
}

void Drawer::resizeGL(int w, int h) {
    float ratio = static_cast<float>(w) / static_cast<float>(h);
    projPerspective = QMatrix4x4();
    projPerspective.perspective(45.0f, ratio, 0.1f, 100.0f);
}

void writeColor(float* to, const QColor& color) {
    to[0] = static_cast<GLfloat>(color.redF());
    to[1] = static_cast<GLfloat>(color.greenF());
    to[2] = static_cast<GLfloat>(color.blueF());
    to[3] = static_cast<GLfloat>(color.alphaF());
}

void Drawer::paintGL() {
    glClearColor(1, 1, 1, 1);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFrontFace(GL_CCW);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    QMatrix4x4 view = _viewWrapper.matrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(view.constData());

    Config& config = *Config::instance;
    GLfloat tempColor[4];
    writeColor(tempColor, config.lightModelAmbient);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, tempColor);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, config.lightModelColorControl);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, config.lightModelLocalViewer);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, config.lightModelTwoSide);

    writeColor(tempColor, config.materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tempColor);
    writeColor(tempColor, config.materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tempColor);
    writeColor(tempColor, config.materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tempColor);
    writeColor(tempColor, config.materialEmission);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, tempColor);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, config.materialShininess);

    setupLight();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projPerspective.constData());

    for (Figure* figure : _figures) {
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf((view * figure->model()).constData());

        figure->paint();
    }
}

void Drawer::setupLight() {
    Config& config = *Config::instance;
    GLenum light = GL_LIGHT0;

    float c[4];
    writeColor(c, config.lightAmbient);
    glLightfv(light, GL_AMBIENT, c);
    writeColor(c, config.lightDiffuse);
    glLightfv(light, GL_DIFFUSE, c);
    writeColor(c, config.lightSpecular);
    glLightfv(light, GL_SPECULAR, c);

    if (config.isLightPositionAttached) {
        _lightPosition = _viewWrapper.eyeAt();
        _lightPosition.setW(1);
        _lightDirection = _viewWrapper.lookVector();
        _lightDirection.setW(0);
    }

    if (config.isLightSpotAttached && !config.isLightDirectional) {
        _lightSpotDirection = _viewWrapper.lookVector();
    }

    if (config.isLightDirectional) {
        QVector4D tempQV = -_lightDirection;
        glLightfv(light, GL_POSITION, reinterpret_cast<GLfloat*>(&tempQV));
    } else {
        glLightfv(light, GL_POSITION, reinterpret_cast<GLfloat*>(&_lightPosition));
        glLightf(light, GL_CONSTANT_ATTENUATION, config.lightConstantAttenuation);
        glLightf(light, GL_LINEAR_ATTENUATION, config.lightLinearAttenuation);
        glLightf(light, GL_QUADRATIC_ATTENUATION, config.lightQuadraticAttenuation);
        glLightfv(light, GL_SPOT_DIRECTION, reinterpret_cast<GLfloat*>(&_lightSpotDirection));
        glLightf(light, GL_SPOT_CUTOFF, config.lightSpotCutoff);
        glLightf(light, GL_SPOT_EXPONENT, config.lightSpotExponent);
    }
}

void Drawer::mouseMoveEvent(QMouseEvent* event) {
    event->setAccepted(false);
    _viewWrapper.mouseMoveEvent(event);
    event->accept();
}

void Drawer::mousePressEvent(QMouseEvent* event) {
    event->setAccepted(false);
    _viewWrapper.mousePressEvent(event);
    event->accept();
}

void Drawer::mouseReleaseEvent(QMouseEvent *event) {
    event->setAccepted(false);
    _viewWrapper.mouseReleaseEvent(event);
    event->accept();
}

void Drawer::keyPressEvent(QKeyEvent *event) {
    _viewWrapper.keyPressEvent(event);
}

void Drawer::keyReleaseEvent(QKeyEvent *event) {
    _viewWrapper.keyReleaseEvent(event);
}
