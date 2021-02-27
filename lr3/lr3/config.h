#pragma once

#include <QMouseEvent>
#include <QObject>
#include <vector>

class Config : public QObject
{
    Q_OBJECT
public:
    static Config* instance;
    static const float PointSize;
    static const float LineSize;

    explicit Config();

    QVector<QVector2D> points;
    QVector2D* hoveredPoint;

    bool isAdding = false;
    bool isRemoving = false;

    void refreshHoveredPoint();
    void onMouseMove(QMouseEvent* event);
    void onMousePress(QMouseEvent* event);
    void onMouseRelease(QMouseEvent* event);

public slots:
    void addButtonClicked();
    void removeButtonClicked();

signals:
    void changed();
};

