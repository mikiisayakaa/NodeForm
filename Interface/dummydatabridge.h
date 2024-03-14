#pragma once

#include "abstractdatabridge.h"

namespace NF{

class DummyDataBridge : public AbstractDataBridge
{
public:
    DummyDataBridge(QObject* parent): AbstractDataBridge(parent) {}

    void bind() {}
};

}

