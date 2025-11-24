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
    _NODISCARD virtual std::optional<TimePoint> getHeadSduCreatedAt() const = 0;
    virtual void enqueueSdu(std::shared_ptr<RlcSdu> sdu) = 0;
    virtual std::vector<std::shared_ptr<RlcPdu>> requestPdu(size_t grantSize) = 0;
    virtual std::vector<std::shared_ptr<RlcPdu>> requestAllPdus(size_t grantSize) = 0;
};