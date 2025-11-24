#include <iostream>
#include "rlc/RlcSegmenter.h"
#include "rlc/RlcEntity.h"
#include "channel/Channel.h"
#include "rlc/RlcSduFactory.h"
#include "mac/MacEntity.h"
#include "mac/PriorityScheduler.h"
#include "mac/FifoScheduler.h"

int main()
{
	auto segmenter = std::make_shared<RlcSegmenter>();
	auto rlc1 = std::make_shared<RlcEntity>(1, 1, segmenter);
	auto rlc2 = std::make_shared<RlcEntity>(2, 10, segmenter);

	std::vector<std::shared_ptr<IRlcEntity>> channels = {rlc1, rlc2};

	ByteBuffer data1(100, 0xAA);
	ByteBuffer data2(200, 0xBB);

	rlc1->enqueueSdu(RlcSduFactory().create(data1, "Test1"));
	rlc2->enqueueSdu(RlcSduFactory().create(data2, "Test2"));

	MacEntity macPriority(std::make_shared<PriorityScheduler>());
	macPriority.addLogicalChannel(rlc1);
	macPriority.addLogicalChannel(rlc2);

	MacEntity macFifo(std::make_shared<FifoScheduler>());
	macFifo.addLogicalChannel(rlc1);
	macFifo.addLogicalChannel(rlc2);

	Channel channel(0.2, 1, 5);

	auto runSimulation = [&](MacEntity &mac)
	{
		for (int tti = 0; tti < 10; ++tti)
		{
			auto pdus = mac.runTti(150);
			channel.transmit(tti, pdus);
		}
	};

	runSimulation(macPriority);
	runSimulation(macFifo);
}