#include "mainwindow.h"

#include <QApplication>
#include <QOpenGLContext>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat *format = new QSurfaceFormat();
    format->setDepthBufferSize(48);
    format->setMajorVersion(3);
    format->setMinorVersion(3);
    format->setSamples(4);
    format->setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(*format);

    MainWindow w;
    w.show();
    return a.exec();
}
