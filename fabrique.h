#ifndef FABRIQUE_H
#define FABRIQUE_H

#include "pointMateriel.h"
#include <QJsonDocument>

class Fabrique
{
public:
	Fabrique();
    static QList <std::shared_ptr<PointMateriel> > fromJson(QJsonDocument & jsonDoc);
};

#endif // FABRIQUE_H
