#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPoint>
#include <QtGlobal>
#include "math.h"
#include "limits"

class Utilities
{
public:
    static const double ONE_DEGREE = M_PI / 180;
    static const double TWO_PI = M_PI *2;
    Utilities();
    //virtual ~Utilities() = 0;

    static float distance(QPoint p1, QPoint p2);

    //Returns radians
    static double getAbsoluteAngle(QPoint point1, QPoint point2);

    static QPoint convertPolarToEuclidianCoordinates(double d, double angle);
    static qreal getIntersectionVariable(QLine line1, QLine line2, bool &linesParallel);

    static bool isNan(double value) {return value != value;}

    static bool isInf(double value) {return value >= std::numeric_limits<double>::max() || value <= -std::numeric_limits<double>::max();}
};

#endif // UTILITIES_H
