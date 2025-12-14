#include "gravitevisiteur.h"

#include <QList>

using namespace std;

GraviteVisiteur::GraviteVisiteur() {}

void GraviteVisiteur::appliqueGravite(QList<shared_ptr <PointMassif> > &points)
{
    QList<shared_ptr<PointMassif> > pointsNus;
    for (const auto & p : points)
    {
        pointsNus << p->points();
    }
    for (int i = 0; i < pointsNus.size() - 1; ++i)
    {
        auto &c1 = pointsNus[i];
        for (int j = i + 1; j < pointsNus.size(); ++j)
        {
            auto &c2 = pointsNus[j];
            if (c1->parent() && (c1->parent() == c2->parent())) continue;
            //Les choses s'attirent en fonction de leur masse et en raison inverse du carré de leur distance
			double dist = 6.67430e-11 * c1->masse() * c2->masse()/(c1->pos(c1->parent()) - c2->pos(c2->parent())).lengthSquared();
			QVector3D f = dist * (c2->pos(c2->parent())-c1->pos(c1->parent())).normalized();
            c1->addForce(f);
            c2->addForce(-f);
        }
    }
}
