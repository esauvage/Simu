#include "lienvisiteur.h"

#include "lienressort.h"
#include "pointmassif.h"

using namespace std;

LienVisiteur::LienVisiteur() {}

void LienVisiteur::appliqueLien(QList<shared_ptr <PointMassif> > &points)
{
    for (auto & p : points)
    {
        for (auto & l : p->liens())
        {
            l->tick(10);
        }
    }
}
