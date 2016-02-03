#ifndef DAY
#define DAY
#include <machine.h>
#include <worker.h>
#include "mainwindow.h"
#include <QVector>
#include <QObject>

class Day : public QObject{
    Q_OBJECT
    Worker worker6;
    Worker worker3;
    QVector <Machine> machines;
public:


    Machine *getBuldozer();
    void setBuldozer(const Machine &value);
    Worker *getWorker6();
    void setWorker6(const Worker &value);
    Worker *getWorker3();
    void setWorker3(const Worker &value);
    Day(Machine, Machine, Machine, Worker, Worker);
    Day(QVector <Machine>, Worker, Worker);
    void calculate(int row);
    void nextCrash();
    static bool lessThan(const Machine &m1, const Machine &m2);
    Machine *getExcavator1();
    void setExcavator1(const Machine &value);
    Machine *getExcavator2();
    void setExcavator2(const Machine &value);
    float randExp(float meanTime);
    QVector<Machine> getMachines() const;
    void setMachines(const QVector<Machine> &value);
    float round(float number);
    float calculateProfit();
signals:
    void onSendData(int row, int col, QString value);
private slots:
    void tableDataCreated(int row, int col, QString value);
};

#endif

