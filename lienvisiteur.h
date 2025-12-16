#ifndef LIENVISITEUR_H
#define LIENVISITEUR_H

#include <QList>

class PointMateriel;

class LienVisiteur
{
public:
    LienVisiteur();
	static void appliqueLien(QList<std::shared_ptr<PointMateriel> > &points, int temps);
};

#endif // LIENVISITEUR_H
