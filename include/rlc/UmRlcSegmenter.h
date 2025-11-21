#include "IRlcSegmenter.h"

class UmRlcSegmenter : public IRlcSegmenter
{
public:
	std::vector<RlcPdu> segment(const std::shared_ptr<RlcSdu>& sdu, 
		size_t maxSize, 
		uint32_t& nextSeqNum,
		size_t startOffset = 0) const override;
};