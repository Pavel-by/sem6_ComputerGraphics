#include "materialconfig.h";

MaterialConfig MaterialConfig::notExactlyWood = {
    GL_FRONT_AND_BACK,
    QColor(54, 33, 14),
    QColor(182, 109, 46),
    QColor(91, 55, 23),
    QColor(),
    10,
};


MaterialConfig MaterialConfig::glassSide = {
    GL_FRONT,
    QColor(0, 26, 15, 128),
    QColor(0, 200, 200, 128),
    QColor(128, 128, 128, 102),
    QColor(),
    50,
};

MaterialConfig MaterialConfig::glassSideBack = {
    GL_BACK,
    QColor(0, 26, 15, 128),
    QColor(0, 200, 200, 128),
    QColor(128, 128, 128, 102),
    QColor(),
    50,
};

MaterialConfig MaterialConfig::glassSideSide = {
    GL_FRONT_AND_BACK,
    QColor(0, 26, 15, 200),
    QColor(0, 200, 200, 200),
    QColor(128, 128, 128, 50),
    QColor(),
    50,
};

MaterialConfig MaterialConfig::ironLeg = {
    GL_FRONT_AND_BACK,
    QColor(64, 64, 64),
    QColor(102, 102, 102),
    QColor(120, 120, 120),
    QColor(),
    20,
};

