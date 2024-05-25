#ifndef CTKEATIMEOUTEXCEPTION_P_H
#define CTKEATIMEOUTEXCEPTION_P_H

#include <ctkException.h>

class ctkEATimeoutException : public ctkRuntimeException
{
public:
    const long duration;

    ctkEATimeoutException(long time, const QString &msg = QString());

    ~ctkEATimeoutException() throw();

    const char* name() const throw();

    ctkEATimeoutException* clone() const;

    void rethrow() const;
};

#endif // CTKEATIMEOUTEXCEPTION_P_H
