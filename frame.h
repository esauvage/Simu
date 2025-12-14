#ifndef FRAME_H
#define FRAME_H

#include <QList>
#include <QVector3D>
#include "grandeur.h"

class Frame
{
public:
	Frame();
	void addValeur(const QString & nom, const Grandeur<QVector3D> & v);
	Grandeur<QVector3D> valeur(const QString & nom) const;
private:
	int _temps;
	QMap<QString, Grandeur<QVector3D> >_valeurs;
};

#endif // FRAME_H
