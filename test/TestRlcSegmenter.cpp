#include <gtest/gtest.h>
#include "rlc/RlcSegmenter.h"
#include "rlc/RlcSduFactory.h"

TEST(SegmenterTest, SinglePdu) {
	RlcSegmenter seg;
	RlcSduFactory factory;

	uint32_t sn = 0;

	auto res = seg.segment(factory.create(ByteBuffer(30, 0x11), "Test"), 100, sn);

	EXPECT_TRUE(res.pdu->isLast());
	EXPECT_EQ(res.newOffset, 0u);
}

TEST(SegmenterTest, MultiplePdu) {
	RlcSegmenter seg;
	RlcSduFactory factory;

	uint32_t sn = 10;
	auto sdu = factory.create(ByteBuffer(100, 0x11), "Test");
	auto res = seg.segment(sdu, 60, sn);
	EXPECT_EQ(res.pdu->getSequenceNumber(), 10u);
	EXPECT_FALSE(res.pdu->isLast());

	res = seg.segment(sdu, 60, sn, res.newOffset);
	EXPECT_EQ(res.pdu->getSequenceNumber(), 11u);
	EXPECT_TRUE(res.pdu->isLast());
}