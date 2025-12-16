#ifndef LIENRESSORT_H
#define LIENRESSORT_H

#include <memory>

class PointMateriel;

class LienRessort
{
public:
	LienRessort(std::shared_ptr<PointMateriel> A, std::shared_ptr<PointMateriel> B, double raideur, double amorti = 0, double lRepos = 0);
    void tick(int temps);
private:
    std::shared_ptr<PointMateriel> _A;
    std::shared_ptr<PointMateriel> _B;
	double _raideur;
	double _amorti;
	double _longueurRepos;
};

#endif // LIENRESSORT_H
