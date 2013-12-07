#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sleeper.h" //wiadomo...

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->simProgressBar->setFormat("Oczekiwanie na start");
    ui->log->append("Zaladowano UI");

    //tworzenie menu zaawansowanych opcji
    advanced = new AdvancedDialog;
    showPlots = new ShowPlotsWindow;

    s = NULL;
    currentTick = 0;
    ui->log->append("Inicjacja systemu zakonczona");

    ui->plot1->plotLayout()->insertRow(0);
    ui->plot1->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->plot1, "Placeholder #1"));
    ui->plot2->plotLayout()->insertRow(0);
    ui->plot2->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->plot2, "Placeholder #2"));

}

MainWindow::~MainWindow()
{
    delete ui;
    if(s != NULL)
        delete s;
    if(advanced != NULL)
        delete advanced;

    if(showPlots != NULL)
        delete showPlots;
    //if(showPlots != NULL)


}

void MainWindow::on_startStopButton_clicked()
{
    ui->log->append(ui->startStopButton->isChecked() ? "Start symulacji" : "Stop symulacji");
    /*
     *blokuje mozliwosc zmiany parametrow juz po starcie
     */
    if(ui->startStopButton->isChecked())
    {
        ui->queueNumBox->setDisabled(true);
        ui->ququeNumSlider->setDisabled(true);
        ui->simTimeBox->setDisabled(true);
        ui->simTimeSlider->setDisabled(true);
        ui->defaultButton->setDisabled(true);
        ui->advancedButton->setDisabled(true);
        ui->startStopButton->setText("Stop");
        //zamyka okienko advanced, just in case
        advanced->hide();

        if(s == NULL)
        {
            s = new System(ui->queueNumBox->value());
            s->setParams(3, 8, 3, 0.7);//TODO
            s->start();
        }

        while(currentTick < ui->simTimeBox->value())
        {
            simulate();
        }
    }
    else
    {
        ui->startStopButton->setText("Kontynuuj");
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
    if(s != NULL)
    {
        delete s;
        s = NULL;
    }
    currentTick = 0;
    resetPlots();

    ui->log->clear();
}

void MainWindow::on_defaultButton_clicked(void)
{
    ui->queueNumBox->setValue(10);
    ui->simTimeBox->setValue(10000);
    ui->log->append("Ustawiono wartosci domyslne.");
}

void MainWindow::on_advancedButton_clicked()
{
    advanced->show();
    ui->log->append("Odwolano sie do okna ustawien zaawansowanych...");
}

void MainWindow::on_showPlotsButton_clicked()
{
    if(ui->showPlotsButton->isChecked())
    {
        showPlots->show();
        ui->log->append("Odwolano sie do okna wykresow");
    }
    else
    {
        showPlots->hide();
        ui->log->append("Zamknieto okno wykresow");
    }
    connect(showPlots, SIGNAL(rejected()),
            this, SLOT(toogleButtonOnExit()));
}

void MainWindow::toogleButtonOnExit()
{
    ui->showPlotsButton->setChecked(false);
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
            s = new System(ui->queueNumBox->value());
            s->setParams(3, 8, 3, 0.7);//TODO
            s->start();
        }

        ui->log->append(QString("Kliknieto sim, %1 tickow do symulacji.").arg(ui->tickBox->value()));
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
        ui->log->append("Symulacja osiagnela limit tickow.");
        endSim();
    }
}

void MainWindow::simulate()
{
    if(ui->simTimeBox->value() == currentTick)
    {
        ui->log->append("Symulacja osiagnela limit tickow");
        return;
    }

    if(s == NULL)
    {
        ui->log->append("System nie zostal prawidlowo zainicjowany");
        return;
    }

    currentTick++;
    ui->log->append(QString("Symulacja ticka %1").arg(currentTick));
    s->simulate();
    ui->simProgressBar->setValue(100. * currentTick / ui->simTimeBox->value());
    ui->simProgressBar->setFormat(QString("Postep symulacji: %p% (%1/%2)").arg(currentTick).arg(ui->simTimeBox->value()));

    if(currentTick == 1)
        makePlots();
    else if((currentTick % 100 == 0 || (ui->tickButton->isChecked())))
        updatePlots();
}

void MainWindow::endSim()
{
    /*
     *konczy symulacje.
     *blokuje odp. przyciski
     */
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
    ui->log->append("Zakonczono symulacje");
    ui->simProgressBar->setFormat("Symulacja zakonczona");
}

void MainWindow::makePlots()
{
    ui->log->append("Odpalanie plotow");
    plotX = QVector<double>(ui->simTimeBox->value() + 1);
    plotX[0] = 0;
    plot1Y = QVector< QVector<double> >(ui->queueNumBox->value());

    for(int i = 0; i < ui->queueNumBox->value(); i++)
    {
        plot1Y[i] = (QVector<double>(ui->simTimeBox->value() + 1));
        plot1Y[i][0] = 0;
        ui->plot1->addGraph();
        ui->plot1->graph(i)->setData(plotX, plot1Y[i]);
    }

    plot2Y = QVector<double>(ui->simTimeBox->value() + 1);
    plot2Y[0] = 0;

    ui->plot1->xAxis->setLabel("Tick");
    ui->plot1->yAxis->setLabel("Oczekujacy w kolejce");
    ui->plot1->xAxis->setRange(0, 1);
    ui->plot1->yAxis->setRange(0, 1);
    ui->plot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot1->replot();

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
        ui->plot1->graph(i)->setData(plotX, plot1Y[i]);
    }

    ui->plot2->graph(0)->setData(plotX, plot2Y);
    if(plot2Y[currentTick] > totalClientsMax)
        totalClientsMax = plot2Y[currentTick];

    ui->plot1->xAxis->setRange(0, currentTick);
    ui->plot1->yAxis->setRange(0, plot1MaxY + 1);
    ui->plot1->replot();

    ui->plot2->xAxis->setRange(0, currentTick);
    ui->plot2->yAxis->setRange(0, totalClientsMax + 1);
    ui->plot2->replot();
}

void MainWindow::resetPlots()
{
    makePlots();
}
