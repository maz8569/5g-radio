#pragma once
#include "IMacScheduler.h"

class MacEntity {
private:
	std::shared_ptr<IMacScheduler> _scheduler;
	std::vector<std::shared_ptr<IRlcEntity>> _logicalChannels;
	int _ttiCounter = 0;

public:

	MacEntity(std::shared_ptr<IMacScheduler> scheduler): _scheduler(std::move(scheduler)) {}

	void addLogicalChannel(std::shared_ptr<IRlcEntity> rlc) {
		_logicalChannels.push_back(std::move(rlc));
	}

	std::vector<std::shared_ptr<RlcPdu>> runTti(int tbSize);
};