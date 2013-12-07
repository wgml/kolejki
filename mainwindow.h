#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread> //msleep
#include "System.h"
#include "advanceddialog.h"
#include "showplotswindow.h"

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
    ShowPlotsWindow * showPlots;

    int currentTick; //obecny progress symulacji

    void contSim(void);//symulacja gdy klikniety start
    void nSim(void);//symulacja, gdy n tickow do przesymulowania
    void simulate(void);//symuluje jeden tick, updatuje wykresy?
    void endSim();
    void makePlots();
    void updatePlots();
    void resetPlots();

    QVector<double> plotX, plot2Y;
    QVector< QVector<double> > plot1Y;
    unsigned plot1MaxY, totalClientsMax;

private slots:
    void on_startStopButton_clicked(void);
    void on_resetButton_clicked(void);
    void on_defaultButton_clicked(void);
    void on_advancedButton_clicked(void);
    void on_tickButton_clicked(void);
    void on_showPlotsButton_clicked(void);

public slots:
    void toogleButtonOnExit(void);

};

#endif // MAINWINDOW_H