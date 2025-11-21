#include "IRlcSegmenter.h"

class UmRlcSegmenter : public IRlcSegmenter
{
public:
	std::vector<RlcPdu> segment(const std::shared_ptr<RlcSdu>& sdu, size_t maxPduSize) const override;
};