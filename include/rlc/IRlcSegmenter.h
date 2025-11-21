#pragma once
#include "RlcPdu.h"
#include "RlcSdu.h"

class IRlcSegmenter
{
public:
	virtual ~IRlcSegmenter() = default;
	virtual std::vector<RlcPdu> segment(const std::shared_ptr<RlcSdu>& sdu, size_t maxPduSize) const = 0;
};