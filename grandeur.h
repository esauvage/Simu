#ifndef GRANDEUR_H
#define GRANDEUR_H

#include <QString>
#include <QMap>

template <typename T>
class Grandeur
{
public:
	Grandeur(const QString &nom = ""):_nom(nom) {};
	Grandeur(const QString &nom, const T &valeur, const int ordre = 0):_nom(nom) {_mOrdreValeur[ordre] = valeur;};
	void setValeur(T valeur, int ordre) {_mOrdreValeur[ordre] = valeur;};
	T getValeur(int ordre) const{
		if (!_mOrdreValeur.contains(ordre)) {
			_mOrdreValeur[ordre] = T();//Si on n'a pas cette valeur, on la construit par défaut.
		}
		return _mOrdreValeur[ordre];
	};
	void integre(int dt, int ordre = 0){
		auto ordres = _mOrdreValeur.keys();
		auto minMax = std::minmax_element(ordres.begin(), ordres.end());
		for (auto i = *(minMax.second); i > qMax(ordre, *(minMax.first)); --i)
		{
			setValeur(getValeur(i) * dt + getValeur(i-1), i-1);
		}
	};
private:
	QMap<int, T> _mOrdreValeur;
	QString _nom;
};

#endif // GRANDEUR_H
