#include "table.h"

Table::Table(float width, float length, float height)
{
    this->width = width;
    this->length = length;
    this->height = height;

    float legW = width * 0.2f,
            legH = height * 0.99f;
    float bigGPW = width,
            bigGPL = length,
            bigGPH = height * 0.01f;
    float smallGPW = 0.75 * width,
            smallGPL = 0.75 * length,
            smallGPH = 0.01 * height;
    float smallLegW = width * 0.05f,
            smallLegH = 0.1 * height;
    float distBtwSmallLegs = (smallGPL -3.0f*smallLegW) / 5.0f;

    float ironLegHeight = height * 0.05f;
    legs.append(new Leg(legW, legW, legH, QVector3D(-width/2.0f + legW/2.0f, legH/2.0f - ironLegHeight, -length/2.0f + legW/2.0f)));
    legs.append(new Leg(legW, legW, legH, QVector3D(width/2.0f - legW/2.0f, legH/2.0f - ironLegHeight, -length/2.0f + legW/2.0f)));
    legs.append(new Leg(legW, legW, legH, QVector3D(width/2.0f - legW/2.0f, legH/2.0f - ironLegHeight, length/2.0f - legW/2.0f)));
    legs.append(new Leg(legW, legW, legH, QVector3D(-width/2.0f + legW/2.0f, legH/2.0f - ironLegHeight, length/2.0f - legW/2.0f)));

    float ironLegR = legW * 0.8 / 2;
    float ironLegTop = legH - ironLegHeight;
    ironLegs.append(new IronLeg(QVector3D(-width/2.0f + legW/2.0f, ironLegTop, -length/2.0f + legW/2.0f), ironLegR, ironLegHeight));
    ironLegs.append(new IronLeg(QVector3D(width/2.0f - legW/2.0f, ironLegTop, -length/2.0f + legW/2.0f), ironLegR, ironLegHeight));
    ironLegs.append(new IronLeg(QVector3D(width/2.0f - legW/2.0f, ironLegTop, length/2.0f - legW/2.0f), ironLegR, ironLegHeight));
    ironLegs.append(new IronLeg(QVector3D(-width/2.0f + legW/2.0f, ironLegTop, length/2.0f - legW/2.0f), ironLegR, ironLegHeight));

    bigPanel = new GlassPanel(bigGPW, bigGPL, bigGPH, QVector3D(0, legH + bigGPH/2.0f, 0));
    bigPanelSides = new GlassPanelSides(bigGPW, bigGPL, bigGPH, QVector3D(0, legH + bigGPH/2.0f, 0));
    smallPanel = new GlassPanel(smallGPW, smallGPL, smallGPH, QVector3D(0, legH - smallLegH - smallGPH/2.0f, 0));
    smallPanelSides = new GlassPanelSides(smallGPW, smallGPL, smallGPH, QVector3D(0, legH - smallLegH - smallGPH/2.0f, 0));

    smallLegs.append(new Leg(smallLegW, smallLegW, smallLegH, QVector3D(0, legH - smallLegH/2.0f, -distBtwSmallLegs/2.0f)));
    smallLegs.append(new Leg(smallLegW, smallLegW, smallLegH, QVector3D(0, legH - smallLegH/2.0f, distBtwSmallLegs/2.0f)));
    smallLegs.append(new Leg(smallLegW, smallLegW, smallLegH, QVector3D(0, legH - smallLegH/2.0f, -1.5 * distBtwSmallLegs)));
    smallLegs.append(new Leg(smallLegW, smallLegW, smallLegH, QVector3D(0, legH - smallLegH/2.0f, 1.5 * distBtwSmallLegs)));

}

Table::~Table()
{
    for (int i = 0; i < legs.length(); i++) {
        delete legs[i];
    }
    for (int i = 0; i < smallLegs.length(); i++) {
        delete smallLegs[i];
    }
    delete bigPanel;
    delete bigPanelSides;
    delete smallPanel;
    delete smallPanelSides;

}
