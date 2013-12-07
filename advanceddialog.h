#ifndef ADVANCEDDIALOG_H
#define ADVANCEDDIALOG_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class AdvancedDialog;
}

class AdvancedDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AdvancedDialog(QWidget *parent = 0);
    ~AdvancedDialog();

    void setDefaults(double, unsigned, unsigned, double, double, double, unsigned);

    QString getParam(unsigned);
    
private:
    Ui::AdvancedDialog *ui;

    double param1, param4, param5, param6;
    unsigned param2, param3, param7;

private slots:
    void on_resetButton_clicked();
    void setPreviousValues(void);
    void savePreviousValues(void);
};

#endif // ADVANCEDDIALOG_H
