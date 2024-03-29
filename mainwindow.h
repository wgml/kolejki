#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "System.h"
#include "advanceddialog.h"

namespace Ui {
class MainWindow;
}

class QTimer;

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
    QTimer * timer;

    int currentTick; //obecny progres symulacji

    void contSim(void);//symulacja gdy klikniety start
    void nSim(void);//symulacja, gdy n tickow do przesymulowania

    void endSim();
    void makePlots();
    void updatePlots();
    void resetPlots();

    QVector<double> plotX, plot2Y, plot4Y, plot5Y;
    QVector< QVector<double> > plot1Y;
    unsigned plot1MaxY, totalClientsMax;

    QCustomPlot * p1, * p2, * p3, * p4, *p5;

private slots:
    void on_startStopButton_clicked(void);
    void on_resetButton_clicked(void);
    void on_defaultButton_clicked(void);
    void on_advancedButton_clicked(void);
    void on_tickButton_clicked(void);
    void updateParams(void);
    void generatePlot(int);
    void showHelp(void);

    void simulate(void);//symuluje jeden tick, updatuje wykresy?

    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
