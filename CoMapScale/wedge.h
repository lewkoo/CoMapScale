#ifndef WEDGE_H
#define WEDGE_H

#include <QPoint>
#include <QPen>
#include <QRect>
#include "global.h"
#include "mapmarker.h"

class QPainter;
class MapMarker;

class Wedge
{

public:
    static const int MAX_APERTURE_WIDTH; //Wedge aperture limit in pixels
    static const int MIN_APERTURE_WIDTH;
    static const float POTENTIAL_STRENGTH;
    static const int AP_CHANGE_DIST;  // Distance where wedge aperature function changes.
    static const int MIN_INTRUSION_DEPTH;

    Wedge ();
    Wedge (QColor colour);

    void init();
    //Wedge(QPoint screenPos, QColor colour, QRect viewport);
    void setWedge(QPoint screenPos, QRect viewport);
    void updatePotential();
    void resetPotentialDelta();
    void detectCollision(Wedge* otherWedge);
    void paint(QPainter *painter);

private:
    void setApertureByWidth(float width);
    Situation determineTargetSituation(QPoint screenPos);
    void setLegLengthAndAperature(Situation targetSit, QPoint screenPos);
    void setRotation(QPoint screenPos, Situation targetSit);
    void determineCornerRotation(QPoint screenPos, QPoint cornerPoint, QLine edge1, QLine edge2);
    bool correctRotation(QPoint screenPos);
    void correctAperture(QPoint screenPos);
    void extendLegs(QPoint screenPos);
    void setTriangle(QPoint screenPos);
    void setTriangle(QPoint screenPos, QPoint p1, QPoint p2);
    void addPotential(QPoint screenPos);

private:
    MapMarker* wedgeIcon;
    QColor colour;
    QPen pen;
    QLine lineBase, lineLeg1, lineLeg2;
    QRect viewport;
    float legLength;
    float aperture;
    float rotation;
    float angleAdjust;
    float intrusionDepth;
    float targetDistance;
    QPoint closestVertex;

    float potential;    //Measures deflection of rotation from other wedges.  Cumulative total.
    float potentialDelta;  //Amount of potential in the current update.
    float potentialMemory; //Remembers the last direction of potential when potential is 0;
    float resistanceDelta;  //Amount of resistance against returning to centre.
};

#endif // WEDGE_H
