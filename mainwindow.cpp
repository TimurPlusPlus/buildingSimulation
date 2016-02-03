#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include "worker.h"
#include <QString>
#include "day.h"
#include <cstdlib>
#include <qdebug.h>
#include <iomanip>
#include <QMessageBox>
#include <qregexp.h>

bool MainWindow::getBoth() const
{
    return both;
}

void MainWindow::setBoth(bool value)
{
    both = value;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->listWidget->clear();
    if(!checkNum())
    {
        QMessageBox::information(0, "Ошибка ", "Введите числовые значения");
        return;
    }

    float excavatorMeanWorkTime = ui->line_AvgExcavatorWorkTime->text().toFloat();
    float excavatorProfit = ui->line_ExcavatorProfit->text().toFloat();
    float excavatorLoss = ui->line_ExcavatorLoss->text().toFloat();
    float excavatorRepairMeanTime = ui->lineEdit_ExcavatorRepairMeanTime->text().toFloat(); //
    float excavatorRepairMeanTimeAlone = ui->lineEdit_12->text().toFloat();
    float buldozerMeanWorkTime = ui->line_AvgBuldozerWorkTime->text().toFloat();
    float buldozerProfit = ui->line_BuldozerProfit->text().toFloat();
    float buldozerLoss = ui->line_BuldozerLoss->text().toFloat();
    float buldozerRepairMeanTime = ui->line_BuldozerRepairMeanTime->text().toFloat(); //
    float buldozerRepairMeanTimeAlone = ui->lineEdit_11->text().toFloat();
    float worker6Cost = ui->lineEdit_9->text().toFloat();
    float worker3Cost = ui->lineEdit_10->text().toFloat();

    float profitBoth = 0;
    float profitAlone = 0;

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(99);


    for(int kkk = 0; kkk < 100; kkk++)
    {

        profitBoth += preparationOfWork(excavatorMeanWorkTime, excavatorProfit, excavatorLoss,
                                        excavatorRepairMeanTime, buldozerMeanWorkTime,
                                        buldozerProfit, buldozerLoss, buldozerRepairMeanTime,
                                        worker6Cost, worker3Cost);

        profitAlone += preparationOfWork(excavatorMeanWorkTime, excavatorProfit, excavatorLoss,
                                        excavatorRepairMeanTimeAlone, buldozerMeanWorkTime,
                                        buldozerProfit, buldozerLoss, buldozerRepairMeanTimeAlone,
                                        worker6Cost, 0);
        ui->progressBar->setValue(kkk);

    }

    profitBoth /= 100.0;
    profitAlone /= 100.0;
    QString result;
    profitAlone > profitBoth? result = "Уволить :(" : result = "Оставить как есть!";
    QMessageBox::information(this, "Result", QString::number(profitBoth) +
                             " VS " + QString::number(profitAlone) + "\n" + result);

}

float MainWindow::preparationOfWork(float excavatorMeanWorkTime, float excavatorProfit,float excavatorLoss,
                        float excavatorRepairMeanTime, float buldozerMeanWorkTime,
                        float buldozerProfit, float buldozerLoss, float buldozerRepairMeanTime,
                        float worker6Cost, float worker3Cost)
{
    Machine excavator1 ("EXCAVATOR1", excavatorProfit, excavatorLoss,
                        excavatorMeanWorkTime, excavatorRepairMeanTime);
    Machine excavator2 ("EXCAVATOR2", excavatorProfit, excavatorLoss,
                        excavatorMeanWorkTime, excavatorRepairMeanTime);

    Machine buldozer ("BULDOZER", buldozerProfit, buldozerLoss,
                      buldozerMeanWorkTime, buldozerRepairMeanTime);

    QVector <Machine> machines;
    machines.append(excavator1);
    machines.append(excavator2);
    machines.append(buldozer);


    Worker worker6(Worker::SIXTH, worker6Cost);
    Worker worker3(Worker::THIRD, worker3Cost);

    Day day(machines, worker3, worker6);

    QObject::connect(&day, SIGNAL(onSendData(int,int,QString)), this, SLOT(toTable(int,int,QString)));

    if(worker3Cost == 0)
        setBoth(false);
    else
        setBoth(true);

    day.nextCrash();
    return day.calculateProfit();
}

bool MainWindow::checkNum()
{
    //QRegExp reg("^([0-9]+\.?[0-9]*)");
    //QRegExp reg("^(\d+\.\d*)$");
    QRegExp reg("[^0-9]*");
    return !reg.exactMatch(ui->line_AvgBuldozerWorkTime->text());
            //&& reg.indexIn(ui->line_AvgExcavatorWorkTime->text()) != -1;
}

void MainWindow::toTable(int row, int column, QString value)
{
    QTableWidgetItem *item = new QTableWidgetItem(value);
    if(getBoth())
    {
        ui->tableWidget->setRowCount(row + 1);
        ui->tableWidget->setItem(row, column, item);

    }
    else
    {
        ui->tableWidget_2->setRowCount(row + 1);
        ui->tableWidget_2->setItem(row, column, item);
    }
}
