#include "lightconfig.h"

LightConfig LightConfig::base(
    GL_LIGHT0,
    QVector4D(30,30,30, 1),
    QColor(62, 62, 62),
    QColor(184, 246, 255),
    QColor(255, 255, 255)
);
/*LightConfig LightConfig::baseReversed = LightConfig(
    GL_LIGHT1,
    QVector3D(1, 1, 1),
    QColor(62, 62, 62),
    QColor(90, 123, 128),
    QColor(75, 128, 118),
);*/
