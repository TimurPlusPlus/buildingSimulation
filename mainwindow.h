#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <machine.h>
#include <worker.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    float avgExcWorkTime;
    float avgBuldWorkTime;
    bool both;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    float round(float);
    bool checkNum();
   float preparationOfWork(float excavatorMeanWorkTime, float excavatorProfit, float excavatorLoss,
                           float excavatorRepairMeanTime, float buldozerMeanWorkTime,
                           float buldozerProfit, float buldozerLoss, float buldozerRepairMeanTime,
                           float worker6Cost, float worker3Cost);

   bool getBoth() const;
   void setBoth(bool value);

private slots:
   void on_pushButton_clicked();

public slots:
    void toTable(int row, int column, QString value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
