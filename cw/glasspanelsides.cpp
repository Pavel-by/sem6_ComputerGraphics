#include "glasspanelsides.h"

GlassPanelSides::GlassPanelSides(float width, float length, float height, QVector3D c)
{
    materials = {
        &MaterialConfig::glassSideSide,
    };

    QVector3D v1 = c + QVector3D(-width/2.0f, height/2.0f, length/2.0f);
    QVector3D v2 = c + QVector3D(-width/2.0f, -height/2.0f, length/2.0f);
    QVector3D v3 = c + QVector3D(width/2.0f, height/2.0f, length/2.0f);
    QVector3D v4 = c + QVector3D(width/2.0f, -height/2.0f, length/2.0f);
    QVector3D v5 = c + QVector3D(width/2.0f, height/2.0f, -length/2.0f);
    QVector3D v6 = c + QVector3D(width/2.0f, -height/2.0f, -length/2.0f);
    QVector3D v7 = c + QVector3D(-width/2.0f, height/2.0f, -length/2.0f);
    QVector3D v8 = c + QVector3D(-width/2.0f, -height/2.0f, -length/2.0f);

    edges.resize(4);

    edges[0] = {{ v1, v2, v4, v3 }};
    edges[1] = {{ v3, v4, v6, v5 }};
    edges[2] = {{ v5, v6, v8, v7 }};
    edges[3] = {{ v7, v8, v2, v1 }};
}
