#include "mac/MacEntity.h"

void MacEntity::runTti(int tbSize)
{
	auto grants = _scheduler->runTti(_ttiCounter, tbSize, _logicalChannels);

	std::vector<RlcPdu> finalPdus;

    for (auto& grant : grants) {
        auto pdus = grant.channel->requestPdu(grant.grantSize);
        finalPdus.insert(finalPdus.end(),
            std::make_move_iterator(pdus.begin()),
            std::make_move_iterator(pdus.end()));
    }

    _ttiCounter++;
}
