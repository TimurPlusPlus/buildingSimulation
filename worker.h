#ifndef WORKER
#define WORKER
#include <QString>

class Worker
{
public:
     enum workerType {SIXTH, THIRD};

private:
    workerType type;
    float cost;
    float workTime;

public:
    QString getWorkerType();
    void setWorkerType(workerType newWorkerType);
    float getCost();
    void setCost(float newCost);


    Worker(workerType newWorkerType, float newCost);
    Worker();
    float getWorkTime() const;
    void setWorkTime(float value);
};


#endif // WORKER

