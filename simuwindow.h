#ifndef SIMUWINDOW_H
#define SIMUWINDOW_H

#include <QMainWindow>

#include <QGraphicsLineItem>
#include "pointMateriel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SimuWindow;
}
QT_END_NAMESPACE

typedef QList<double> Chromosome;

class SimuWindow : public QMainWindow
{
    Q_OBJECT

public:
    SimuWindow(QWidget *parent = nullptr);
    ~SimuWindow();

private slots:
    void on_btnGo_clicked();

    void on_actionOuvrir_triggered();

private:
    void tick(int temps);
    void createPopulation(int size);

    Ui::SimuWindow *ui;
    QList<std::shared_ptr<PointMateriel> > _corps;
    QList<Chromosome> _population;
	QList<QGraphicsLineItem *> _gTerre;
};
#endif // SIMUWINDOW_H
