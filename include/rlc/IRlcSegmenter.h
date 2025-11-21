#pragma once
#include "RlcPdu.h"
#include "RlcSdu.h"

class IRlcSegmenter
{
public:
	virtual ~IRlcSegmenter() = default;
	virtual std::vector<RlcPdu> segment(const std::shared_ptr<RlcSdu>& sdu, 
		size_t maxSize, 
		uint32_t& nextSeqNum,
		size_t startOffset = 0) const = 0;
};