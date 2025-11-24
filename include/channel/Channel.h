#pragma once
#include <random>
#include "rlc/RlcPdu.h"

class Channel {
private:
    double _lossProb;
    int _minDelay;
    int _maxDelay;

    std::mt19937 _rng;
    std::uniform_real_distribution<double> _uniform;
    std::uniform_int_distribution<int> _delayDist;

public:
    Channel (double lossProb, int minDelay, int maxDelay):
        _lossProb(lossProb), _minDelay(minDelay), _maxDelay(maxDelay), _rng(std::random_device{}()), _uniform(0.0, 1.0), _delayDist(minDelay, maxDelay) { }

    void transmit(int tti, const std::vector<std::shared_ptr<RlcPdu>>& pdus);
};