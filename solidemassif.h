#ifndef SOLIDEMASSIF_H
#define SOLIDEMASSIF_H

#include "pointmassif.h"
class SolideMassif
{
public:
    SolideMassif();
    void tick(int temps);
    void clearPoints();
    void addPoint(const PointMassif &f);

private:
    QString _nom;
    QList<PointMassif> _points;
};

#endif // SOLIDEMASSIF_H
