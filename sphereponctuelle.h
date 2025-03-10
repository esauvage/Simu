#ifndef SPHEREPONCTUELLE_H
#define SPHEREPONCTUELLE_H

#include "pointmassif.h"

class SpherePonctuelle : public PointMassif
{
public:
    SpherePonctuelle(double rayon = 0);
private:
    double _rayon;
};

#endif // SPHEREPONCTUELLE_H
