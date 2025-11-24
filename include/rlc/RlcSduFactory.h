#pragma once
#include "RlcSdu.h"
#include <atomic>

class RlcSduFactory
{
private:
	std::atomic<uint32_t> _nextId{0};

public:
	RlcSduFactory() = default;

	std::shared_ptr<RlcSdu> create(BufferPtr buffer, const std::string &origin);
	std::shared_ptr<RlcSdu> create(ByteBuffer &&data, const std::string &origin);
	std::shared_ptr<RlcSdu> create(const ByteBuffer &data, const std::string &origin);
};