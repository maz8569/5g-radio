#pragma once
#include "rlc/IRlcEntity.h"

struct MacGrant
{
    std::shared_ptr<IRlcEntity> channel;
    size_t grantSize;
};

class IMacScheduler
{
public:
    virtual ~IMacScheduler() = default;
    virtual std::vector<MacGrant> runTti(
        int ttiNum,
        int tbSize,
        const std::vector<std::shared_ptr<IRlcEntity>>& channels) = 0;
};
