#include "showplotswindow.h"
#include "ui_showplotswindow.h"

ShowPlotsWindow::ShowPlotsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowPlotsWindow)
{
    ui->setupUi(this);

    connect(ui->plotChooser, SIGNAL(currentIndexChanged(int)),
            this, SLOT(plotAsker(int)));
}

ShowPlotsWindow::~ShowPlotsWindow()
{
    delete ui;
}

void ShowPlotsWindow::plotAsker(int i)
{
    if(i != 0)
        emit askForPlot(i);
}

void ShowPlotsWindow::setPlot(QCustomPlot * p)
{
    delete ui->plotWidget;
    ui->plotWidget = p;
    ui->plotWidget->replot();
    ui->plotWidget->repaint();
    ui->plotWidget->show();
}
