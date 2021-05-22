#include "glasspanel.h"

GlassPanel::GlassPanel(float width, float length, float height, QVector3D c)
{
    materials = {
        &MaterialConfig::glassSide,
        &MaterialConfig::glassSideBack,
    };

    QVector3D v1 = c + QVector3D(-width/2.0f, height/2.0f, length/2.0f);
    QVector3D v2 = c + QVector3D(width/2.0f, height/2.0f, length/2.0f);
    QVector3D v3 = c + QVector3D(width/2.0f, height/2.0f, -length/2.0f);
    QVector3D v4 = c + QVector3D(-width/2.0f, height/2.0f, -length/2.0f);

    edges.resize(2);
    edges[0] = {{ v1, v2, v3, v4 }};
    edges[1] = {{
                    v1 - QVector3D(0, height, 0),
                    v4 - QVector3D(0, height, 0),
                    v3 - QVector3D(0, height, 0),
                    v2 - QVector3D(0, height, 0),
                }};

}
