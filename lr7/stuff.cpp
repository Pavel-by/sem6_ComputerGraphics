#include "stuff.h"
#include <iostream>
#include "config.h"

Stuff::Stuff()
{
    generate(20);
}

void Stuff::generate(int count) {
    edges.resize(count * 5);

    int edgeIndex = 0;

    QVector3D v1 = p1();
    for (int i = 0; i < count; i++) {
        edges[edgeIndex++] =
        {{
             v1,
             c1(count, i + 1),
             c1(count, i),
         }};
    }
    for (int i = 0; i < count; i++) {
        edges[edgeIndex++] =
        {{
             c1(count, i),
             c1(count, i + 1),
             c2(count, i + 1),
             c2(count, i),
         }};
    }
    for (int i = 0; i < count; i++) {
        edges[edgeIndex++] =
        {{
             c2(count, i),
             c2(count, i + 1),
             c3(count, i + 1),
             c3(count, i),
         }};
    }
    for (int i = 0; i < count; i++) {
        edges[edgeIndex++] =
        {{
             c3(count, i),
             c3(count, i + 1),
             c4(count, i + 1),
             c4(count, i),
         }};
    }
    v1 = p2();
    for (int i = 0; i < count; i++) {
        edges[edgeIndex++] =
        {{
             v1,
             c4(count, i),
             c4(count, i + 1),
         }};
    }

    markVertexChanged();
    markNeedsPaint();
}

QVector3D Stuff::p1() {
    return QVector3D(d3, 0, 0);
}

QVector3D Stuff::c1(int count, int index) {
    QVector3D v = QVector3D(d2, 0, r2);
    QMatrix4x4 m;
    m.rotate(static_cast<float>(index) / count * 360, QVector3D(1, 0, 0));
    return m * v;
}

QVector3D Stuff::c2(int count, int index) {
    QVector3D v = QVector3D(d1, 0, r1);
    QMatrix4x4 m;
    m.rotate(static_cast<float>(index) / count * 360, QVector3D(1, 0, 0));
    return m * v;
}

QVector3D Stuff::c3(int count, int index) {
    return QVector3D(-1, 1, 1) * c2(count, index);
}

QVector3D Stuff::c4(int count, int index) {
    return QVector3D(-1, 1, 1) * c1(count, index);
}

QVector3D Stuff::p2() {
    return QVector3D(-1, 1, 1) * p1();
}
