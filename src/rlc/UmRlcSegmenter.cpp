#include "rlc/UmRlcSegmenter.h"

std::vector<RlcPdu> UmRlcSegmenter::segment(const std::shared_ptr<RlcSdu>& sdu, 
    size_t maxSize, 
    uint32_t& nextSeqNum,
    size_t startOffset) const
{
    std::vector<RlcPdu> pdus;
    size_t offset = startOffset;
    const size_t payloadSize = sdu->size();
    const size_t maxPayload = maxSize - Config::RLC_HEADER_SIZE;

    while (offset < payloadSize && maxSize > 0)
    {
        size_t chunk = std::min(maxPayload, payloadSize - offset);
        bool isLast = (offset + chunk >= payloadSize);

        pdus.emplace_back(
            nextSeqNum++,
            sdu->getSduId(),
            sdu->getBuffer(),
            offset,
            chunk,
            isLast
        );

        offset += chunk;
    }

    return pdus;
}
