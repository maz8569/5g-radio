#pragma once
#include "IMacScheduler.h"

class BaseMacScheduler : public IMacScheduler
{
protected:
	virtual void sortChannels(std::vector<std::shared_ptr<IRlcEntity>>& channels) = 0;

public:
	std::vector<MacGrant> runTti(int ttiNum, int tbSize, const std::vector<std::shared_ptr<IRlcEntity>>& channels) override;

};