#include "IRlcSegmenter.h"

class RlcSegmenter : public IRlcSegmenter
{
public:
	SegmentResult segment(const std::shared_ptr<RlcSdu> &sdu,
						  size_t maxSize,
						  uint32_t &nextSeqNum,
						  size_t startOffset = 0) const override;
};