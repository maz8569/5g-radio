#include "rlc/RlcEntity.h"

size_t RlcEntity::getBufferStatus() const
{
	size_t total = 0;

	if (_sduBuffer.empty()) return 0;

	auto it = _sduBuffer.begin();
	total += it->size() - _currentSduOffset; 
	for (++it; it != _sduBuffer.end(); ++it)
		total += it->size();

	return total;
}

void RlcEntity::enqueueSdu(RlcSdu sdu)
{
	_sduBuffer.push_back(std::move(sdu));
}

std::vector<RlcPdu> RlcEntity::requestPdu(size_t grantSize)
{
	return std::vector<RlcPdu>();
}
