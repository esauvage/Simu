#include "simuwindow.h"
#include "ui_simuwindow.h"

#include <QDateTime>
#include <QThread>

#include <QFileDialog>
#include <QJsonDocument>

#include "soleil.h"
#include "terre.h"
//#include "mercure.h"
//#include "venus.h"
#include "gravitevisiteur.h"
#include "lienvisiteur.h"
#include "collisionsvisiteur.h"
#include "fabrique.h"

#include "sphereponctuelle.h"

using namespace std;

SimuWindow::SimuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimuWindow)
{
    ui->setupUi(this);
	const auto raideur = 0.2;
	const auto amorti = 0;
	auto s = make_shared<SolideMassif>();
	s->setNom("Test 4 boules");
	s->setMasse(2);
	s->setPos(QVector3D(0, 0, 0));
    s->setVit(QVector3D(2, 0, 0));
	shared_ptr<SpherePonctuelle> a = make_shared<SpherePonctuelle>(1);
	a->setPos(QVector3D(-1, 0, 0));
	a->setVit(QVector3D(0, 0.1, 0));
	a->setParent(s.get());
	a->setMasse(s->masse()/4);
	s->addPoint(a);
	auto b = make_shared<SpherePonctuelle>(1);
	b->setPos(QVector3D(1, 0, 0));
	b->setVit(QVector3D(0, -0.1, 0));
	b->setParent(s.get());
	b->setMasse(s->masse()/4);
	s->addPoint(b);
	auto c = make_shared<SpherePonctuelle>(1);
	c->setPos(QVector3D(0, 1, 0));
	c->setVit(QVector3D(0.1, 0, 0));
	c->setParent(s.get());
	c->setMasse(s->masse()/4);
	s->addPoint(c);
	auto d = make_shared<SpherePonctuelle>(1);
	d->setPos(QVector3D(0, -1, 0));
	d->setVit(QVector3D(-0.1, 0, 0));
	d->setParent(s.get());
	d->setMasse(s->masse()/4);
	s->addPoint(d);
	s->addLien(a->addLien(b, raideur, amorti, a->pos().distanceToPoint(b->pos())));
	s->addLien(b->addLien(c, raideur, amorti, b->pos().distanceToPoint(c->pos())));
	s->addLien(c->addLien(d, raideur, amorti, c->pos().distanceToPoint(d->pos())));
	s->addLien(d->addLien(a, raideur, amorti, d->pos().distanceToPoint(a->pos())));
	s->addLien(d->addLien(b, raideur, amorti, d->pos().distanceToPoint(b->pos())));
	s->addLien(c->addLien(a, raideur, amorti, c->pos().distanceToPoint(a->pos())));
	_corps << s;
    s = make_shared<SolideMassif>();
    s->setNom("Test 4 boules");
    s->setMasse(amorti);
    s->setPos(QVector3D(1, 1, 0));
    s->setVit(QVector3D(0, -2, 0));
    s->addPoint(a);
    s->addPoint(b);
    s->addPoint(c);
    s->addPoint(d);
    s->addLien(a->addLien(b, raideur, amorti, a->pos().distanceToPoint(b->pos())));
    s->addLien(b->addLien(c, raideur, amorti, b->pos().distanceToPoint(c->pos())));
    s->addLien(c->addLien(d, raideur, amorti, c->pos().distanceToPoint(d->pos())));
    s->addLien(d->addLien(a, raideur, amorti, d->pos().distanceToPoint(a->pos())));
    s->addLien(d->addLien(b, raideur, amorti, d->pos().distanceToPoint(b->pos())));
    s->addLien(c->addLien(a, raideur, amorti, c->pos().distanceToPoint(a->pos())));
    _corps << s;

    _corps << make_shared<Soleil>();
    auto terre = make_shared<Terre>();
    _corps << terre;
    // _corps << make_shared<Mercure>();
    // _corps << make_shared<Venus>();

    QGraphicsScene *scene = new QGraphicsScene();
	// const QPointF t1(terre->points().at(0)->pos().x(), terre->points().at(0)->pos().y());
	//    const QPointF t2(terre->points().at(1)->pos().x(), terre->points().at(1)->pos().y());
	//    const QLineF gTerre(t1, t2);

	for (int i = 0; i < s->points().size(); ++i) {
		const QPointF t1(s->points().at(i)->pos(s.get()).x()*100, s->points().at(i)->pos(s.get()).y()*100);
		const QPointF t2(s->points().at((i+1)%s->points().size())->pos(s.get()).x()*100, s->points().at((i+1)%s->points().size())->pos(s.get()).y()*100);
		const QLineF gTerre(t1, t2);
		_gTerre << scene->addLine(gTerre);
	}
	scene->setSceneRect(-10, -10, 20, 20);
	scene->addLine(QLineF(QPointF(10, 10), QPointF(30, 30)));
	ui->gvwTerre->setScene(scene);
	ui->gvwTerre->update();
//	ui->gvwTerre->ensureVisible(_gTerre, 10, 10);
//	ui->gvwTerre->setSceneRect(QRect(-10, -10, 20, 20));
}

SimuWindow::~SimuWindow()
{
    delete ui;
}

void SimuWindow::on_btnGo_clicked()
{
//    for (int i = 0; i < 87.869 * 24 * 3.6; ++i)
//    for (int i = 0; i < 365.25 * 24 * 3600; i+=1000)
    {
//        qDebug() << QDateTime(QDate(2024, 1, 1), QTime(0, 0)).addSecs(i);
		tick(1);
        update();
//		QObject().thread()->usleep(10000);
    }
}

void SimuWindow::tick(int temps)
{
    for (auto &c : _corps)
    {
        c->clearForces();
	}
	GraviteVisiteur::appliqueGravite(_corps);
	LienVisiteur::appliqueLien(_corps, temps);
    for (auto &c : _corps)
    {
        c->tick(temps);
    }
	CollisionsVisiteur::detecte(_corps);
	auto s = _corps.last();
	for (int i = 0; i < s->points().size(); ++i) {
		const QPointF t1(s->points().at(i)->pos(s.get()).x()*100, s->points().at(i)->pos(s.get()).y()*100);
		const QPointF t2(s->points().at((i+1)%s->points().size())->pos(s.get()).x()*100, s->points().at((i+1)%s->points().size())->pos(s.get()).y()*100);
		const QLineF gTerre(t1, t2);
		_gTerre[i]->setLine(gTerre);
	}
//	 ui->gvwTerre->ensureVisible(_gTerre);
    ui->gvwTerre->update();
}

void SimuWindow::createPopulation(int size)
{
    _population.clear();
    for (; _population.size()< size;)
    {
		double raideur = 10^(rand()%30 - 15);
		double amorti = 10^(rand()%30 - 15);
		double tension = rand()/(double)RAND_MAX;
		_population << QList<Chromosome>({Chromosome({raideur, amorti, tension})});
    }
}


void SimuWindow::on_actionOuvrir_triggered()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier de description JSON"), "/.", tr("Fichiers JSON (*.json)"));
    QFile file_obj(fileName);
    if (!file_obj.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open "<< fileName;
        return;
    }

    QTextStream file_text(&file_obj);
    auto json_string = file_text.readAll();
    file_obj.close();
	auto jsonDoc = QJsonDocument::fromJson(json_string.toLocal8Bit());
	_corps = Fabrique::fromJson(jsonDoc);
}

