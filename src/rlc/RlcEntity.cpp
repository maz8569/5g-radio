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
	std::vector<RlcPdu> pdus;
	size_t remainingGrant = grantSize;

	while (!_sduBuffer.empty() && remainingGrant > 0) {
		auto& sdu = _sduBuffer.front();
		size_t sduRemaining = sdu.size() - _currentSduOffset;
		size_t maxChunk = std::min(remainingGrant, sduRemaining);

		auto chunkPdus = _segmenter->segment(std::make_shared<RlcSdu>(sdu),
			maxChunk,
			_txNextSn,
			_currentSduOffset);

		pdus.insert(pdus.end(), chunkPdus.begin(), chunkPdus.end());

		size_t sentBytes = 0;
		for (auto& pdu : chunkPdus)
			sentBytes += pdu.getPayloadSize();

		_currentSduOffset += sentBytes;
		remainingGrant -= sentBytes;

		if (_currentSduOffset >= sdu.size())
		{
			_sduBuffer.pop_front();
			_currentSduOffset = 0;
		}
	}

	return pdus;
}

std::optional<TimePoint> RlcEntity::getHeadSduCreatedAt() const
{
	if (_sduBuffer.empty()) return std::nullopt;
	return _sduBuffer.front().createdAt();
}
