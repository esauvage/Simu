#include "collisionsvisiteur.h"

#include <QDebug>

CollisionsVisiteur::CollisionsVisiteur() {}

void CollisionsVisiteur::detecte(QList<std::shared_ptr<PointMateriel> > &points)
{
	for (auto & p1 : points) {
		auto iPenultieme = p1->frames().size() - 2;
		if (iPenultieme < 0) continue;
		if (!p1->frames().last().valeur("position").getValeur(1).lengthSquared()) continue; // Si il ne bouge pas il ne collisionnera personne
		auto p1A = p1->frames().at(iPenultieme).valeur("position").getValeur(0);
		auto p1B = p1->frames().last().valeur("position").getValeur(0);
		//Il nous faut l'ordonnée à l'origine.
		for (auto & p2 : points) {
			if (p1 == p2) continue;
			iPenultieme = p2->frames().size() - 2;
			if (iPenultieme < 0) continue;
			auto p2A = p2->frames().at(iPenultieme).valeur("position").getValeur(0);
			auto p2B = p2->frames().last().valeur("position").getValeur(0);
			//Est-ce que les trajectoires sont coplanaires ?
			//On prend un plan, donc 3 points. Le 4ème point est coplanaire s'il est perpendiculaire à la normale à ce plan.
			auto c = QVector3D::crossProduct(p1B-p1A, p2A-p1A);//Calcul de la normale, le célèbre produit vectoriel.
			if (c.isNull()) {
				//Cas colinéaire
				if (QVector3D::dotProduct(p1B-p1A, p2B-p2A) < 0) {//Ils vont en sens invers
					qDebug() << "Sens inverse";
				}
				else {//Ils vont dans le même sens
					continue;
				}
			}
			auto isNonCoplanaire = QVector3D::dotProduct(c, p2B);
			if (isNonCoplanaire) continue;
			qDebug() << "Ca va toucher !";
		}
	}
}
