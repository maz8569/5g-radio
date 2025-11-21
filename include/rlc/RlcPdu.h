#pragma once
#include "common/Types.h"

class RlcPdu
{
private:
    uint32_t _seqNum;
    uint32_t _sduId;
    BufferPtr _sharedPayload;
    size_t _offset;
    size_t _length;
    bool _isLast;

public:
    RlcPdu(uint32_t seq, uint32_t sduId, BufferPtr data, size_t offset, size_t len, bool last) : _seqNum(seq), _sduId(sduId), _sharedPayload(std::move(data)), _offset(offset), _length(len), _isLast(last) {}

    _NODISCARD size_t size() const noexcept { return Config::RLC_HEADER_SIZE + _length; }
    _NODISCARD uint32_t getSequenceNumber() const noexcept { return _seqNum; }
    _NODISCARD uint32_t getSduId() const noexcept { return _sduId; }
    _NODISCARD size_t getPayloadSize() const noexcept { return _length; }
    _NODISCARD bool isLast() const noexcept { return _isLast; }

    _NODISCARD ByteBuffer toBytes() const;
};
