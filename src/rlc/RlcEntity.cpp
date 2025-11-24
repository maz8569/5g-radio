#include "rlc/RlcEntity.h"
#include "common/Logger.h"

size_t RlcEntity::getBufferStatus() const
{
	size_t total = 0;

	if (_sduBuffer.empty())
		return 0;

	total += _sduBuffer.front()->size() - _currentSduOffset;
	for (size_t i = 1; i < _sduBuffer.size(); ++i)
		total += _sduBuffer[i]->size();

	return total;
}

void RlcEntity::enqueueSdu(std::shared_ptr<RlcSdu> sdu)
{
	_sduBuffer.push_back(std::move(sdu));
	LOG("RLCEntity LCID " + std::to_string(_lcid) + " enqued sdu current buffer size " + std::to_string(_sduBuffer.size()));
}

std::vector<std::shared_ptr<RlcPdu>> RlcEntity::requestPdu(size_t grantSize)
{
	std::vector<std::shared_ptr<RlcPdu>> pdus;
	size_t remainingGrant = grantSize;

	while (!_sduBuffer.empty() && remainingGrant > Config::RLC_HEADER_SIZE)
	{
		auto r = _segmenter->segment(_sduBuffer.front(),
									 remainingGrant,
									 _txNextSn,
									 _currentSduOffset);

		if (!r.pdu) break;
		size_t size = Config::RLC_HEADER_SIZE + r.pdu->getPayloadSize();
		if (size > remainingGrant) break;

		pdus.push_back(r.pdu);
		remainingGrant -= size;

		_currentSduOffset = r.newOffset;
		if (_currentSduOffset == 0)
			_sduBuffer.pop_front();
	}

	return pdus;
}

std::vector<std::shared_ptr<RlcPdu>> RlcEntity::requestAllPdus(size_t grantSize)
{
	std::vector<std::shared_ptr<RlcPdu>> allPdus;

	while (!_sduBuffer.empty()) {
		auto pdus = requestPdu(grantSize);
		if (pdus.empty()) break;
		allPdus.insert(allPdus.end(), pdus.begin(), pdus.end());
	}

	return allPdus;
}

std::optional<TimePoint> RlcEntity::getHeadSduCreatedAt() const
{
	if (_sduBuffer.empty())
		return std::nullopt;
	return _sduBuffer.front()->createdAt();
}
