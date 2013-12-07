#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread> //msleep
#include "/home/vka/workspace/kolejki/src/System.h"
#include "advanceddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    System * s;
    AdvancedDialog * advanced;

    int currentTick; //obecny progress symulacji

    void contSim(void);//symulacja gdy klikniety start
    void nSim(void);//symulacja, gdy n tickow do przesymulowania
    void simulate(void);//symuluje jeden tick, updatuje wykresy?
    void endSim();
    void makePlots();
    void updatePlots();
    void resetPlots();

    QVector<double> plot1X;
    QVector< QVector<double> > plot1Y;
    unsigned plot1MaxY;

private slots:
    void on_startStopButton_clicked(void);
    void on_resetButton_clicked(void);
    void on_defaultButton_clicked(void);
    void on_advancedButton_clicked(void);
    void on_tickButton_clicked(void);

};

#endif // MAINWINDOW_H
