#include "figurewrapper.h"

FigureWrapper::FigureWrapper(QObject *parent) : QObject(parent)
{

}

void FigureWrapper::mouseMoveEvent(QMouseEvent* event) {
    if (!ready())
        return;

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
        figure->rotate(-static_cast<float>(diff.x()) / 2,
                       figure->model().inverted() * viewWrapper->upVector());
    }

    if (diff.y() != 0) {
        figure->rotate(
                    -static_cast<float>(diff.y()) / 2,
                    figure->model().inverted() * QVector3D::crossProduct(viewWrapper->lookVector(), viewWrapper->upVector())
                    );
    }
    emit changed();
}

void FigureWrapper::mousePressEvent(QMouseEvent* event) {
    if (event->isAccepted())
        return;

    if (event->button() & Qt::RightButton && ready()) {
        _tracking = true;
        event->accept();
        _lastMouse = event->globalPos();
        _yRotateVector = viewWrapper->lookVector();
    }
}

void FigureWrapper::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() & Qt::RightButton && _tracking) {
        event->accept();
        _tracking = false;
    }
}

bool FigureWrapper::ready() {
    return figure != nullptr && viewWrapper != nullptr;
}
