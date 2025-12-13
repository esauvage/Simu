#include "lienressort.h"

#include "pointmassif.h"

using namespace std;

LienRessort::LienRessort(shared_ptr<PointMassif> A, shared_ptr<PointMassif> B, double raideur, double amorti, double lRepos)
	:_A(A), _B(B), _raideur(raideur), _amorti(amorti), _longueurRepos(lRepos)
{
	if (!_longueurRepos) _longueurRepos = _A->pos().distanceToPoint(_B->pos()) * 0.875;
}

void LienRessort::tick(int temps)
{
    (void)temps;
    auto longueur = _A->pos().distanceToPoint(_B->pos());
    auto v = _B->pos() - _A->pos();
    v.normalize();
    auto f = (longueur - _longueurRepos) * _raideur * (_A->masse() +  _B->masse());
	_A->addForce(v*f);
	_B->addForce(-v*f);
	_A->addForce(v * QVector3D::dotProduct(v, _B->vit() - _A->vit()) * _amorti * _A->masse());
	_B->addForce(v * QVector3D::dotProduct(v, _A->vit() - _B->vit()) * _amorti * _B->masse());
}
