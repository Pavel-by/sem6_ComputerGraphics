#include "figure.h"

#ifndef GLASSPANEL_H
#define GLASSPANEL_H


class GlassPanel : public Figure
{
public:
    GlassPanel(float width, float length, float height, QVector3D c);
};

#endif // GLASSPANEL_H
