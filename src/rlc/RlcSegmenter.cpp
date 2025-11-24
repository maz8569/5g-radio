#include "rlc/RlcSegmenter.h"

SegmentResult RlcSegmenter::segment(const std::shared_ptr<RlcSdu> &sdu,
                                    size_t maxSize,
                                    uint32_t &nextSeqNum,
                                    size_t startOffset) const
{
    SegmentResult result;

    if (maxSize < Config::RLC_HEADER_SIZE)
        return result;

    size_t payloadLeft = sdu->size() - startOffset;
    size_t payloadSize = std::min(payloadLeft, maxSize - Config::RLC_HEADER_SIZE);

    if (payloadSize == 0)
        return result;

    bool isLast = (payloadSize == payloadLeft);

    result.pdu = std::make_shared<RlcPdu>(
        nextSeqNum++,
        sdu->getSduId(),
        sdu->getBuffer(),
        startOffset,
        payloadSize,
        isLast);

    result.newOffset = isLast ? 0 : startOffset + payloadSize;
    return result;
}
