#ifndef CTKEACYCLICBARRIER_P_H
#define CTKEACYCLICBARRIER_P_H

#include <QMutex>
#include <QWaitCondition>

class ctkEARunnable;

class ctkEACyclicBarrier
{
public:
    ctkEACyclicBarrier(int parties, ctkEARunnable *command = nullptr);

    ctkEARunnable *setBarrierCommand(ctkEARunnable *command);

    bool broken() const;

    void restar();

    int parties() const;

    int barrier();

    int attemptBarrier(long mesecs);

protected:
    int doBarrier(long timed, long msecs);

private:
    int parties_;
    int broken_;
    ctkEARunnable *barrierCommand_;
    int count_;
    int reset_;
    mutable QMutex mutex_;
    mutable QMutex monitor_;
    QWaitCondition waitCondition_;
};

#endif // CTKEACYCLICBARRIER_P_H