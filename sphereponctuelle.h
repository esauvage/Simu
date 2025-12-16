#ifndef SPHEREPONCTUELLE_H
#define SPHEREPONCTUELLE_H

#include "pointMateriel.h"

class SpherePonctuelle : public PointMateriel
{
public:
    SpherePonctuelle(double rayon = 0);
private:
    double _rayon;
};

#endif // SPHEREPONCTUELLE_H
