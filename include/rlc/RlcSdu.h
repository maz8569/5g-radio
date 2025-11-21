#pragma once
#include "common/Types.h"
#include <string>

class RlcSdu
{
    friend class RlcSduFactory;
private:
    BufferPtr _payload;
    uint32_t _sduId;
    std::string _origin;
    TimePoint _createdAt{ std::chrono::steady_clock::now() };

    RlcSdu(uint32_t id, BufferPtr ptr, const std::string& origin) : _sduId(id), _payload(std::move(ptr)), _origin(origin) {}
public:

    _NODISCARD std::size_t size() const noexcept { return _payload->size(); }
    _NODISCARD BufferPtr getBuffer() const noexcept { return _payload; }
    _NODISCARD uint32_t getSduId() const noexcept { return _sduId; }
    _NODISCARD const std::string& origin() const noexcept { return _origin; }
    _NODISCARD TimePoint createdAt() const noexcept { return _createdAt; }
};