#ifndef GRAVITEVISITEUR_H
#define GRAVITEVISITEUR_H

#include "pointmassif.h"

class GraviteVisiteur
{
public:
    GraviteVisiteur();
    static void appliqueGravite(QList<std::shared_ptr<PointMateriel> > &points);
};

#endif // GRAVITEVISITEUR_H
