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
        while((ticksToGo-- > 0))
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
