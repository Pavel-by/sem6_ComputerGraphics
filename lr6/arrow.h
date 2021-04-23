#include "figure.h"

#include <QVector3D>

#pragma once


class Arrow : public Figure
{
public:
    Arrow();

    void generate(QVector3D from, QVector3D to, float radius = 0.03, int count = 10);
};

