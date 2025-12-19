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
                //Il faut caluler les 3 produits scalaires
                auto p1 = QVector3D::dotProduct(p1B-p1A, p2A-p1A);
                auto p2 = QVector3D::dotProduct(p1B-p1A, p2B-p1A);
                auto p3 = QVector3D::dotProduct(p1B-p1A, p1B-p1A);
                if (p1 > p3 && p2 > p3) {
                    continue; //Ne touche pas
                }
                if (p1 < 0 && p2 < 0) {
                    continue; //Ne touche pas
                }
                qDebug() << "Ca touche !";
			}
			auto isNonCoplanaire = QVector3D::dotProduct(c, p2B);
			if (isNonCoplanaire) continue;
            auto d = QVector3D::crossProduct(p1B-p1A, p2B-p1A);//Calcul de la normale, le célèbre produit vectoriel.
            if (QVector3D::dotProduct(c, d) > 0) continue; // Ils sont du même côté, ça ne touche pas.
            qDebug() << "Ca touche !";
            auto v3 = p1A - p2A;
            auto v1 = p1B - p1A;
            auto v2 = p2B - p2A;
            if (!v1.x()) qSwap(v1, v2);
            if (!v1.x()) qSwap(v1, v3);
            v1 /= v1.x();
            v2 /= v2.x() ? v2.x() : 1;
            v3 /= v3.x() ? v3.x() : 1;
            v2 -= v1;
            v3 -= v1;
            v2 /= v2.y() ? v2.y() : 1;
            v3 /= v3.y() ? v3.y() : 1;
            v3 -= v2;
            // auto alpha = (v3.x() + alpha * v1.x()) / v2.x();
            // auto beta = (v3.x() + alpha * v1.x()) / v2.x();// = CA.x/CD.y + &alpha;AB.x/ CD.x
		}
	}
}
