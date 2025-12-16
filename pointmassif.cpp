#include "pointmassif.h"

#include "lienressort.h"

#include <QDebug>

using namespace std;

PointMateriel::PointMateriel()
	:_masse(0), _parent(nullptr)
{

}

void PointMateriel::tick(int temps)
{
	if (_frames.isEmpty()) return;
	auto p = _frames.last().valeur("position");
    if (_masse)
    {
		p.setValeur(force()/_masse, 2);
	}
	p.integre(temps);
	_frames << Frame();
	_frames.last().addValeur("position", p);
	while (_frames.size()>2) _frames.removeFirst();
	qDebug() << _nom << "Position : " << _frames.last().valeur("position").getValeur(0) << "Vitesse : " << _frames.last().valeur("position").getValeur(1)
			 << "Accélération :" << _frames.last().valeur("position").getValeur(2);
}

float PointMateriel::masse() const
{
    return _masse;
}

void PointMateriel::setMasse(float newMasse)
{
    _masse = newMasse;
}

QVector3D PointMateriel::pos(PointMateriel *ref) const
{
	if (_frames.isEmpty()) return QVector3D();
	QVector3D r = _frames.last().valeur("position").getValeur(0);
	return ref ? r + ref->pos() : r;
}

void PointMateriel::setPos(const QVector3D &newPos)
{
	if (_frames.isEmpty()) _frames << Frame();
	auto p = _frames.last().valeur("position");
	p.setValeur(newPos, 0);
	_frames.last().addValeur("position", p);
}

void PointMateriel::clearForces()
{
    _forces.clear();
}

void PointMateriel::addForce(const QVector3D &f)
{
    _forces << f;
}

QVector3D PointMateriel::force() const
{
    QVector3D r;
    for (const auto & f : _forces)
    {
        r += f;
    }

    return r;
}

QVector3D PointMateriel::vit(PointMateriel * ref) const
{
	if (_frames.isEmpty()) return QVector3D();
	auto r = _frames.last().valeur("position").getValeur(1);
	return ref ? r + ref->vit() : r;
}

void PointMateriel::setVit(const QVector3D &newVit)
{
	if (_frames.isEmpty()) _frames << Frame();
	auto p = _frames.last().valeur("position");
	p.setValeur(newVit, 1);
	_frames.last().addValeur("position", p);
}

QString PointMateriel::nom() const
{
    return _nom;
}

void PointMateriel::setNom(const QString &newNom)
{
    _nom = newNom;
}

PointMateriel *PointMateriel::parent() const
{
    return _parent;
}

void PointMateriel::setParent(PointMateriel *newParent)
{
    _parent = newParent;
}

QList<shared_ptr<PointMateriel> > PointMateriel::points()
{
	QList<shared_ptr<PointMateriel> >r;
    r << shared_from_this();
    return r;
}

shared_ptr<LienRessort> PointMateriel::addLien(shared_ptr<PointMateriel> point, double raideur, double amorti, double lRepos)
{
	auto lien = make_shared<LienRessort>(shared_from_this(), point, raideur, amorti, lRepos);
    _liens << lien;
    point->addLien(lien);
    return lien;
}

void PointMateriel::addLien(std::shared_ptr<LienRessort> lien)
{
    _liens << lien;
}

QList<std::shared_ptr<LienRessort> > PointMateriel::liens()
{
    return _liens;
}

QList<Frame> PointMateriel::frames() const
{
	return _frames;
}

QList<Frame> &PointMateriel::rFrames()
{
	return _frames;
}
