#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randSeed.h"
#include <QWidget>
#include <QUrl>
#include <QDesktopServices>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->simProgressBar->setFormat("Oczekiwanie na start");
    ui->log->append(QString::fromUtf8("Załadowano UI"));

    //tworzenie menu zaawansowanych opcji
    advanced = new AdvancedDialog;

    s = NULL;
    currentTick = 0;
    ui->log->append(QString::fromUtf8("Inicjacja systemu zakończona"));

    ui->plot2->plotLayout()->insertRow(0);
    ui->plot2->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->plot2, QString::fromUtf8("Ilość klientów w czasie")));

    advanced->setDefaults(3, 8, 3, 0.7, 10, 2, 0.7, 0);

    connect(advanced, SIGNAL(accepted()),
            this, SLOT(updateParams()));

    connect(this->ui->plotChooser, SIGNAL(activated(int)),
            this, SLOT(generatePlot(int)));

    connect(this->ui->help, SIGNAL(triggered()),
            this, SLOT(showHelp()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(simulate()));

    p1 = p2 = p3 = p4 = p5 = NULL;
    makePlots();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(s != NULL)
        delete s;
    if(advanced != NULL)
        delete advanced;

    if(timer != NULL)
        delete timer;

    if(p1 != NULL)
        delete p1;
    if(p2 != NULL)
        delete p2;
    if(p3 != NULL)
        delete p3;
    if(p4 != NULL)
        delete p4;
    if(p5 != NULL)
        delete p5;
}

void MainWindow::on_startStopButton_clicked()
{
    if(currentTick == 0)
        updateParams();
    if(!ui->interactCheckbox->isChecked())
    {
        if(p1 != NULL)
            delete p1;
        if(p2 != NULL)
            delete p2;
        if(p3 != NULL)
            delete p3;
        if(p4 != NULL)
            delete p4;
        if(p5 != NULL)
            delete p5;
        p1 = p2 = p3 = p4 = NULL;
    }

    ui->log->append(ui->startStopButton->isChecked() ? "Start symulacji" : "Stop symulacji");
    /*
     *blokuje mozliwosc zmiany parametrow juz po starcie
     */
    if(!timer->isActive())
    {
        ui->queueNumBox->setDisabled(true);
        ui->ququeNumSlider->setDisabled(true);
        ui->simTimeBox->setDisabled(true);
        ui->simTimeSlider->setDisabled(true);
        ui->defaultButton->setDisabled(true);
        ui->advancedButton->setDisabled(true);
        if(!ui->interactCheckbox->isChecked())
            ui->plotChooser->setDisabled(true);
        ui->startStopButton->setText("Stop");
        ui->interactCheckbox->setDisabled(true);
        //zamyka okienko advanced, just in case
        if(advanced != NULL)
            advanced->hide();

        /*if(p1 != NULL)
            delete p1;
        if(p2 != NULL)
            delete p2;
        if(p3 != NULL)
            delete p3;
        if(p4 != NULL)
            delete p4;
        p1 = p2 = p3 = p4 = NULL;*/

        if(s == NULL)
        {
            s = new System(ui->queueNumBox->value(), ui->simTimeBox->value());
            s->setParams(3, 8, 3, 0.7, 10, 2, 0.7, 0);//TODO
            s->start();
        }
        if(ui->interactCheckbox->isChecked())
            timer->start(0);
        else
            while(currentTick < ui->simTimeBox->value())
                simulate();
    }
    else
    {
        if(ui->interactCheckbox->isChecked())
                timer->stop();
        ui->startStopButton->setText("Kontynuuj");
        ui->interactCheckbox->setEnabled(true);
        ui->plotChooser->setEnabled(true);
    }

    if(currentTick >= ui->simTimeBox->value())
        endSim();
}

void MainWindow::on_resetButton_clicked()
{
    /*
     *odblokowuje przyciski,
     *TODO zeruje wykresy
     */

    ui->queueNumBox->setDisabled(false);
    ui->ququeNumSlider->setDisabled(false);
    ui->simTimeBox->setDisabled(false);
    ui->simTimeSlider->setDisabled(false);
    ui->defaultButton->setDisabled(false);
    ui->advancedButton->setDisabled(false);
    ui->startStopButton->setDisabled(false);
    ui->tickBox->setDisabled(false);
    ui->tickButton->setDisabled(false);
    ui->startStopButton->setText("Start");
    ui->simProgressBar->setFormat("Oczekiwanie na start");
    ui->tickButton->setChecked(false);
    ui->startStopButton->setChecked(false);
    ui->plotChooser->setEnabled(false);
    ui->interactCheckbox->setEnabled(true);
    ui->plotChooser->setCurrentIndex(0);
    ui->plotChooser->setEnabled(true);
    if(s != NULL)
    {
        delete s;
        s = NULL;
    }
    currentTick = 0;
    resetPlots();

    advanced->setDefaults(3, 8, 3, 0.7, 10, 2, 0.7, 0);

    if(p1 != NULL)
    {
        delete p1;
        p1 = NULL;
    }
    if(p2 != NULL)
    {
        delete p2;
        p2 = NULL;
    }
    if(p3 != NULL)
    {
        delete p3;
        p3 = NULL;
    }
    if(p4 != NULL)
    {
        delete p4;
        p4 = NULL;
    }
    if(p5 != NULL)
    {
        delete p5;
        p5 = NULL;
    }
    ui->log->clear();
}

void MainWindow::on_defaultButton_clicked(void)
{
    ui->queueNumBox->setValue(10);
    ui->simTimeBox->setValue(10000);
    ui->log->append(QString::fromUtf8("Ustawiono wartości domyślne."));
}

void MainWindow::on_advancedButton_clicked()
{
    advanced->show();
    ui->log->append(QString::fromUtf8("Odwołano się do okna ustawień zaawansowanych..."));
}

void MainWindow::on_tickButton_clicked()
{
    if(ui->tickButton->isChecked())
    {
        ui->queueNumBox->setDisabled(true);
        ui->ququeNumSlider->setDisabled(true);
        ui->simTimeBox->setDisabled(true);
        ui->simTimeSlider->setDisabled(true);
        ui->defaultButton->setDisabled(true);
        ui->advancedButton->setDisabled(true);
        ui->startStopButton->setDisabled(true);

        if(s == NULL)
        {
            s = new System(ui->queueNumBox->value(), ui->simTimeBox->value());
            s->setParams(3, 8, 3, 0.7, 10, 2, 0.7, 0);//TODO
            s->start();
        }

        ui->log->append(QString::fromUtf8("Kliknięto sim, %1 ticków do symulacji.").arg(ui->tickBox->value()));
        unsigned ticksToGo = ui->tickBox->value();
        while((ticksToGo-- > 0) && ui->tickButton)
        {
            if(currentTick >= ui->simTimeBox->value())
                break;
            simulate();
        }
        ui->startStopButton->setEnabled(true);
        ui->tickButton->setChecked(false);
        ui->tickButton->setEnabled(true);
        ui->tickBox->setEnabled(true);
    }
    if(currentTick >= ui->simTimeBox->value())
    {
        ui->log->append(QString::fromUtf8("Symulacja osiagnęla limit ticków."));
        endSim();
    }
}

void MainWindow::simulate()
{
    if(ui->simTimeBox->value() == currentTick)
    {
        ui->log->append(QString::fromUtf8("Symulacja osiagnęła limit ticków"));
        endSim();
        return;
    }

    if(s == NULL)
    {
        ui->log->append(QString::fromUtf8("System nie został prawidłowo zainicjowany"));
        return;
    }

    currentTick++;
    ui->log->append(QString("Symulacja ticka %1").arg(currentTick));
    s->simulate();
    ui->simProgressBar->setValue(100. * currentTick / ui->simTimeBox->value());
    ui->simProgressBar->setFormat(QString("Postep symulacji: %p% (%1/%2)").arg(currentTick).arg(ui->simTimeBox->value()));

    /*if(currentTick == 1)
        makePlots();*/
    if((currentTick % 100 == 0 || (ui->tickButton->isChecked())) || (timer->isActive() && (currentTick % 20 == 0)))
        updatePlots();

    plotX[currentTick] = currentTick;
    plot2Y[currentTick] = 0;

    for(int i = 0; i < ui->queueNumBox->value(); i++)
    {
        plot2Y[currentTick] += s->getQueueLength(i);
        plot1Y[i][currentTick] = s->getQueueLength(i);
    }
    plot4Y[currentTick] = 0;
    for(int i = 0; i < ui->queueNumBox->value(); i++)
        plot4Y[currentTick] += s->getQueueTime(i);

    int bakNum;
    plot4Y[currentTick] = 1.0 * plot4Y[currentTick] / (((bakNum = s->numWorkingQueues()) != 0) ? bakNum : 1);

    plot5Y[currentTick] = s->numWorkingQueues();
}

void MainWindow::endSim()
{
    /*
     *konczy symulacje.
     *blokuje odp. przyciski
     */
    if(timer->isActive())
        timer->stop();

    ui->queueNumBox->setDisabled(true);
    ui->ququeNumSlider->setDisabled(true);
    ui->simTimeBox->setDisabled(true);
    ui->simTimeSlider->setDisabled(true);
    ui->defaultButton->setDisabled(true);
    ui->advancedButton->setDisabled(true);
    ui->startStopButton->setDisabled(true);
    ui->tickBox->setDisabled(true);
    ui->tickButton->setDisabled(true);
    ui->resetButton->setEnabled(true);
    ui->plotChooser->setEnabled(true);
    ui->interactCheckbox->setDisabled(true);
    ui->log->append(QString::fromUtf8("Zakończono symulację"));
    ui->simProgressBar->setFormat(QString::fromUtf8("Symulacja zakończona"));
    updatePlots();
}

void MainWindow::makePlots()
{
    if(p1 != NULL)
        delete p1;
    if(p2 != NULL)
        delete p2;
    if(p3 != NULL)
        delete p3;
    if(p4 != NULL)
        delete p4;
    if(p5 != NULL)
        delete p5;

    p1 = p2 = p3 = p4 = p5 = NULL;

    plotX.clear();
    plot1Y.clear();
    for(int i = 0; i < plot1Y.size(); i++)
    {
        plot1Y[i].clear();
    }
    plot2Y.clear();
    plot4Y.clear();
    plot5Y.clear();
    ui->log->append(QString::fromUtf8("Odpalanie plotów"));
    plotX = QVector<double>(ui->simTimeBox->value() + 1);
    plotX[0] = 0;
    plot1Y = QVector< QVector<double> >(ui->queueNumBox->value());

    for(int i = 0; i < ui->queueNumBox->value(); i++)
    {
        plot1Y[i] = (QVector<double>(ui->simTimeBox->value() + 1));
        plot1Y[i][0] = 0;
    }

    plot2Y = QVector<double>(ui->simTimeBox->value() + 1);
    plot2Y[0] = 0;
    plot4Y = QVector<double>(ui->simTimeBox->value() + 1);
    plot4Y[0] = 0;

    plot5Y = QVector<double>(ui->simTimeBox->value() + 1);
    plot5Y[0] = 0;

    ui->plot2->addGraph();
    ui->plot2->graph(0)->setData(plotX, plot2Y);
    ui->plot2->xAxis->setLabel("Tick");
    ui->plot2->yAxis->setLabel("Klienci w kolejkach");
    ui->plot2->xAxis->setRange(0, 1);
    ui->plot2->yAxis->setRange(0, 1);
    ui->plot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot2->replot();

    plot1MaxY = 0;
    totalClientsMax = 0;
}

void MainWindow::updatePlots(void)
{
    plotX[currentTick] = currentTick;
    plot2Y[currentTick] = 0;
    for(int i = 0; i < ui->queueNumBox->value(); i++)
    {
        unsigned len = s->getQueueLength(i);
        plot1Y[i][currentTick] = len;
        plot2Y[currentTick] += len;
        if(plot1MaxY < len)
            plot1MaxY = len;
    }

    ui->plot2->graph(0)->setData(plotX, plot2Y);
    if(plot2Y[currentTick] > totalClientsMax)
        totalClientsMax = plot2Y[currentTick];

    ui->plot2->xAxis->setRange(0, currentTick);
    ui->plot2->yAxis->setRange(0, totalClientsMax + 1);
    ui->plot2->replot();

    unsigned curTick;
    if(currentTick != 0)
        curTick = currentTick;
    else if(s != NULL)
        curTick = s->getCurrentTIck();
    else
        curTick = 1;

    if(p1 != NULL && p1->isHidden())
    {
        delete p1;
        p1 = NULL;
    }
    if(p2 != NULL && p2->isHidden())
    {
        delete p2;
        p2 = NULL;
    }
    if(p3 != NULL && p3->isHidden())
    {
        delete p3;
        p3 = NULL;
    }
    if(p4 != NULL && p4->isHidden())
    {
        delete p4;
        p4 = NULL;
    }
    if(p5 != NULL && p5->isHidden())
    {
        delete p5;
        p4 = NULL;
    }

    if(p1 != NULL)
    {
        for(int i = 0; i < ui->queueNumBox->value(); i++)
        {
            p1->graph(i)->setData(plotX, plot1Y[i]);
        }
        p1->xAxis->setRange(0, curTick);
        p1->yAxis->setRange(0, plot1MaxY);
        p1->replot();
    }

    if(p2 != NULL)
    {
        p2->graph(0)->setData(plotX, plot2Y);
        p2->xAxis->setRange(0, curTick);
        p2->yAxis->setRange(0, totalClientsMax);
        p2->replot();
    }

    if(p3 != NULL)
    {
        QVector<double> p3Y(curTick + 1);
        for(int i = 0; i <= curTick; i++)
            p3Y[i] = (1. * plot2Y[i]) / ui->queueNumBox->value();

        p3->graph(0)->setData(plotX, p3Y);
        p3->xAxis->setRange(0, curTick);
        p3->yAxis->setRange(0, (1. * totalClientsMax) / ui->queueNumBox->value());
        p3->replot();
    }

    if(p4 != NULL)
    {
        p4->graph(0)->setData(plotX, plot4Y);
        p4->xAxis->setRange(0, curTick);
        {
           double max = 0;
           for(unsigned i = 0; i < plot4Y.size(); i++)
                if(max < plot4Y[i])
                    max = plot4Y[i];

            p4->yAxis->setRange(0, max);
        }
        p4->replot();
    }

    if(p5 != NULL)
    {
        p5->graph(0)->setData(plotX, plot5Y);
        p5->xAxis->setRange(0, curTick);
        p5->replot();
    }
}

void MainWindow::resetPlots()
{
    makePlots();
}

void MainWindow::updateParams()
{
    double p1, p4, p5, p6, p7;
    unsigned p2, p3, p8;

    p1 = advanced->getParam(1).toDouble();
    p2 = advanced->getParam(2).toUInt();
    p3 = advanced->getParam(3).toUInt();
    p4 = advanced->getParam(4).toDouble();
    p5 = advanced->getParam(5).toDouble();
    p6 = advanced->getParam(6).toDouble();
    p7 = advanced->getParam(7).toDouble();
    p8 = advanced->getParam(8).toUInt();

    ui->log->append(QString::fromUtf8("Otrzymano parametry: %1, %2, %3, %4, %5, %6, %7, %8.")
                    .arg(p1).arg(p2).arg(p3).arg(p4).arg(p5).arg(p6).arg(p7).arg(p8));

    if(s == NULL)
    {
        s = new System(ui->queueNumBox->value(), ui->simTimeBox->value());
        s->start();
    }
    s->setParams(p1, p2, p3, p4, p5, p6, p7, p8);

    plotX = QVector<double>(ui->simTimeBox->value() + 1);
    plot2Y = QVector<double>(ui->simTimeBox->value() + 1);
    plot4Y = QVector<double>(ui->simTimeBox->value() + 1);
    plot5Y = QVector<double>(ui->simTimeBox->value() + 1);
    plot1Y = QVector< QVector<double> >(ui->queueNumBox->value());
    for(int i = 0; i < ui->queueNumBox->value(); i++)
        plot1Y[i] = QVector<double>(ui->simTimeBox->value() + 1);
    makePlots();
}

void MainWindow::generatePlot(int p)
{
    ui->log->append(QString(QString::fromUtf8("Zażądano wykresu %1")).arg(p));

    QVector<double> p3Y(ui->simTimeBox->value() + 1);

    unsigned curTick;
    if(currentTick != 0)
        curTick = currentTick;
    else if(s != NULL)
        curTick = s->getCurrentTIck();
    else
        curTick = 1;

    switch(p)
    {
    case 1: // liczba osob w kazdej kolejce
    {
        if(p1 != NULL)
            delete p1;
        p1 = new QCustomPlot;

        p1->xAxis->setLabel("Tick");
        p1->yAxis->setLabel(QString::fromUtf8("Liczba osób w kolejce"));
        for(int i = 0; i < ui->queueNumBox->value(); i++)
        {
            p1->addGraph();
            p1->graph(i)->setData(plotX, plot1Y[i]);
        }
        p1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        p1->xAxis->setRange(0, curTick);
        p1->yAxis->setRange(0, plot1MaxY);
        p1->setGeometry(QRect(100, 100, 800, 200));
        p1->setWindowTitle(QString::fromUtf8("Liczebność kolejek"));
        p1->legend->setVisible(true);
        p1->legend->setFont(QFont("Helvetica",9));
        p1->show();
    }
        break;
    case 2:
        if(p2 != NULL)
            delete p2;
        p2 = new QCustomPlot;

        p2->xAxis->setLabel("Tick");
        p2->yAxis->setLabel(QString::fromUtf8("Liczba osób w sklepie"));

        p2->addGraph();
        p2->graph(0)->setData(plotX, plot2Y);
        p2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        p2->xAxis->setRange(0, curTick);
        p2->yAxis->setRange(0, totalClientsMax);
        p2->setGeometry(QRect(100, 200, 800, 200));
        p2->setWindowTitle(QString::fromUtf8("Liczba osób w sklepie"));
        p2->show();
        break;
    case 3:
        if(p3 != NULL)
            delete p3;
        p3 = new QCustomPlot;

        p3->xAxis->setLabel("Tick");
        p3->yAxis->setLabel(QString::fromUtf8("Średnia długość kolejki"));

        for(int i = 0; i <= ui->simTimeBox->value(); i++)
            p3Y[i] = (1. * plot2Y[i]) / ui->queueNumBox->value();

        p3->addGraph();
        p3->graph(0)->setData(plotX, p3Y);
        p3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        p3->xAxis->setRange(0, curTick);
        p3->yAxis->setRange(0, (1. * totalClientsMax) / ui->queueNumBox->value());


        p3->setGeometry(QRect(100, 300, 800, 200));
        p3->setWindowTitle(QString::fromUtf8("Średnia długość kolejki"));
        p3->show();
        break;
    case 4:
        if(p4 != NULL)
            delete p4;
        p4 = new QCustomPlot;

        p4->xAxis->setLabel("Tick");
        p4->yAxis->setLabel(QString::fromUtf8("Średni czas oczekiwania w kolejce"));

        p4->addGraph();
        p4->graph(0)->setData(plotX, plot4Y);
        p4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        p4->xAxis->setRange(0, curTick);

        {
           double max = 0;
           for(unsigned i = 0; i < plot4Y.size(); i++)
                if(max < plot4Y[i])
                    max = plot4Y[i];

            p4->yAxis->setRange(0, max);
        }
        p4->setGeometry(QRect(100, 400, 800, 200));
        p4->setWindowTitle(QString::fromUtf8("Średni czas oczekiwania w kolejce"));
        p4->show();
        break;
    case 5:
        if(p5 != NULL)
            delete p5;
        p5 = new QCustomPlot;

        p5->xAxis->setLabel("Tick");
        p5->yAxis->setLabel(QString::fromUtf8("Ilość otwartych kolejek"));

        p5->addGraph();
        p5->graph(0)->setData(plotX, plot5Y);
        p5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        p5->xAxis->setRange(0, curTick);
        p5->yAxis->setRange(0, ui->queueNumBox->value() + 1);
        p5->setGeometry(100, 500, 800, 200);
        p5->setWindowTitle(QString::fromUtf8("Ilość otwartych kolejek"));
        p5->show();
        break;
    default:
        break;
    }
}

void MainWindow::showHelp()
{
    ui->log->append(QString::fromUtf8("Ładowanie pliku pomocy."));
    QDesktopServices::openUrl(QUrl("help.pdf", QUrl::TolerantMode));
}
