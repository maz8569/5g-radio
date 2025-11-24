#pragma once
#include "IRlcEntity.h"
#include "IRlcSegmenter.h"
#include <deque>
#include <optional>

class RlcEntity : public IRlcEntity
{
private:
    uint32_t _lcid;
    size_t _priority;
    std::deque<std::shared_ptr<RlcSdu>> _sduBuffer;
    uint32_t _txNextSn = 0;
    size_t _currentSduOffset = 0;
    std::shared_ptr<IRlcSegmenter> _segmenter;

public:
    RlcEntity(uint32_t id, size_t priority, std::shared_ptr<IRlcSegmenter> segmenter) : _lcid(id), _priority(priority), _segmenter(std::move(segmenter)) {}
    uint32_t getLcid() const override { return _lcid; }
    size_t getPriority() const override { return _priority; }

    std::optional<TimePoint> getHeadSduCreatedAt() const override;
    size_t getBufferStatus() const override;
    void enqueueSdu(std::shared_ptr<RlcSdu> sdu) override;
    std::vector<std::shared_ptr<RlcPdu>> requestPdu(size_t grantSize) override;
    std::vector<std::shared_ptr<RlcPdu>> requestAllPdus(size_t grantSize) override;
};