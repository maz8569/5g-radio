#include "mac/BaseMacScheduler.h"

std::vector<MacGrant> BaseMacScheduler::runTti(int ttiNum, int tbSize, const std::vector<std::shared_ptr<IRlcEntity>>& channels)
{
	std::vector<std::shared_ptr<IRlcEntity>> sorted = channels;
	sortChannels(sorted);

	std::vector<MacGrant> grants;
	grants.reserve(sorted.size());

	size_t remaining = tbSize;

	for (auto& ch : sorted) {
		if (remaining == 0) break;

		size_t bs = ch->getBufferStatus();
		if (bs == 0)
			continue;

		size_t g = std::min(bs, remaining);
		grants.push_back({ ch, g });
		remaining -= g;
	}

	return grants;
}
