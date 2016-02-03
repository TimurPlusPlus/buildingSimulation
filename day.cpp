#include "day.h"
#include "mainwindow.h"
#include <qdebug.h>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <QMessageBox>
#include <qalgorithms.h>
#include <QObject>



QVector<Machine> Day::getMachines() const
{
    return machines;
}

void Day::setMachines(const QVector<Machine> &value)
{
    machines = value;
}

Worker* Day::getWorker6()
{
    return &worker6;
}

void Day::setWorker6(const Worker &value)
{
    worker6 = value;
}

Worker* Day::getWorker3()
{
    return &worker3;
}

void Day::setWorker3(const Worker &value)
{
    worker3 = value;
}


Day::Day(QVector <Machine> newMachines, Worker newWorker3, Worker newWorker6)
{
    machines = newMachines;
    worker3 = newWorker3;
    worker6 = newWorker6;
}

void Day::nextCrash()
{
    for(int i = 0; i < getMachines().size(); i++)
    {
        float workTime = randExp(machines[i].getWorkMeanTime());
        machines[i].setTempWorkTime(workTime);
    }

    qSort(machines.begin(), machines.end(), lessThan);
    int i = 0;
    Machine tmpMachine;
    while(machines[0].getInactionTime() + machines[0].getWorkTime() < 15.99
          || machines[1].getInactionTime() + machines[1].getWorkTime() < 15.99
          || machines[2].getInactionTime() + machines[2].getWorkTime() < 15.99)
    {
        calculate(i);
        machines[0].setTempWorkTime(randExp(machines[0].getWorkMeanTime()));
        qSort(machines.begin(), machines.end(), lessThan);
        if(machines[0].getFinished())
            for(int j = 1; j <= 2; j++)
            {
                if(!machines[j].getFinished())
                {
                    tmpMachine = machines[j];
                    machines[j] = machines[0];
                    machines[0] = tmpMachine;
                    break;
                }
            }

        i++;
    }
}

bool Day::lessThan(const Machine &m1, const Machine &m2)
{
   // if(m1.getWorkTime() + m1.getInactionTime() < 15.99) ///НЕ ДАВАТЬ ОБРАБАтыватЬСЯ УЖЕ ОТРАБОТАВШИМ
        return (m1.getTempWorkTime() + m1.getWorkTime() + m1.getInactionTime()
                < m2.getTempWorkTime() + m2.getWorkTime() + m2.getInactionTime())
                ;
  // && !m1.getFinished() else
    //    return false;

}

void Day::calculate(int row)
{

    float workTime = getMachines()[0].getWorkTime();            //Общее время работы
    float tempWorkTime = getMachines()[0].getTempWorkTime();   //Длительность текущей работы
    float inactionTime = getMachines()[0].getInactionTime();    //Общее время простоя


    ///Прибавил время работы машины
    /// проверил

    float currentTime = workTime + inactionTime + tempWorkTime;  //День
    if(currentTime > 16)                                        //Отработал больше 16 часов
    {
        machines[0].setWorkTime(workTime + tempWorkTime - (currentTime - 16));

        tableDataCreated(row, 0, getMachines()[0].getType()); //ЗАНЕСЕНИЕ В ТАБЛИЦУ
        tableDataCreated(row, 1, QString::number(getMachines()[0].getTempWorkTime()));
        tableDataCreated(row, 2, QString::number(workTime + inactionTime));
        tableDataCreated(row, 3, QString::number(getMachines()[0].getWorkTime() + inactionTime));
        tableDataCreated(row, 8, QString::number(getMachines()[0].getWorkTime()));
        tableDataCreated(row, 9, QString::number(round(getMachines()[0].getRepairTime())));
        tableDataCreated(row, 10, QString::number(round(getMachines()[0].getInactionTime())));
        machines[0].setFinished(true);
        return;
    }
    else
    {
        machines[0].setWorkTime(workTime + tempWorkTime);

        tableDataCreated(row, 0, getMachines()[0].getType());
        tableDataCreated(row, 1, QString::number(round(getMachines()[0].getTempWorkTime())));
        tableDataCreated(row, 2, QString::number(round(workTime + inactionTime)));
        tableDataCreated(row, 3, QString::number(round(getMachines()[0].getWorkTime() + inactionTime)));
        tableDataCreated(row, 8, QString::number(round(getMachines()[0].getWorkTime())));
    }


    /// Прибавил время простоя

    float max = 0;
    for(int i = 1; i < getMachines().size(); i++)
    {
        float lastRepairTime = machines[i].getLastRepairTime();       //Время конца предыдущего ремонта
        if(lastRepairTime > currentTime && lastRepairTime > max)
        {
            max = lastRepairTime;
        }
    }

    float newInactionTime = 0;

    /// проверил
    if(max > 16)
    {
        newInactionTime = (max - currentTime) - (max - 16);
        tableDataCreated(row, 4, QString::number(round(newInactionTime)));
        machines[0].setInactionTime(inactionTime + newInactionTime); //Вычитаем всё, что вылезло
        tableDataCreated(row, 10, QString::number(round(getMachines()[0].getInactionTime())));
        machines[0].setFinished(true);
        return;
    }
    else if(max > 0)
    {
        newInactionTime = max - currentTime;
        tableDataCreated(row, 4, QString::number(round(newInactionTime)));
        machines[0].setInactionTime(inactionTime + newInactionTime);
       // tableDataCreated(row, 10, QString::number(round(getMachines()[0].getInactionTime())));
        currentTime = max;
    }



    /// Разыграл время ремонта

    float repairTempTime = randExp(machines[0].getRepairMeanTime());
    tableDataCreated(row, 5, QString::number(round(repairTempTime)));

    /// Прибавил время ремонта + время работы слесарей

    machines[0].setRepairTime(getMachines()[0].getRepairTime() + repairTempTime);
    getWorker3()->setWorkTime(getWorker3()->getWorkTime() + repairTempTime);
    getWorker6()->setWorkTime(getWorker6()->getWorkTime() + repairTempTime);
    machines[0].setLastRepairTime(currentTime + repairTempTime);
    tableDataCreated(row, 6, QString::number(round(currentTime)));

    ///ПРОВЕРИЛ

    currentTime += repairTempTime;
    if(currentTime > 16)
    {
        machines[0].setInactionTime(machines[0].getInactionTime() + repairTempTime
                                    - (currentTime - 16)); //Убавил время простоя
        machines[0].setFinished(true);
    }
    else
    {
        machines[0].setInactionTime(getMachines()[0].getInactionTime() + repairTempTime);
    }
    tableDataCreated(row, 9, QString::number(round(getMachines()[0].getRepairTime())));
    tableDataCreated(row, 7, QString::number(round(currentTime)));
    tableDataCreated(row, 10, QString::number(round(getMachines()[0].getInactionTime())));

}

void Day::tableDataCreated(int row, int col, QString value)
{
    emit onSendData(row, col, value);
}

float Day::calculateProfit()
{
   float profit = 0;
   for(int i = 0; i < 3; i++)
      profit += getMachines()[i].getWorkTime() * getMachines()[i].getProfit() -
                getMachines()[i].getInactionTime() * getMachines()[i].getLoss() -
                getMachines()[i].getRepairTime() * getWorker6()->getCost() -
                getMachines()[i].getRepairTime() * getWorker3()->getCost();
   return profit;
}


float Day::randExp(float meanTime)
{
    float y;
  //  for(int i = 0; i < 100; i++)
    //rsrand(time);
    y = 1.0 * rand() / (RAND_MAX * 1.0);
    float x = -log(y) * meanTime; //натур. логарифм.
    return x;
}

float Day::round(float number)
{
    return (int)(number * 100)/100.0;
}
