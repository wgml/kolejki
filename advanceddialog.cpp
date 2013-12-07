#include "advanceddialog.h"
#include "ui_advanceddialog.h"

AdvancedDialog::AdvancedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedDialog)
{
    ui->setupUi(this);

    QIntValidator * val = new QIntValidator;
    ui->seedValue->setValidator(val);
}

AdvancedDialog::~AdvancedDialog()
{
    delete ui;
}

void AdvancedDialog::setDefaults(double p1, unsigned p2, unsigned p3, double p4, double p5, double p6, unsigned p7)
{
    ui->constNewClients->setValue(p1);
    ui->constToOpen->setValue(p2);
    ui->constToClose->setValue(p3);
    ui->constChanging->setValue(p4);
    ui->normalMean->setValue(p5);
    ui->normalSTD->setValue(p6);
    ui->seedValue->setText(QString::number(p7));

    savePreviousValues();
}

void AdvancedDialog::on_resetButton_clicked()
{
    setDefaults(3, 8, 3, 0.7, 10, 2, 0);
}

void AdvancedDialog::savePreviousValues()
{
    param1 = ui->constNewClients->value();
    param2 = ui->constToOpen->value();
    param3 = ui->constToClose->value();
    param4 = ui->constChanging->value();
    param5 = ui->normalMean->value();
    param6 = ui->normalSTD->value();
    param7 = QString(ui->seedValue->text()).toInt();
}

void AdvancedDialog::setPreviousValues()
{
    ui->constNewClients->setValue(param1);
    ui->constToOpen->setValue(param2);
    ui->constToClose->setValue(param3);
    ui->constChanging->setValue(param4);
    ui->normalMean->setValue(param5);
    ui->normalSTD->setValue(param6);
    ui->seedValue->setText(QString::number(param7));
}

QString AdvancedDialog::getParam(unsigned p)
{
    switch(p)
    {
    case 1:
        return QString::number(ui->constNewClients->value());
        break;
    case 2:
        return QString::number(ui->constToOpen->value());
        break;
    case 3:
        return QString::number(ui->constToClose->value());
        break;
    case 4:
        return QString::number(ui->constChanging->value());
        break;
    case 5:
        return QString::number(ui->normalMean->value());
        break;
    case 6:
        return QString::number(ui->normalSTD->value());
        break;
    case 7:
        return QString(ui->seedValue->text());
        break;
    default:
        return QString("");
    }
}
