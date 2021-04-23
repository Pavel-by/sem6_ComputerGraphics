#include <QMatrix4x4>
#include <QMouseEvent>
#include <time.h>
#include <QTimer>

#pragma once


class ViewMatrixWrapper : public QObject
{
    Q_OBJECT

signals:
    void changed();

public:
    ViewMatrixWrapper();

    QMatrix4x4 matrix();
    QVector3D eyeAt();
    QVector3D lookVector();
    QVector3D upVector();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void timerTimeout();

private:
    QVector3D _playerAt;
    QVector3D _lookVector;
    QVector3D _upVector;
    QTimer _timer;

    bool _tracking = false;
    bool _goForward = false,
    _goBackward = false,
    _goLeft = false,
    _goRight = false,
    _goUp = false,
    _goDown = false;
    QPoint _lastMouse;
    clock_t  _lastTime;

    bool moving();
};

