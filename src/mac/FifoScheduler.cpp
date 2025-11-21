#include "mac/FifoScheduler.h"
#include <algorithm>

void FifoScheduler::sortChannels(std::vector<std::shared_ptr<IRlcEntity>>& channels)
{
    std::sort(channels.begin(), channels.end(),
        [](auto& a, auto& b)
        {
            return a->getHeadSduCreatedAt() < b->getHeadSduCreatedAt();
        });
}
