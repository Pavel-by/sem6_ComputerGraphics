#ifndef LEG_H
#define LEG_H

#include "figure.h"



class Leg : public Figure
{
public:
    Leg(float width = 1, float length = 1, float height = 1, QVector3D c = QVector3D(0, 0, 0));
};

#endif // LEG_H
