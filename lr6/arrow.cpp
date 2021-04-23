#include "arrow.h"

Arrow::Arrow()
{

}

void Arrow::generate(
        QVector3D from,
        QVector3D to,
        float radius,
        int count) {
    float arrowLength = radius * 3;
    QVector3D look = to - from;
    QVector3D crossHelper = QVector3D(1, 2, 3);
    QVector3D normal = QVector3D::crossProduct(look, crossHelper).normalized() * radius;
    QVector3D look2 = look * ((from - to).length() - arrowLength) / (from - to).length();
    int edgesCount = count * 2 + 1;
    int edgeIndex = 0;
    edges.resize(edgesCount);
    edges[edgeIndex++] = Edge();
    edges[0].vertices.resize(count);
    QVector3D p1, p2, p1_next, p2_next;
    QMatrix4x4 m;
    m.rotate(360.0f / count, look);
    p1_next = from + normal;
    p2_next = from + look2 + normal;

    for (int i = 0; i < count; i++) {
        normal = m * normal;
        p1 = p1_next;
        p2 = p2_next;
        p1_next = from + normal;
        p2_next = from + look2 + normal;
        edges[edgeIndex++] =
        {{
             p1, p2, p2_next, p1_next
         }};
        edges[edgeIndex++] =
        {{
             p2, to, p2_next
         }};
        edges[0].vertices[i] = p1;
    }

    markVertexChanged();
    markNeedsPaint();
}
