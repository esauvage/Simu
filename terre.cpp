#include "terre.h"

#include <QDebug>

#include "sphereponctuelle.h"

using namespace std;

Terre::Terre()
    :SolideMassif()
{
    const auto raideur = 1e15;
    setNom("Terre");
    setMasse(5.9722e24);
    setPos(QVector3D(1.52097701e11, 0, 0));
    setVit(QVector3D(0, 29.291e3, 0));
    shared_ptr<SpherePonctuelle> a = make_shared<SpherePonctuelle>(6389e3/2.);
    a->setPos(QVector3D(6389e3, 0, 0));
    a->setVit(QVector3D(0, 464.6212, 0));
    a->setParent(this);
    a->setMasse(masse()/7.);
    addPoint(a);
    a = make_shared<SpherePonctuelle>(6389e3/2.);
    a->setPos(QVector3D(-6389e3, 0, 0));
    a->setVit(QVector3D(0, -464.6212, 0));
    a->setParent(this);
    a->setMasse(masse()/7.);
    addPoint(a);
    a = make_shared<SpherePonctuelle>(6389e3/2.);
    a->setPos(QVector3D(0, 6389e3, 0));
    a->setVit(QVector3D(-464.6212, 0, 0));
    a->setParent(this);
    a->setMasse(masse()/7.);
    addPoint(a);
    a = make_shared<SpherePonctuelle>(6389e3/2.);
    a->setPos(QVector3D(0, -6389e3, 0));
    a->setVit(QVector3D(464.6212, 0, 0));
    a->setParent(this);
    a->setMasse(masse()/7.);
    addPoint(a);
    addLien(points().at(0)->addLien(points().at(2), raideur));
    addLien(points().at(0)->addLien(points().at(3), raideur));
    addLien(points().at(1)->addLien(points().at(2), raideur));
    addLien(points().at(1)->addLien(points().at(3), raideur));
    a = make_shared<SpherePonctuelle>(6389e3/2.);
    a->setPos(QVector3D(0, 0, 0));
    a->setVit(QVector3D(0, 0, 0));
    a->setParent(this);
    a->setMasse(masse()/7.);
    for (auto & p : points())
    {
        //Chaque pointeur sur le lien est stocké 3 fois : une fois dans le solide, pour le visiteur, et une fois dans les objets liés,
        //pour qu'ils soient au courant.
        addLien(p->addLien(a, raideur));
    }
    addPoint(a);
    a = make_shared<SpherePonctuelle>(6389e3/2.);
    a->setPos(QVector3D(0, 0, -6389e3));
    a->setVit(QVector3D(0, 0, 0));
    a->setParent(this);
    a->setMasse(masse()/7.);
    for (auto & p : points())
    {
        addLien(p->addLien(a, raideur));
    }
    addPoint(a);
    a = make_shared<SpherePonctuelle>();
    a->setPos(QVector3D(0, 0, 6389e3));
    a->setVit(QVector3D(0, 0, 0));
    a->setParent(this);
    a->setMasse(masse()/7.);
    for (auto & p : points())
    {
        if (p == points().at(points().size()-1))
            break;
        addLien(p->addLien(a, raideur));
    }
    addPoint(a);
    setMasse(0);
    qDebug() << liens().size();
}
