#ifndef POINTMASSIF_H
#define POINTMASSIF_H

#include <QVector3D>
#include <QList>

#include "frame.h"

class LienRessort;

class PointMateriel : public std::enable_shared_from_this<PointMateriel>
{
public:
    PointMateriel();
    virtual void tick(int temps);
    float masse() const;
    void setMasse(float newMasse);

	QVector3D pos(PointMateriel *ref = nullptr) const;
    void setPos(const QVector3D &newPos);

    virtual void clearForces();
    void addForce(const QVector3D &f);
    QVector3D force() const;
	QVector3D vit(PointMateriel *ref = nullptr) const;
    void setVit(const QVector3D &newVit);

    QString nom() const;
    void setNom(const QString &newNom);

    PointMateriel *parent() const;
    void setParent(PointMateriel *newParent);
    virtual QList <std::shared_ptr<PointMateriel> > points();

	std::shared_ptr<LienRessort> addLien(std::shared_ptr<PointMateriel> point, double raideur, double amorti = 0, double lRepos = 0);
    void addLien(std::shared_ptr<LienRessort> lien);
    QList<std::shared_ptr<LienRessort> > liens();

	QList<Frame> frames() const;
protected:
	QList<Frame> &rFrames();
private:
    QString _nom;
    QList<QVector3D> _forces;
    QList<std::shared_ptr<LienRessort> > _liens;
    float _masse;
    PointMateriel * _parent;
	QList <Frame> _frames;
};

#endif // POINTMASSIF_H
