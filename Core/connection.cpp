#include "connection.h"


NF::Connection::~Connection()
{
    delete m_connectObj;
}
