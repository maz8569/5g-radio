#include "rlc/RlcPdu.h"

ByteBuffer RlcPdu::toBytes() const
{
	ByteBuffer buf(size());
	buf[0] = (_seqNum >> 8) & 0xFF;
	buf[1] = _seqNum & 0xFF;

	std::copy(_sharedPayload->begin() + _offset,
		_sharedPayload->begin() + _offset + _length,
		buf.begin() + Config::RLC_HEADER_SIZE);

	return buf;
}
