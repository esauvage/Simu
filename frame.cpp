#include "frame.h"

Frame::Frame() {}

void Frame::addValeur(const QString &nom, const Grandeur<QVector3D> &v)
{
	_valeurs.insert(nom, v);
}

Grandeur<QVector3D> Frame::valeur(const QString &nom) const
{
	return _valeurs.value(nom);
}
