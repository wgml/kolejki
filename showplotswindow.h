#ifndef SHOWPLOTSWINDOW_H
#define SHOWPLOTSWINDOW_H

#include <QDialog>

namespace Ui {
class ShowPlotsWindow;
}

class ShowPlotsWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShowPlotsWindow(QWidget *parent = 0);
    ~ShowPlotsWindow();
    
private:
    Ui::ShowPlotsWindow *ui;
};

#endif // SHOWPLOTSWINDOW_H
