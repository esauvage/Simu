#ifndef GRAVITEVISITEUR_H
#define GRAVITEVISITEUR_H

#include "pointmassif.h"

class GraviteVisiteur
{
public:
    GraviteVisiteur();
    static void appliqueGravite(QList<PointMassif> &points);
};

#endif // GRAVITEVISITEUR_H
