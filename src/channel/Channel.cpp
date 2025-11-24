#include "channel/Channel.h"
#include <iostream>
#include "common/Logger.h"

void Channel::transmit(int tti, const std::vector<std::shared_ptr<RlcPdu>>& pdus)
{
    if (pdus.empty())
        return;

    if (_uniform(_rng) < _lossProb)
    {
        LOG_TTI(tti, "Channel: LOST " + std::to_string(pdus.size()) + " PDUs");
        return;
    }
    int delay = _delayDist(_rng);
    LOG_TTI(tti, "Channel: DELAY " + std::to_string(pdus.size()) +
        " PDUs by " + std::to_string(delay) + " TTIs");
}
