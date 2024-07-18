#ifndef SIMUWINDOW_H
#define SIMUWINDOW_H

#include <QMainWindow>
#include "pointmassif.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SimuWindow;
}
QT_END_NAMESPACE

class SimuWindow : public QMainWindow
{
    Q_OBJECT

public:
    SimuWindow(QWidget *parent = nullptr);
    ~SimuWindow();

private slots:
    void on_btnGo_clicked();

private:
    void tick(int temps);

    Ui::SimuWindow *ui;
    QList<std::shared_ptr<PointMassif> > _corps;
};
#endif // SIMUWINDOW_H
