#pragma once
#include "BaseMacScheduler.h"

class FifoScheduler : public BaseMacScheduler
{
public:
	void sortChannels(std::vector<std::shared_ptr<IRlcEntity>>& channels) override;
};