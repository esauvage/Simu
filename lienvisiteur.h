#ifndef LIENVISITEUR_H
#define LIENVISITEUR_H

#include <QList>

class PointMassif;

class LienVisiteur
{
public:
    LienVisiteur();
    static void appliqueLien(QList<std::shared_ptr<PointMassif> > &points);
};

#endif // LIENVISITEUR_H
