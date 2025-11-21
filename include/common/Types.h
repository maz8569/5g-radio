#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <chrono>

using byte_t = std::uint8_t;
using ByteBuffer = std::vector<byte_t>;
using BufferPtr = std::shared_ptr<ByteBuffer>;
using TimePoint = std::chrono::steady_clock::time_point;

struct Config
{
	static constexpr std::size_t RLC_HEADER_SIZE = 2;
};