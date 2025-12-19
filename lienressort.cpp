#include "lienressort.h"

#include "pointMateriel.h"
#include "force.h"

using namespace std;

LienRessort::LienRessort(shared_ptr<PointMateriel> A, shared_ptr<PointMateriel> B, double raideur, double amorti, double lRepos)
	:_A(A), _B(B), _raideur(raideur), _amorti(amorti), _longueurRepos(lRepos)
{
	if (!_longueurRepos) _longueurRepos = _A->pos().distanceToPoint(_B->pos());
}

void LienRessort::tick(int temps)
{
    (void)temps;
    auto v = _B->pos() - _A->pos();
	auto longueur = v.length();
	v.normalize();
	auto f = (longueur - _longueurRepos) * _raideur;
    _A->addForce(Force(_B, v*f));
    _B->addForce(Force(_A, -v*f));
	f = QVector3D::dotProduct(v, _B->vit() - _A->vit()) * _amorti;
    _A->addForce(Force(_B, -v * f));
    _B->addForce(Force(_B, v * f));
}
