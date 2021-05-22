#pragma once

#include <QColor>
#include <QObject>
#include <QGLFunctions>
#include <QOpenGLFunctions_3_3_Compatibility>

struct MaterialConfig {
    static MaterialConfig notExactlyWood;
    static MaterialConfig glassSide;
    static MaterialConfig glassSideBack;
    static MaterialConfig glassSideSide;
    static MaterialConfig ironLeg;

    // GL_FRONT_AND_BACK, GL_FRONT or GL_BACK
    GLenum face;
    QColor materialAmbient;
    QColor materialDiffuse;
    QColor materialSpecular;
    QColor materialEmission;
    GLint materialShininess;

    void use(QOpenGLContext *context) {
        auto funcs = context->versionFunctions<QOpenGLFunctions_3_3_Compatibility>();
        GLfloat tempColor[4];
        writeColor(tempColor, materialAmbient);
        funcs->glMaterialfv(face, GL_AMBIENT, tempColor);
        writeColor(tempColor, materialDiffuse);
        funcs->glMaterialfv(face, GL_DIFFUSE, tempColor);
        writeColor(tempColor, materialSpecular);
        funcs->glMaterialfv(face, GL_SPECULAR, tempColor);
        writeColor(tempColor, materialEmission);
        funcs->glMaterialfv(face, GL_EMISSION, tempColor);
        funcs->glMateriali(face, GL_SHININESS, materialShininess);
    }

    void writeColor(float* to, const QColor& color) {
        to[0] = static_cast<GLfloat>(color.redF());
        to[1] = static_cast<GLfloat>(color.greenF());
        to[2] = static_cast<GLfloat>(color.blueF());
        to[3] = static_cast<GLfloat>(color.alphaF());
    }
};

