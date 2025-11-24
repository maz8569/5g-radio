#pragma once
#include "RlcPdu.h"
#include "RlcSdu.h"

struct SegmentResult {
	std::shared_ptr<RlcPdu> pdu;
	size_t newOffset;
};

class IRlcSegmenter
{
public:
	virtual ~IRlcSegmenter() = default;
	virtual SegmentResult segment(const std::shared_ptr<RlcSdu>& sdu,
		size_t maxSize, 
		uint32_t& nextSeqNum,
		size_t startOffset = 0) const = 0;
};