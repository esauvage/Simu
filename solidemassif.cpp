#include "solidemassif.h"

#include <QDebug>

using namespace std;

SolideMassif::SolideMassif() {}

void SolideMassif::tick(int temps)
{
    QVector3D centre;
    QVector3D vitCentre;
    double masseTotale = 0;
    for (auto & p : _points)
    {
        p->tick(temps);
        centre += p->pos() * p->masse();
        masseTotale += p->masse();
    }
    centre /= masseTotale;
	vitCentre = (centre - pos())/temps;
    QVector3D a;
    QVector3D moment;
    double momentInertie;
    for (auto & p : _points)
    {
        p->setPos(p->pos() - centre);
        p->setVit(p->vit() - vitCentre);
        if (p->masse())
        {
            a += p->force();
        }
        moment += QVector3D::crossProduct(p->pos() - centre, p->force());
        momentInertie = (p->pos() - centre).lengthSquared() * p->masse();
    }
    a /= masseTotale;
	_momentCinetique = moment * temps;
	_vitAngle = _momentCinetique/momentInertie;
 //   setVit(vit() + a * temps);
    setVit(vitCentre);
    centre += vit() * temps;
    setPos(centre);
    // setPos(pos() + vit() * temps);
    qDebug() << nom() << "Position : " << pos() << "Vitesse : " << vit() << "Vitesse Angulaire : " << _vitAngle ;
}

void SolideMassif::clearPoints()
{
    _points.clear();
}

void SolideMassif::addPoint(const std::shared_ptr<PointMassif> &f)
{
    _points << f;
}

QList<shared_ptr<PointMassif> > SolideMassif::points()
{
    return _points;
    // QList<PointMassif *> r;
    // for (const auto & p : _points)
    // {
    //     r << p.get();
    // }
    // return r;
}

void SolideMassif::clearForces()
{
    for (auto & p : _points)
    {
        p->clearForces();
    }
}
