#ifndef GRAVITEVISITEUR_H
#define GRAVITEVISITEUR_H

#include "pointMateriel.h"

class GraviteVisiteur
{
public:
    GraviteVisiteur();
    static void appliqueGravite(QList<std::shared_ptr<PointMateriel> > &points);
};

#endif // GRAVITEVISITEUR_H
