#include "pointmassif.h"

#include "lienressort.h"

#include <QDebug>

using namespace std;

PointMassif::PointMassif()
	:_masse(0), _parent(nullptr)
{

}

void PointMassif::tick(int temps)
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

float PointMassif::masse() const
{
    return _masse;
}

void PointMassif::setMasse(float newMasse)
{
    _masse = newMasse;
}

QVector3D PointMassif::pos(PointMassif *ref) const
{
	if (_frames.isEmpty()) return QVector3D();
	QVector3D r = _frames.last().valeur("position").getValeur(0);
	return ref ? r + ref->pos() : r;
}

void PointMassif::setPos(const QVector3D &newPos)
{
	if (_frames.isEmpty()) _frames << Frame();
	auto p = _frames.last().valeur("position");
	p.setValeur(newPos, 0);
	_frames.last().addValeur("position", p);
}

void PointMassif::clearForces()
{
    _forces.clear();
}

void PointMassif::addForce(const QVector3D &f)
{
    _forces << f;
}

QVector3D PointMassif::force() const
{
    QVector3D r;
    for (const auto & f : _forces)
    {
        r += f;
    }

    return r;
}

QVector3D PointMassif::vit(PointMassif * ref) const
{
	if (_frames.isEmpty()) return QVector3D();
	auto r = _frames.last().valeur("position").getValeur(1);
	return ref ? r + ref->vit() : r;
}

void PointMassif::setVit(const QVector3D &newVit)
{
	if (_frames.isEmpty()) _frames << Frame();
	auto p = _frames.last().valeur("position");
	p.setValeur(newVit, 1);
	_frames.last().addValeur("position", p);
}

QString PointMassif::nom() const
{
    return _nom;
}

void PointMassif::setNom(const QString &newNom)
{
    _nom = newNom;
}

PointMassif *PointMassif::parent() const
{
    return _parent;
}

void PointMassif::setParent(PointMassif *newParent)
{
    _parent = newParent;
}

QList<shared_ptr<PointMassif> > PointMassif::points()
{
    QList<shared_ptr<PointMassif> >r;
    r << shared_from_this();
    return r;
}

shared_ptr<LienRessort> PointMassif::addLien(shared_ptr<PointMassif> point, double raideur, double amorti, double lRepos)
{
	auto lien = make_shared<LienRessort>(shared_from_this(), point, raideur, amorti, lRepos);
    _liens << lien;
    point->addLien(lien);
    return lien;
}

void PointMassif::addLien(std::shared_ptr<LienRessort> lien)
{
    _liens << lien;
}

QList<std::shared_ptr<LienRessort> > PointMassif::liens()
{
    return _liens;
}

QList<Frame> PointMassif::frames() const
{
	return _frames;
}

QList<Frame> &PointMassif::rFrames()
{
	return _frames;
}
