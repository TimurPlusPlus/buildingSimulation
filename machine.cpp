#include <QString>
#include "machine.h"

int Machine::getCrashes() const
{
    return crashes;
}

void Machine::setCrashes(int value)
{
    crashes = value;
}

float Machine::getWorkTime() const
{
    return workTime;
}

void Machine::setWorkTime(float value)
{
    workTime = value;
}

float Machine::getInactionTime() const
{
    return inactionTime;
}

void Machine::setInactionTime(float value)
{
    inactionTime = value;
}

float Machine::getRepairTime() const
{
    return repairTime;
}

void Machine::setRepairTime(float value)
{
    repairTime = value;
}

float Machine::getRepairMeanTime() const
{
    return repairMeanTime;
}

void Machine::setRepairMeanTime(float value)
{
    repairMeanTime = value;
}

float Machine::getWorkMeanTime() const
{
    return workMeanTime;
}

void Machine::setWorkMeanTime(float value)
{
    workMeanTime = value;
}

QString Machine::getType() const
{
    return type;
}
//"!:

void Machine::setType(QString value)
{
    type = value;
}

float Machine::getTempWorkTime() const
{
    return tempWorkTime;
}

void Machine::setTempWorkTime(float value)
{
    tempWorkTime = value;
}

float Machine::getLastRepairTime() const
{
    return lastRepairTime;
}

void Machine::setLastRepairTime(float value)
{
    lastRepairTime = value;
}


bool Machine::getFinished() const
{
    return finished;
}

void Machine::setFinished(bool value)
{
    finished = value;
}

float Machine::getProfit()
{
    return this->profit;
}

void Machine::setProfit(float newProfit)
{
    this->profit = newProfit;
}

float Machine::getLoss()
{
    return this->loss;
}

void Machine::setLoss(float newLoss)
{
    this->loss = newLoss;
}


Machine::Machine(QString newMachineType, float newProfit, float newLoss,
                 float newMeanTime, float newRepairTime)
{
    type = newMachineType;
    profit = newProfit;
    loss = newLoss;
    workMeanTime = newMeanTime;
    repairMeanTime = newRepairTime;
    crashes = 0;
    workTime = 0;
    inactionTime = 0;
    repairTime = 0;
    tempWorkTime = 0;
    lastRepairTime = 0;
    finished = false;
}

Machine::Machine()
{
    type = "EXCAVATOR";
    profit = 500;
    loss = 500;
    workMeanTime = 6;
    repairMeanTime = 0.25;
    crashes = 0;
    workTime = 0;
    inactionTime = 0;
    repairTime = 0;
    tempWorkTime = 0;
    lastRepairTime = 0;
}

