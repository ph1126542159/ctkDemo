#ifndef CTKEABROKENBARRIEREXCEPTION_P_H
#define CTKEABROKENBARRIEREXCEPTION_P_H

#include <ctkException.h>

class ctkEABrokenBarrierException : public ctkRuntimeException
{
public:
    const int index;
    ctkEABrokenBarrierException(int idx, const QString &msg = QString());

    ~ctkEABrokenBarrierException() throw();

    const char *name() const throw();

    ctkEABrokenBarrierException *clone() const;

    void rethrow() const;
};

#endif /* CTKEABROKENBARRIEREXCEPTION_P_H */