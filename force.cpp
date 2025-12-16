#include "force.h"

#include "pointMateriel.h"

Force::Force(std::shared_ptr<PointMateriel>source, QVector3D intensite)
    :_source(source), _intensite(intensite)
{

}

QVector3D Force::intensite() const
{
    return _intensite;
}
