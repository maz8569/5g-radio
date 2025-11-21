#pragma once
#include "IRlcEntity.h"
#include "IRlcSegmenter.h"
#include <deque>

class RlcEntity : public IRlcEntity
{
private:
    uint32_t _lcid;
    size_t _priority;
    std::deque<RlcSdu> _sduBuffer;
    uint32_t _txNextSn = 0;
    size_t _currentSduOffset = 0;
    std::shared_ptr<IRlcSegmenter> _segmenter;

public:
    RlcEntity(uint32_t id, size_t priority, std::shared_ptr<IRlcSegmenter> segmenter) : _lcid(id), _priority(priority), _segmenter(std::move(segmenter)) {} 
    uint32_t getLcid() const override { return _lcid; } 
    size_t getPriority() const override { return _priority; } 

    size_t getBufferStatus() const override; 
    void enqueueSdu(RlcSdu sdu) override; 
    std::vector<RlcPdu> requestPdu(size_t grantSize) override;
};