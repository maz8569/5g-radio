#pragma once
#include "BaseMacScheduler.h"

class PriorityScheduler : public BaseMacScheduler
{
public:
	void sortChannels(std::vector<std::shared_ptr<IRlcEntity>>& channels) override;
};