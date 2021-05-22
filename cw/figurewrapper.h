#pragma once

#include "figure.h"
#include "viewmatrixwrapper.h"

#include <QMouseEvent>
#include <QObject>

class FigureWrapper : public QObject
{
    Q_OBJECT
public:
    Figure* figure = nullptr;
    ViewMatrixWrapper* viewWrapper = nullptr;

    explicit FigureWrapper(QObject *parent = nullptr);
    FigureWrapper(const FigureWrapper& other);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    FigureWrapper& operator=(const FigureWrapper& other);

signals:
    void changed();

private:
    QPoint _lastMouse;
    bool _tracking = false;
    QVector3D _yRotateVector;

    bool ready();
};

