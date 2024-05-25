#include "ctkEABrokenBarrierException_p.h"

ctkEABrokenBarrierException::ctkEABrokenBarrierException(int idx, const QString &message)
    : ctkRuntimeException(message), index(idx)
{
}

ctkEABrokenBarrierException::~ctkEABrokenBarrierException() throw()
{
}

const char *ctkEABrokenBarrierException::name() const throw()
{
    return "ctkEABrokenBarrierException";
}

ctkEABrokenBarrierException *ctkEABrokenBarrierException::clone() const
{
    return new ctkEABrokenBarrierException(*this);
}

void ctkEABrokenBarrierException::rethrow() const
{
    throw *this;
}