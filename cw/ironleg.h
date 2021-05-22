#pragma once

#include <figure.h>


class IronLeg : public Figure
{
public:
    IronLeg(QVector3D c, float r, float height, int count = 100);
};

