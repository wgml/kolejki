#ifndef SHOWPLOTSWINDOW_H
#define SHOWPLOTSWINDOW_H

#include <QDialog>
#include <qcustomplot.h>

namespace Ui {
class ShowPlotsWindow;
}

class ShowPlotsWindow : public QDialog
{
    Q_OBJECT
    QCustomPlot * plot;
    
public:
    explicit ShowPlotsWindow(QWidget *parent = 0);
    ~ShowPlotsWindow();

    void setPlot(QCustomPlot *);

private:
    Ui::ShowPlotsWindow *ui;

signals:
    void askForPlot(int);

private slots:
    void plotAsker(int);
};

#endif // SHOWPLOTSWINDOW_H
