#include "showplotswindow.h"
#include "ui_showplotswindow.h"

ShowPlotsWindow::ShowPlotsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowPlotsWindow)
{
    ui->setupUi(this);
}

ShowPlotsWindow::~ShowPlotsWindow()
{
    delete ui;
}
