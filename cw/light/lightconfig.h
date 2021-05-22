#include <QColor>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QVector3D>
#include <QVector4D>
#include <viewmatrixwrapper.h>

#pragma once

class LightConfig : public QObject {
    Q_OBJECT

signals:
    void changed();

public:
    static LightConfig base;
    //static LightConfig baseReversed;

    GLenum light;
    QVector4D direction;
    QColor lightAmbient;
    QColor lightDiffuse;
    QColor lightSpecular;

    LightConfig(GLenum _light,
                QVector4D _direction,
                QColor _lightAmbient,
                QColor _lightDiffuse,
                QColor _lightSpecular):
        QObject(),
        light(_light),
        direction(_direction),
        lightAmbient(_lightAmbient),
        lightDiffuse(_lightDiffuse),
        lightSpecular(_lightSpecular) {}

    virtual ~LightConfig() override {}

    void use(QOpenGLContext *context) {
        auto funcs = context->versionFunctions<QOpenGLFunctions_3_3_Compatibility>();
        glEnable(light);
        float c[4];
        writeColor(c, lightAmbient);
        funcs->glLightfv(light, GL_AMBIENT, c);
        writeColor(c, lightDiffuse);
        funcs->glLightfv(light, GL_DIFFUSE, c);
        writeColor(c, lightSpecular);
        funcs->glLightfv(light, GL_SPECULAR, c);
        QVector4D tempV = -direction;
        funcs->glLightfv(light, GL_POSITION, reinterpret_cast<GLfloat*>(&tempV));
    }

    void attachViewWrapper(ViewMatrixWrapper *wrapper) {
        if (_wrapper != nullptr)
            return;

        this->_wrapper = wrapper;
        QObject::connect(_wrapper, SIGNAL(changed()), this, SLOT(wrapperChanged()));
        wrapperChanged();
    }

    void detachViewWrapper() {
        if (_wrapper == nullptr)
            return;

        QObject::disconnect(_wrapper, SIGNAL(changed()), this, SLOT(wrapperChanged()));
        _wrapper = nullptr;
    }

private slots:
    void wrapperChanged() {
        assert(_wrapper != nullptr);
        direction = _wrapper->eyeAt();
        direction.setW(1);
        emit changed();
    }

private:
    ViewMatrixWrapper *_wrapper = nullptr;

    void writeColor(float* to, const QColor& color) {
        to[0] = static_cast<GLfloat>(color.redF());
        to[1] = static_cast<GLfloat>(color.greenF());
        to[2] = static_cast<GLfloat>(color.blueF());
        to[3] = static_cast<GLfloat>(color.alphaF());
    }
};
