#include "simuwindow.h"
#include "ui_simuwindow.h"

#include <QDateTime>

#include "soleil.h"
#include "terre.h"
#include "mercure.h"
#include "venus.h"
#include "gravitevisiteur.h"

using namespace std;

SimuWindow::SimuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimuWindow)
{
    ui->setupUi(this);
    _corps << make_shared<Soleil>();
    _corps << make_shared<Terre>();
    // _corps << make_shared<Mercure>();
    // _corps << make_shared<Venus>();
}

SimuWindow::~SimuWindow()
{
    delete ui;
}

void SimuWindow::on_btnGo_clicked()
{
//    for (int i = 0; i < 87.869 * 24 * 3.6; ++i)
        for (int i = 0; i < 365.25 * 24 * 3.6; ++i)
    {
        qDebug() << QDateTime(QDate(2024, 1, 1), QTime(0, 0)).addSecs(i*1000);
        tick(1000);
    }
}

void SimuWindow::tick(int temps)
{
    for (auto &c : _corps)
    {
        c->clearForces();
    }
    GraviteVisiteur::appliqueGravite(_corps);
    for (auto &c : _corps)
    {
        c->tick(temps);
    }
}

