#pragma once
#include "rlc/RlcSdu.h"
#include "rlc/RlcPdu.h"

class IRlcEntity
{
public:
    virtual ~IRlcEntity() = default;
    _NODISCARD virtual uint32_t getLcid() const = 0;
    _NODISCARD virtual size_t getPriority() const = 0;
    _NODISCARD virtual size_t getBufferStatus() const = 0;
    virtual void enqueueSdu(RlcSdu sdu) = 0;
    virtual std::vector<RlcPdu> requestPdu(size_t grantSize) = 0;
};