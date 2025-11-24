#include "mac/MacEntity.h"
#include "common/Logger.h"

std::vector<std::shared_ptr<RlcPdu>> MacEntity::runTti(int tbSize)
{
    auto grants = _scheduler->runTti(_ttiCounter, tbSize, _logicalChannels);

    std::vector<std::shared_ptr<RlcPdu>> finalPdus;

    for (auto &grant : grants)
    {
        auto pdus = grant.channel->requestAllPdus(grant.grantSize);
        finalPdus.insert(finalPdus.end(),
                         std::make_move_iterator(pdus.begin()),
                         std::make_move_iterator(pdus.end()));
        LOG_TTI(_ttiCounter, "MAC: sent " + std::to_string(pdus.size()) + " PDUs from LCID " + std::to_string(grant.channel->getLcid()));
    }

    _ttiCounter++;
    return finalPdus;
}
