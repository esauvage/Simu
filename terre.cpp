#include "terre.h"

using namespace std;

Terre::Terre()
    :PointMassif()
{
    setNom("Terre");
    setMasse(5.9722e24);
    setPos(QVector3D(152097701e3, 0, 0));
    setVit(QVector3D(0, 29.291e3, 0));
    // shared_ptr<PointMassif> a = make_shared<PointMassif>();
    // a->setPos(QVector3D(6389e3, 0, 0));
    // a->setParent(this);
    // a->setMasse(masse()/2.);
    // addPoint(a);
    // a = make_shared<PointMassif>();
    // a->setPos(QVector3D(-6389e3, 0, 0));
    // a->setParent(this);
    // a->setMasse(masse()/2.);
    // addPoint(a);
    // setMasse(0);
}
