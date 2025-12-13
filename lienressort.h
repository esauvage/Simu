#ifndef LIENRESSORT_H
#define LIENRESSORT_H

#include <memory>

class PointMassif;

class LienRessort
{
public:
	LienRessort(std::shared_ptr<PointMassif> A, std::shared_ptr<PointMassif> B, double raideur, double amorti = 0, double lRepos = 0);
    void tick(int temps);
private:
    std::shared_ptr<PointMassif> _A;
    std::shared_ptr<PointMassif> _B;
	double _raideur;
	double _amorti;
	double _longueurRepos;
};

#endif // LIENRESSORT_H
