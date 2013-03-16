#include <QPainter>
#include <QLine>
#include <QPen>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "wedge.h"
#include "utilities.h"
#include "math.h"
#include "mappingwidget.h"
#include <QGraphicsScene>



const float Wedge::POTENTIAL_STRENGTH = Utilities::ONE_DEGREE;
const int Wedge::MAX_APERTURE_WIDTH = 80;
const int Wedge::MIN_APERTURE_WIDTH = 5;
const int Wedge::AP_CHANGE_DIST = 800;
const int Wedge::MIN_INTRUSION_DEPTH = 10;
const qreal Wedge::ICON_HEIGHT = 35;
const qreal Wedge::ICON_WIDTH = 40;

Wedge::Wedge()
{
    init();
    this->colour = QColor("black");
}

Wedge::Wedge(QColor colour)
{
    this->colour = colour;
    init();
}

void Wedge::setWedgeIcon(MapMarker* marker){
    wedgeIcon = marker;
}

void Wedge::init()
{
    lineBase = QLine(0, 0, 0, 0);
    lineLeg1 = QLine(0, 0, 0, 0);
    lineLeg2 = QLine(0, 0, 0, 0);

    QPoint* temp = calculateIconLocation();

    button = new WedgeIcon();
    button->setRect(temp->x(),temp->y(),ICON_WIDTH, ICON_HEIGHT);
    if(MappingWidget::getScene() != NULL)
    MappingWidget::getScene()->addItem(button);

    wedgeIcon = NULL;
    //wedgeIcon->setMarkerType(MapMarker::WedgePeerBlueType);

    colour.setAlpha(200);
    pen.setColor(colour);
    pen.setWidth(5);

    potential = 0;
    potentialDelta = 0;
    potentialMemory = 0;
    resistanceDelta = 0;
}

QPoint* Wedge::calculateIconLocation(){

    QPoint* temp = NULL;

    if(wedgeIcon != NULL){
    int x = (lineBase.x2() + lineBase.x1())/2;
    int y = (lineBase.y2() + lineBase.y1())/2;


    //int distance = sqrt( (pow(lineBase.x2()-lineBase.x1(),2)) + ( pow ( lineBase.y2()-lineBase.y1(),2)) );

    x = x-20;
    y = y-20;

    temp = new QPoint(x,y);

    }



    return temp;

}

void Wedge::paint(QPainter *painter)
{
    painter->setPen(pen);
    painter->drawLine(lineBase);
    painter->drawLine(lineLeg1);
    painter->drawLine(lineLeg2);

    QPoint* temp = calculateIconLocation();
    button->setRect(temp->x(),temp->y(),ICON_WIDTH, ICON_HEIGHT);
    button->setPen(QPen(QBrush(),0));
    button->setBrush(QBrush(QColor(0,0,0,150)));

    //if(distance >= wedgeIcon->pixmap().width()){ //allows wedge icon to disappear when the line gets too small - smaller than the icon size
    painter->drawPixmap(temp->x(),temp->y(),wedgeIcon->pixmap());
   // }




}



void Wedge::setWedge(QPoint screenPos, QRect viewport)
{
    if (screenPos.x() < 0 || screenPos.x() > viewport.width() ||
            screenPos.y() < 0 || screenPos.y() > viewport.height())
    {
        this->viewport = viewport;
        float apertureWidth;
        Situation targetSit = determineTargetSituation(screenPos);

        setLegLengthAndAperature(targetSit, screenPos);
        setRotation(screenPos, targetSit);
        this->setTriangle(screenPos);

        apertureWidth = QLineF(lineBase).length();

        if (apertureWidth > MAX_APERTURE_WIDTH)
        {
            //Recalculate the legs
            setApertureByWidth(MAX_APERTURE_WIDTH);
            this->setTriangle(screenPos);
        }

        if (targetSit == SitNorth || targetSit == SitSouth || targetSit == SitEast || targetSit == SitWest)
        {
            this->correctRotation(screenPos);
        }

        this->addPotential(screenPos);

        this->correctAperture(screenPos);

        apertureWidth = QLineF(lineBase).length();
        if (apertureWidth < MIN_APERTURE_WIDTH)
        {
            setApertureByWidth(MIN_APERTURE_WIDTH);
            this->setTriangle(screenPos);
        }

        this->extendLegs(screenPos);
    }
    else
    {
        button->setVisible(false);
        init();
    }
}

void Wedge::addPotential(QPoint screenPos)
{
    float potentialStrength;
    float rawRotation;
    bool inBounds = true;
    QPoint p1, p2;
    float potentialCorrection = 0;

    if (this->potential > 0)
        potentialCorrection = -1;
    else if (this->potential < 0)
        potentialCorrection = 1;

    //Add rotation from potential
    //potentialStrength = POTENTIAL_STRENGTH / (float)math.pow((this.LegLength / 100), 1);
    potentialStrength = Wedge::POTENTIAL_STRENGTH / (this->legLength / 100);
    rawRotation = rotation;

    rotation = rawRotation + this->potential * potentialStrength;
    this->setTriangle(screenPos);
    p1 = this->lineBase.p1();
    p2 = this->lineBase.p2();
    inBounds = (this->viewport.contains(p1) && this->viewport.contains(p2));

    while (!inBounds && potential != 0)
    {
        //rotation = rawRotation + (this.potential - potentialCorrection) * potentialStrength;//PotentialStrength;
        potential += potentialCorrection;
        rotation = rawRotation + this->potential * potentialStrength;//PotentialStrength;
        this->setTriangle(screenPos);
        p1 = lineBase.p1();
        p2 = lineBase.p2();
        inBounds = (this->viewport.contains(p1) && this->viewport.contains(p2));
    }
}

void Wedge::updatePotential()
{
    //Update the wedge's potential
    if (potentialDelta == 0)
    {
        //Return to normal.
        if (potential > 0 && resistanceDelta <= 0)
        {
            potential -= 1;
        }
        else if (potential < 0 && resistanceDelta >= 0)
        {
            potential += 1;
        }
    }
    else
    {
        //Update based on the delta.
        if (potentialDelta > 0)
        {
            potential += 1;
        }
        else if (potentialDelta < 0)
        {
            potential -= 1;
        }
    }
}

void Wedge::resetPotentialDelta()
{
    potentialDelta = 0;
    resistanceDelta = 0;
}

//See if this wedge contains a vertex from the other wedge.
void Wedge::detectCollision(Wedge* otherWedge)
{
    static const float CONTAINMENT_THRESHOLD = 400; //Creates a boundary around the triangle.
    static const float DEAD_ZONE_THRESHOLD = 2.0f * CONTAINMENT_THRESHOLD;
    bool containsP1 = true;
    bool containsP2 = true;
    bool deadZoneContainsP1 = true;
    bool deadZoneContaintP2 = true;
    QLine toVertex1, toVertex2; //Represent vectors with QLines. Can get the x, y lengths with dx/dy.
    QLine edge;
    double crossProduct1, crossProduct2;

    //if (this.triangle.CountVectors >= 3 && otherWedge.triangle.CountVectors >= 3)
    if (otherWedge != NULL)
    {
        //Walk around the edges.  If any cross product is negative, then the point is to the left of the edge, thus outside the triangle.
        for (int i = 0; i < 3; i++)
        {
            switch (i)
            {
            case 0:
                edge = this->lineLeg1;
                break;
            case 1:
                edge = this->lineBase;
                break;
            case 2:
                edge = this->lineLeg2;
                break;
            }

            //toVertex1 = otherWedge.triangle.GetVector(1) - this.triangle.GetVector(i);
            toVertex1 = QLine(edge.p1(), otherWedge->lineBase.p1());
            //toVertex2 = otherWedge.triangle.GetVector(2) - this.triangle.GetVector(i);
            toVertex2 = QLine(edge.p1(), otherWedge->lineBase.p2());

            crossProduct1 = (edge.dx() * toVertex1.dy()) - (edge.dy() * toVertex1.dx());
            crossProduct2 = (edge.dx() * toVertex2.dy()) - (edge.dy() * toVertex2.dx());

            //Positive - left
            //Negative - right
            if (crossProduct1 > CONTAINMENT_THRESHOLD)
            {
                containsP1 = false;
            }

            if (crossProduct1 > DEAD_ZONE_THRESHOLD)
            {
                deadZoneContainsP1 = false;
            }

            if (crossProduct2 > CONTAINMENT_THRESHOLD)
            {
                containsP2 = false;
            }

            if (crossProduct2 > DEAD_ZONE_THRESHOLD)
            {
                deadZoneContaintP2 = false;
            }
        }

        //If a wedge collision is detected, nudge the wedges apart.
        if (containsP1 || containsP2)
        {
            if (containsP1 && containsP2)
            {
                if (this->potentialMemory > 0)
                {
                    this->potentialDelta += 1;
                    otherWedge->potentialDelta -= 1;
                }
                else
                {
                    this->potentialDelta -= 1;
                    otherWedge->potentialDelta += 1;
                }
            }
            else
            {
                if (containsP1)
                {
                    //Wedge contains other wedge's point 1.
                    //Rotate clockwise.  Other wedge rotates counter clockwise.
                    this->potentialDelta += 1;
                    otherWedge->potentialDelta -= 1;
                    this->potentialMemory = 1;
                }

                if (containsP2)
                {
                    //Wedge contains other wedge's point 2.
                    //Rotate counter clockwise.  Other wedge rotates clockwise.
                    this->potentialDelta -= 1;
                    otherWedge->potentialDelta += 1;
                    this->potentialMemory = -1;
                }
            }
        }
        else if (deadZoneContainsP1 || deadZoneContaintP2)
        {
            //If the wedges don't collide, but are in one anothers' dead zones, resist moving back to normal position.
            if (deadZoneContainsP1)
            {
                //Wedge's dead zone contains other wedge's point 1.
                //Resist counter clockwise motion.  Other wedge resists clockwise.
                this->resistanceDelta += 1;
                otherWedge->resistanceDelta -= 1;
            }

            if (deadZoneContaintP2)
            {
                //Wedge's dead zone contains other wedge's point 2.
                //Resist clockwise motion.  Other wedge resists counter clockwise.
                this->resistanceDelta -= 1;
                otherWedge->resistanceDelta += 1;
            }
        }
    }
}

void Wedge::setApertureByWidth(float width)
{
    //Half the aperature angle is equal to the sin of y/h (1/2 width over leg length)
    float halfAperture = (float)sin(((0.5f * width) / this->legLength));
    this->aperture = halfAperture * 2;
}

void Wedge::setTriangle(QPoint screenPos)
{
    QPoint p1, p2;
    double shift = this->aperture /2;

    p1 = screenPos + Utilities::convertPolarToEuclidianCoordinates(this->legLength, this->rotation + shift);
    p2 = screenPos + Utilities::convertPolarToEuclidianCoordinates(this->legLength, this->rotation - shift);

    this->lineBase = QLine(p1, p2);
    //this->lineLeg1 = QLine(p1, screenPos);
    this->lineLeg1 = QLine(screenPos, p1);
    this->lineLeg2 = QLine(p2, screenPos);
}

void Wedge::setTriangle(QPoint screenPos, QPoint p1, QPoint p2)
{
    this->lineBase = QLine(p1, p2);
    //this->lineLeg1 = QLine(p1, screenPos);
    this->lineLeg1 = QLine(screenPos, p1);
    this->lineLeg2 = QLine(p2, screenPos);
}

void Wedge::determineCornerRotation(QPoint screenPos, QPoint cornerPoint, QLine edge1, QLine edge2)
{
    double startAngle, startRotation; //The angle of the line form the target to the corner.
    QLine line1, line2;
    double t1, t2;     //Parametric values for each line.
    bool linesParallel1;
    bool linesParallel2;

    //Start with line1 from the target to the nearest corner.
    startAngle = Utilities::getAbsoluteAngle(screenPos, cornerPoint);

    if (!Utilities::isNan(startAngle) && !Utilities::isInf(startAngle))
    {
        this->rotation = startAngle - (this->aperture / 2.0);
        startRotation = this->rotation;

        this->setTriangle(screenPos);

        line1 = QLine(screenPos, lineBase.p1());
        line2 = QLine(screenPos, lineBase.p2());

        t1 = Utilities::getIntersectionVariable(line1, edge1, linesParallel1);
        t2 = Utilities::getIntersectionVariable(line2, edge2, linesParallel2);

        //If t2 is negative, it points away from the screen.  If null, it is parallel with the screen edge.
        while ((linesParallel2 || t2 < 0 || t1 < t2) && startRotation < (rotation + Utilities::TWO_PI))
        {
            this->rotation += this->angleAdjust;

            this->setTriangle(screenPos);

            line1 = QLine(screenPos, lineBase.p1());
            line2 = QLine(screenPos, lineBase.p2());

            t1 = Utilities::getIntersectionVariable(line1, edge1, linesParallel1);
            t2 = Utilities::getIntersectionVariable(line2, edge2, linesParallel2);
        }
    }
}
//Rotate until the whole wedge is in bounds.
bool Wedge::correctRotation(QPoint screenPos)
{
    bool success = true;
    QPoint p1, p2;
    bool containsP1, containsP2;
    bool triedLeft = false;
    bool triedRight = false;
    float startRotation = this->rotation;
    QRect correctionBound;

    correctionBound = viewport;
    //correctionBound.Inflate(-AperatureBorder, -AperatureBorder);

    p1 = QPoint(this->lineBase.p1());
    p2 = QPoint(this->lineBase.p2());

    containsP1 = correctionBound.contains(p1);
    containsP2 = correctionBound.contains(p2);

    while ((!containsP1 || !containsP2) && startRotation < (this->rotation + Utilities::TWO_PI) && (!triedLeft || !triedRight))
    {
        if (containsP1)
        {
            //Rotate left.
            rotation += this->angleAdjust;
            triedLeft = true;
        }
        else
        {
            //Rotate right.
            rotation -= this->angleAdjust;
            triedRight = true;
        }

        setTriangle(screenPos);

        p1 = QPoint(this->lineBase.p1());
        p2 = QPoint(this->lineBase.p2());

        containsP1 = correctionBound.contains(p1);
        containsP2 = correctionBound.contains(p2);
    }

    if (!containsP1 || !containsP2)
    {
        success = false;
    }

    return success;
}

void Wedge::correctAperture(QPoint screenPos)
{
    QPoint p1, p2;
    bool containsP1, containsP2;
    bool correctRotationSuccess = true;
    QRect correctionBound;

    correctionBound = viewport;
    //correctionBound.Inflate(-AperatureBorder, -AperatureBorder);

    p1 = lineBase.p1();
    p2 = lineBase.p2();

    containsP1 = correctionBound.contains(p1);
    containsP2 = correctionBound.contains(p2);

    while (this->aperture > 0 && (!containsP1 || !containsP2))
    {
        while (this->aperture > 0 && ((!containsP1 && !containsP2) || (!correctRotationSuccess && (!containsP1 || !containsP2))))
        {
            this->aperture -= this->angleAdjust;

            this->setTriangle(screenPos);

            p1 = lineBase.p1();
            p2 = lineBase.p2();

            containsP1 = correctionBound.contains(p1);
            containsP2 = correctionBound.contains(p2);

            correctRotationSuccess = true;
        }

        correctRotationSuccess = this->correctRotation(screenPos);

        p1 = lineBase.p1();
        p2 = lineBase.p2();

        containsP1 = correctionBound.contains(p1);
        containsP2 = correctionBound.contains(p2);
    }
}

 void Wedge::extendLegs(QPoint screenPos)
{
    QPoint point1, point2;
    double legExtension;

    //Extend the legs for rotated wedges.
    legExtension = fabs(sin(2 * this->rotation)) * (this->intrusionDepth);
    //legExtension = ((Math.Abs(MathHelper.PiOver4 - ((MathHelper.PiOver4 + this.rotation) % MathHelper.PiOver2))) / MathHelper.PiOver4) * this.intrusionDepth;

    point1 = screenPos + Utilities::convertPolarToEuclidianCoordinates(legLength + legExtension, this->rotation + (this->aperture / 2));
    point2 = screenPos + Utilities::convertPolarToEuclidianCoordinates(legLength + legExtension, this->rotation - (this->aperture / 2));

    this->setTriangle(screenPos, point1, point2);
}

void Wedge::setRotation(QPoint screenPos, Situation targetSit)
{
    QPoint vertex1, vertex2;
    QLine edge1, edge2;

    switch (targetSit)
    {
    case SitNorth:
        this->rotation = M_PI_2;
        break;
    case SitSouth:
        this->rotation = -M_PI_2;
        break;
    case SitEast:
        this->rotation = M_PI;
        break;
    case SitWest:
        this->rotation = 0;
        break;
    case SitNorthWest:
        vertex1 = QPoint(0, viewport.height());
        vertex2 = QPoint(viewport.width(), 0);
        edge1 = QLine(this->closestVertex, vertex1);
        edge2 = QLine(this->closestVertex, vertex2);
        determineCornerRotation(screenPos, this->closestVertex, edge1, edge2);
        break;
    case SitNorthEast:
        vertex1 = QPoint(0, 0);
        vertex2 = QPoint(viewport.width(), viewport.height());
        edge1 = QLine(this->closestVertex, vertex1);
        edge2 = QLine(this->closestVertex, vertex2);
        determineCornerRotation(screenPos, this->closestVertex, edge1, edge2);
        break;
    case SitSouthWest:
        vertex1 = QPoint(viewport.width(), viewport.height());
        vertex2 = QPoint(0, 0);
        edge1 = QLine(this->closestVertex, vertex1);
        edge2 = QLine(this->closestVertex, vertex2);
        determineCornerRotation(screenPos, this->closestVertex, edge1, edge2);
        break;
    case SitSouthEast:
        vertex1 = QPoint(viewport.width(), 0);
        vertex2 = QPoint(0, viewport.height());
        edge1 = QLine(this->closestVertex, vertex1);
        edge2 = QLine(this->closestVertex, vertex2);
        determineCornerRotation(screenPos, this->closestVertex, edge1, edge2);
        break;
    default:
        this->rotation = 0;
        break;
    }
}

void Wedge::setLegLengthAndAperature(Situation targetSituation, QPoint screenPos)
{
    double logTerm;

    switch (targetSituation)
    {
        case SitNorth:
            this->targetDistance = -screenPos.y();
            break;
        case SitSouth:
            this->targetDistance = screenPos.y() - viewport.height();
            break;
        case SitEast:
            this->targetDistance = screenPos.x() - viewport.width();
            break;
        case SitWest:
            this->targetDistance = -screenPos.x();
            break;
        case SitNorthWest:
            closestVertex = QPoint(0, 0);
            this->targetDistance = Utilities::distance(screenPos, closestVertex);
            break;
        case SitNorthEast:
            closestVertex = QPoint(viewport.width(), 0);
            this->targetDistance = Utilities::distance(screenPos, closestVertex);
            break;
        case SitSouthWest:
            closestVertex = QPoint(0, viewport.height());
            this->targetDistance = Utilities::distance(screenPos, closestVertex);
            break;
        case SitSouthEast:
            closestVertex = QPoint(viewport.width(), viewport.height());
            this->targetDistance = Utilities::distance(screenPos, closestVertex);
            break;
        default:
            break;
    }

    //Original leg length function
    logTerm = log((this->targetDistance + 20.0) / 12.0);
    this->intrusionDepth = (float)(logTerm * 10.0);
    this->legLength = (this->targetDistance + this->intrusionDepth);

    //Use sigmoid in place of log function to shift growth to greater distances

    //(1/((1+exp(-(x-1200)/100))^(1/5))*50)
    //const int min = AperatureBorder + 1;        //Determines min intrusion depth.
    //const double scale = 50.0 - min;   //Determines max intrusion depth.
    //const double shift = 1200.0; //Shifts the function away from 0 centre.
    //const double line = 100.0;    //Makes the function more linear.
    //const double growth = 1.0 / 5.0;  //Shifts the maximum growth from centre toward an asymptote.

    //10+(40-10/(1+exp(-(x-800)/150))^(3/4))
    //const int min = AperatureBorder + 1;        //Determines min intrusion depth.
    //const int min = 13;
    //const float scale = 40.0f - min;   //Determines max intrusion depth.
    //const float shift = 800.0f; //Shifts the function away from 0 centre.
    //const float line = 150.0f;    //Makes the function more linear.
    //const float growth = 0.75f;  //Shifts the maximum growth from centre toward an asymptote.

    //this.intrusionDepth = (float)(min + (scale / Math.Pow((1.0 + (Math.Exp(-(distance - shift) / line))), growth)));
    //this.legLength = (float)(distance) + this.intrusionDepth;

    this->angleAdjust = Utilities::ONE_DEGREE / (this->legLength / 10);

    if (targetDistance < AP_CHANGE_DIST)
    {
        //Gustafson's formula
        this->aperture = (float)((5 + (targetDistance * 0.3)) / this->legLength);
    }
    else
    {
        this->aperture = (-targetDistance / 2000) + 0.6;

        if (aperture < 0)
        {
            aperture = 0;
        }

        this->intrusionDepth = (-targetDistance / 100) + 50;

        if (intrusionDepth < MIN_INTRUSION_DEPTH)
        {
            intrusionDepth = MIN_INTRUSION_DEPTH;
        }

        this->legLength = this->targetDistance + this->intrusionDepth;
    }

    //Reduce aperature growth for larger distances.
    //this.aperature = (float)((5 + (distance * 0.15)) / this.legLength);
    //this.aperature = (float)((10 + (this.targetDistance * 0.10)) / this.legLength);
}

Situation Wedge::determineTargetSituation(QPoint screenPos)
{
    Situation situation;

    if (screenPos.x() < 0)
    {
        if (screenPos.y() < 0)
        {
            situation = SitNorthWest;
        }
        else if (screenPos.y() > viewport.height())
        {
            situation = SitSouthWest;
        }
        else
        {
            situation = SitWest;
        }
    }
    else if (screenPos.x() > viewport.width())
    {
        if (screenPos.y() < 0)
        {
            situation = SitNorthEast;
        }
        else if (screenPos.y() > viewport.height())
        {
            situation = SitSouthEast;
        }
        else
        {
            situation = SitEast;
        }
    }
    else
    {
        if (screenPos.y() < 0)
        {
            situation = SitNorth;
        }
        else if (screenPos.y() > viewport.height())
        {
            situation = SitSouth;
        }
        else
        {
            situation = SitCentre;
        }
    }

    return situation;
}
