#include "ironleg.h"

IronLeg::IronLeg(QVector3D c, float r, float height, int count)
{
    materials = {
        &MaterialConfig::ironLeg,
    };

    int edgesCount = count + 2;
    edges.resize(edgesCount);

    QVector3D v = QVector3D(r, 0, 0),
            top1 = v + c, top2,
            bot1 = v + c + QVector3D(0, height, 0), bot2;
    QMatrix4x4 matrix;
    matrix.rotate(-360.0f / count, QVector3D(0,1,0));
    for (int i = 0; i < count; i++) {
        v = matrix * v;
        top2 = top1;
        bot2 = bot1;
        top1 = v + c;
        bot1 = v + c + QVector3D(0, height, 0);
        edges[0].vertices.insert(0, top1);
        edges[1].vertices.insert(0, bot1);
        edges[i + 2] = {{top1, top2, bot2, bot1}};
    }
}
