#include "ctkEATimeoutException_p.h"

ctkEATimeoutException::ctkEATimeoutException(long time, const QString &message)
    : ctkRuntimeException(message), duration(time)
{
}

ctkEATimeoutException::~ctkEATimeoutException()  throw(){

}

const char* ctkEATimeoutException::name() const throw() {
    return "ctkEATimeoutException";
}

ctkEATimeoutException* ctkEATimeoutException::clone() const {
    return new ctkEATimeoutException(*this);
}

void ctkEATimeoutException::rethrow() const {
    throw *this;
}