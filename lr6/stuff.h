#include "arrow.h"
#include "figure.h"

#pragma once


class Stuff : public Figure
{
public:
    float d1 = 0.5,
    d2 = 1.0f,
    d3 = 1.3f,
    r1 = 1,
    r2 = 0.5f;

    Stuff();

    void generate(int edges);

    QVector3D p1();
    QVector3D c1(int count, int index);
    QVector3D c2(int count, int index);
    QVector3D c3(int count, int index);
    QVector3D c4(int count, int index);
    QVector3D p2();
};

