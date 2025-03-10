#include "lienressort.h"

#include "pointmassif.h"

using namespace std;

LienRessort::LienRessort(shared_ptr<PointMassif> A, shared_ptr<PointMassif> B, double raideur)
    :_A(A), _B(B), _raideur(raideur)
{
    _longueurRepos = _A->pos().distanceToPoint(_B->pos());
}

void LienRessort::tick(int temps)
{
    (void)temps;
    auto longueur = _A->pos().distanceToPoint(_B->pos());
    auto v = _B->pos() - _A->pos();
    v.normalize();
    auto f = (longueur - _longueurRepos) * _raideur;
    _A->addForce(v*f);
    _B->addForce(-v*f);
}
