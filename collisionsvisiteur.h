#ifndef COLLISIONSVISITEUR_H
#define COLLISIONSVISITEUR_H

#include "pointmassif.h"

class CollisionsVisiteur
{
public:
	CollisionsVisiteur();
	static void detecte(QList<std::shared_ptr<PointMateriel> > &points);
};

#endif // COLLISIONSVISITEUR_H
