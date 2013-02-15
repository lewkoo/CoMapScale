#include <QLine>
#include "math.h"
#include "utilities.h"
//#include "limits"

float Utilities::distance(QPoint p1, QPoint p2)
{
    float dist;
    float a, b, c;

    a = p1.x() - p2.x();
    b = p1.y() - p2.y();
    c = pow(a, 2) + pow(b, 2);

    dist = sqrt(c);

    return dist;
}

double Utilities::getAbsoluteAngle(QPoint point1, QPoint point2)
{
    double deltaX, deltaY;
    double angle;

    deltaX = point2.x() - point1.x();
    deltaY = point2.y() - point1.y();
    angle = atan2(deltaY, deltaX);

    return angle;
}

//d is a valid positive distance
//angle is in radians
QPoint Utilities::convertPolarToEuclidianCoordinates(double d, double angle)
{
    float x, y;

    x = (float)(cos(angle) * d);
    y = (float)(sin(angle) * d);

    return QPoint(x, y);
}

//Get the value t in the equation P = P0 + t(P1 - p0)
//at the point where this line intersects another line.
qreal Utilities::getIntersectionVariable(QLine line1, QLine line2, bool &linesParallel)
{
   qreal result = 0;
   qreal numerator;       // (x4 - x3)(y1 - y3) - (y4 - y3)(x1 - x3)
   qreal denominator;     // (y4 - y3)(x2 - x1) - (x4 - x3)(y2 - y1)

   numerator = ((qreal)(line2.p2().x() - line2.p1().x()) * (line1.p1().y() - line2.p1().y())) - ((qreal)(line2.p2().y() - line2.p1().y()) * (line1.p1().x() - line2.p1().x()));
   //numerator = ((qreal)(other.Point2.X - other.Point1.X) * (this.Point1.Y - other.Point1.Y)) - ((double)(other.Point2.Y - other.Point1.Y) * (this.Point1.X - other.Point1.X));

   denominator = ((qreal)(line2.p2().y() - line2.p1().y()) * (line1.p2().x() - line1.p1().x())) - ((qreal)(line2.p2().x() - line2.p1().x()) * (line1.p2().y() - line1.p1().y()));
   //denoninator = ((qreal)(other.Point2.Y - other.Point1.Y) * (this.Point2.X - this.Point1.X)) - ((double)(other.Point2.X - other.Point1.X) * (this.Point2.Y - this.Point1.Y));

   if (denominator != 0)
   {
       result = numerator / denominator;
       linesParallel = false;
   }
   else
   {
       linesParallel = true;
   }

   return result;
}

//bool Utilities::isNan(double value)
//{
//    return value != value;
//}

//bool Utilities::isInf(double value)
//{
//    return value < std::numeric_limits<double>::max() && value > -std::numeric_limits<double>::max();
//}


