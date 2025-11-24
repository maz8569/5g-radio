#include "rlc/RlcSduFactory.h"
#include "common/Logger.h"

std::shared_ptr<RlcSdu> RlcSduFactory::create(BufferPtr buffer, const std::string &origin)
{
	if (!buffer || buffer->empty())
	{
		LOG("Error: RlcSduFactory::create called with empty buffer");
		return nullptr;
	}

	uint32_t id = _nextId.fetch_add(1);
	return std::shared_ptr<RlcSdu>(new RlcSdu(id, buffer, origin));
}

std::shared_ptr<RlcSdu> RlcSduFactory::create(ByteBuffer &&data, const std::string &origin)
{
	auto buffer = std::make_shared<ByteBuffer>(std::move(data));
	return create(buffer, origin);
}

std::shared_ptr<RlcSdu> RlcSduFactory::create(const ByteBuffer &data, const std::string &origin)
{
	auto buffer = std::make_shared<ByteBuffer>(data);
	return create(buffer, origin);
}
