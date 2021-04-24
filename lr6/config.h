#pragma once

#include "figure.h"
#include "stuff.h"

#include <QMatrix4x4>
#include <QObject>
#include <QVector3D>

class Config : public QObject
{
    Q_OBJECT
public:
    static Config* instance;

    explicit Config(QObject *parent = nullptr);

    bool is3D = true;
    float light = 1;
    bool isOrtho = false;

    Stuff* figure;

    void notify();

signals:
    void changed();
};

