#include "mac/PriorityScheduler.h"
#include <algorithm>

void PriorityScheduler::sortChannels(std::vector<std::shared_ptr<IRlcEntity>>& channels)
{
    std::sort(channels.begin(), channels.end(),
        [](auto& a, auto& b)
        {
            return a->getPriority() > b->getPriority();
        });
}
