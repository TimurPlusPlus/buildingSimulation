#ifndef MACHINE
#define MACHINE
#include <QString>


class Machine
{
public:
     //enum machineType {BULDOZER, EXCAVATOR};

private:
    QString type;
    float profit;
    float loss;
    float workMeanTime; //Мат ожидание времени работы
    float repairMeanTime; //Мат ожидание времени ремонта
    int crashes;

    float workTime; //Общее отработанное время
    float inactionTime; //Общее время простоя
    float repairTime; //Общее время ремонта


    float tempWorkTime; //Время работы до ремонта
    float lastRepairTime; //Время окончания последнего ремонта

    bool finished;
public:

    float getProfit();
    void setProfit(float newProfit);
    float getLoss();
    void setLoss(float newLoss);
    Machine();
    Machine(QString newType, float newProfit, float newLoss, float newMeanTime,
           float newRepairTime);

    int getCrashes() const;
    void setCrashes(int value);
    float getWorkTime() const;
    void setWorkTime(float value);
    float getInactionTime() const;
    void setInactionTime(float value);
    float getRepairTime() const;
    void setRepairTime(float value);
    float getRepairMeanTime() const;
    void setRepairMeanTime(float value);
    float getWorkMeanTime() const;
    void setWorkMeanTime(float value);
    QString getType() const;
    void setType(QString);
    float getTempWorkTime() const;
    void setTempWorkTime(float value);
    float getLastRepairTime() const;
    void setLastRepairTime(float value);
    float getEnds() const;
    void setEnds(float value);
    bool getFinished() const;
    void setFinished(bool value);
};


#endif // MACHINE

