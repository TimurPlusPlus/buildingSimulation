
#include "worker.h"


QString Worker::getWorkerType()
{
    return (QString)type;
}

float Worker::getWorkTime() const
{
    return workTime;
}

void Worker::setWorkTime(float value)
{
    workTime = value;
}

void Worker::setWorkerType(workerType newWorkerType)
{
    this->type = newWorkerType;
}

float Worker::getCost()
{
    return this->cost;
}

void Worker::setCost(float newCost)
{
    this->cost = newCost;
}



Worker::Worker(workerType newWorkerType, float newCost)
{
    this->type = newWorkerType;
    this->cost = newCost;
    this->workTime = 0;
}

Worker::Worker()
{
    this->type = Worker::THIRD;
    this->cost = 300;
    this->workTime = 0;
}

