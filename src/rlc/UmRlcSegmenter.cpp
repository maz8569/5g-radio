#include "rlc/UmRlcSegmenter.h"

std::vector<RlcPdu> UmRlcSegmenter::segment(const std::shared_ptr<RlcSdu>& sdu, size_t maxPduSize) const
{
    std::vector<RlcPdu> pdus;
    size_t offset = 0;
    uint32_t seqNum = 0;

    while (offset < sdu->size())
    {
        size_t chunk = std::min(maxPduSize - Config::RLC_HEADER_SIZE, sdu->size() - offset);
        bool isLast = (offset + chunk >= sdu->size());
        pdus.emplace_back(seqNum++, sdu->getSduId(), sdu->getBuffer(), offset, chunk, isLast);
        offset += chunk;
    }

    return pdus;
}
