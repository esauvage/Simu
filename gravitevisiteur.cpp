#include "gravitevisiteur.h"

#include <QList>

GraviteVisiteur::GraviteVisiteur() {}

void GraviteVisiteur::appliqueGravite(QList<PointMassif> &points)
{
    for (int i = 0; i < points.size() - 1; ++i)
    {
        auto &c1 = points[i];
        for (int j = i + 1; j < points.size(); ++j)
        {
            auto &c2 = points[j];
            //Les choses s'attirent en fonction de leur masse et en raison inverse du carré de leur distance
            double dist = 6.67430e-11 * c1.masse() * c2.masse()/(c1.pos() - c2.pos()).lengthSquared();
            QVector3D f = dist * (c2.pos()-c1.pos()).normalized();
            c1.addForce(f);
            c2.addForce(-f);
        }
    }
}
