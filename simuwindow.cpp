#include "simuwindow.h"
#include "ui_simuwindow.h"

#include <QDateTime>
#include <QThread>

#include <QFileDialog>

#include "soleil.h"
#include "terre.h"
#include "mercure.h"
#include "venus.h"
#include "gravitevisiteur.h"
#include "lienvisiteur.h"

using namespace std;

SimuWindow::SimuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimuWindow)
{
    ui->setupUi(this);
    _corps << make_shared<Soleil>();
    auto terre = make_shared<Terre>();
    _corps << terre;
    // _corps << make_shared<Mercure>();
    // _corps << make_shared<Venus>();

    QGraphicsScene *scene = new QGraphicsScene();
    ui->gvwTerre->setScene(scene);
    const QPointF t1(terre->points().at(0)->pos().x(), terre->points().at(0)->pos().y());
    const QPointF t2(terre->points().at(1)->pos().x(), terre->points().at(1)->pos().y());
    const QLineF gTerre(t1, t2);
    _gTerre = ui->gvwTerre->scene()->addLine(gTerre);
    ui->gvwTerre->ensureVisible(_gTerre);
}

SimuWindow::~SimuWindow()
{
    delete ui;
}

void SimuWindow::on_btnGo_clicked()
{
//    for (int i = 0; i < 87.869 * 24 * 3.6; ++i)
    for (int i = 0; i < 365.25 * 24 * 3600; i+=1000)
    {
        qDebug() << QDateTime(QDate(2024, 1, 1), QTime(0, 0)).addSecs(i);
        tick(1000);
        update();
        QObject().thread()->usleep(100);
    }
}

void SimuWindow::tick(int temps)
{
    for (auto &c : _corps)
    {
        c->clearForces();
    }
    GraviteVisiteur::appliqueGravite(_corps);
    LienVisiteur::appliqueLien(_corps);
    for (auto &c : _corps)
    {
        c->tick(temps);
    }
    const QPointF t1(_corps.last()->points().at(0)->pos().x(), _corps.last()->points().at(0)->pos().y());
    const QPointF t2(_corps.last()->points().at(1)->pos().x(), _corps.last()->points().at(1)->pos().y());
    const QLineF gTerre(t1, t2);
    _gTerre->setLine(gTerre);
    ui->gvwTerre->ensureVisible(_gTerre);
    ui->gvwTerre->update();
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
    auto json_bytes = json_string.toLocal8Bit();
}

