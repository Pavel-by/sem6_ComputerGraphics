#include "viewmatrixwrapper.h"
#include <iostream>

ViewMatrixWrapper::ViewMatrixWrapper()
    : QObject(),
      _playerAt(QVector3D(20, 20, 20)),
      _lookVector(QVector3D(-1, -1, -1).normalized()),
      _upVector(QVector3D(0, 1, 0))
{
    _timer.setInterval(1000 / 60);
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

QMatrix4x4 ViewMatrixWrapper::matrix() {
    QMatrix4x4 m;
    m.lookAt(_playerAt, _playerAt + _lookVector, _upVector);
    return m;
}

void ViewMatrixWrapper::mouseMoveEvent(QMouseEvent* event) {
    if (event->isAccepted())
        return;

    if (!_tracking)
        return;

    QPoint diff = _lastMouse - event->globalPos();
    _lastMouse = event->globalPos();

    if (diff.x() == 0 && diff.y() == 0)
        return;

    QMatrix4x4 m;

    if (diff.x() != 0) {
        m.rotate(static_cast<float>(diff.x()) / 4, _upVector);
        _lookVector = m * _lookVector;
    }

    if (diff.y() != 0) {
        m.setToIdentity();
        m.rotate(static_cast<float>(diff.y()) / 4,
                 QVector3D::crossProduct(_lookVector, _upVector));
        _lookVector = m * _lookVector;
    }
    emit changed();
}

void ViewMatrixWrapper::mousePressEvent(QMouseEvent* event) {
    if (event->isAccepted())
        return;

    if (event->button() & Qt::LeftButton) {
        _tracking = true;
        event->accept();
        _lastMouse = event->globalPos();
    }
}

void ViewMatrixWrapper::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() & Qt::LeftButton && _tracking) {
        event->accept();
        _tracking = false;
    }
}

void ViewMatrixWrapper::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    _goForward |= key == Qt::Key_W;
    _goBackward |= key == Qt::Key_S;
    _goLeft |= key == Qt::Key_A;
    _goRight |= key == Qt::Key_D;
    _goUp |= key == Qt::Key_Space;
    _goDown |= key == Qt::Key_Shift;

    if (moving() && !_timer.isActive()) {
        _lastTime = clock();
        _timer.start();
    }
}

void ViewMatrixWrapper::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    _goForward &= key != Qt::Key_W;
    _goBackward &= key != Qt::Key_S;
    _goLeft &= key != Qt::Key_A;
    _goRight &= key != Qt::Key_D;
    _goUp &= key != Qt::Key_Space;
    _goDown &= key != Qt::Key_Shift;

    if (!moving())
        _timer.stop();
}

bool ViewMatrixWrapper::moving() {
    return _goForward || _goBackward || _goLeft
            || _goRight || _goUp || _goDown;
}

void ViewMatrixWrapper::timerTimeout() {
    if (!moving())
        return;

    QVector3D direction;

    if (_goForward)
        direction += _lookVector;

    if (_goBackward)
        direction += -_lookVector;

    if (_goLeft)
        direction += QVector3D::crossProduct(_upVector, _lookVector).normalized();

    if (_goRight)
        direction += -QVector3D::crossProduct(_upVector, _lookVector).normalized();

    if (_goUp)
        direction += _upVector;

    if (_goDown)
        direction += -_upVector;

    clock_t now = clock();
    float delta = static_cast<float>((now - _lastTime)) / CLOCKS_PER_SEC;
    _lastTime = now;
    direction.normalize();
    _playerAt += direction  * delta * 12.0f;
    emit changed();
}

QVector3D ViewMatrixWrapper::eyeAt() {
    return _playerAt;
}

QVector3D ViewMatrixWrapper::lookVector() {
    return _lookVector;
}

QVector3D ViewMatrixWrapper::upVector() {
    return _upVector;
}
