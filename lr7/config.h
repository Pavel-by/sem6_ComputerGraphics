#pragma once

#include "figure.h"

#include <QMatrix4x4>
#include <QObject>
#include <QVector3D>

class Config : public QObject
{
    Q_OBJECT
public:
    static Config* instance;

    explicit Config(QObject *parent = nullptr);

    QColor lightModelAmbient;
    GLint lightModelColorControl;
    GLint lightModelLocalViewer;
    GLint lightModelTwoSide;

    QColor materialAmbient;
    QColor materialDiffuse;
    QColor materialSpecular;
    QColor materialEmission;
    GLint materialShininess;

    bool isLightDirectional;
    bool isLightPositionAttached;
    bool isLightSpotAttached;
    QColor lightAmbient;
    QColor lightDiffuse;
    QColor lightSpecular;
    GLfloat lightConstantAttenuation;
    GLfloat lightLinearAttenuation;
    GLfloat lightQuadraticAttenuation;
    GLfloat lightSpotCutoff;
    GLfloat lightSpotExponent;

    void notify();

signals:
    void changed();
};

