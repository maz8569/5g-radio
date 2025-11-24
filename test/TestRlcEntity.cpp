#include <gtest/gtest.h>
#include "rlc/RlcEntity.h"
#include "rlc/RlcSduFactory.h"
#include "rlc/RlcSegmenter.h"

TEST(RlcEntityTest, EnqueueSingle)
{
    auto seg = std::make_shared<RlcSegmenter>();
    RlcEntity rlc(1, 1, seg);

    auto sdu = RlcSduFactory().create(ByteBuffer(100, 0x11), "Test");

    ASSERT_TRUE(sdu);

    EXPECT_EQ(rlc.getBufferStatus(), 0u);

    rlc.enqueueSdu(sdu);

    EXPECT_EQ(rlc.getBufferStatus(), 100u);
}

TEST(RlcEntityTest, EnqueueMultiple)
{
    auto seg = std::make_shared<RlcSegmenter>();
    RlcEntity rlc(1, 1, seg);

    RlcSduFactory factory;

    rlc.enqueueSdu(factory.create(ByteBuffer(20, 0x11), "Test"));
    rlc.enqueueSdu(factory.create(ByteBuffer(30, 0x11), "Test"));
    rlc.enqueueSdu(factory.create(ByteBuffer(40, 0x11), "Test"));

    EXPECT_EQ(rlc.getBufferStatus(), 20 + 30 + 40);
}

TEST(RlcEntityTest, RequestPduSingleFull)
{
    auto seg = std::make_shared<RlcSegmenter>();
    RlcEntity rlc(1, 1, seg);

    RlcSduFactory factory;
    auto sdu = factory.create(ByteBuffer(30, 0x11), "Test");

    rlc.enqueueSdu(sdu);

    auto pdus = rlc.requestPdu(100);
    ASSERT_EQ(pdus.size(), 1u);
    EXPECT_TRUE(pdus[0]->isLast());
}

TEST(RlcEntityTest, RequestPduSegmentation) {
    auto seg = std::make_shared<RlcSegmenter>();
    RlcEntity rlc(1, 1, seg);

    RlcSduFactory factory;
    auto sdu = factory.create(ByteBuffer(100, 0x11), "Test");

    rlc.enqueueSdu(sdu);

    auto pdus = rlc.requestAllPdus(40);
    ASSERT_GE(pdus.size(), 2u);

    EXPECT_FALSE(pdus[0]->isLast());
    EXPECT_TRUE(pdus.back()->isLast());
}

TEST(RlcEntityTest, MultipleSduAcrossGrants)
{

    auto seg = std::make_shared<RlcSegmenter>();
    RlcEntity rlc(1, 1, seg);

    RlcSduFactory factory;
    rlc.enqueueSdu(factory.create(ByteBuffer(40, 0x11), "Test"));
    rlc.enqueueSdu(factory.create(ByteBuffer(50, 0x11), "Test"));

    auto pdus1 = rlc.requestPdu(40);

    EXPECT_GE(pdus1.size(), 1u);
    EXPECT_EQ(rlc.getBufferStatus(), 52u);

    rlc.requestPdu(100);
    EXPECT_EQ(rlc.getBufferStatus(), 0u);
}

TEST(RlcEntityTest, ZeroGrant)
{
    auto seg = std::make_shared<RlcSegmenter>();
    RlcEntity rlc(1, 1, seg);

    RlcSduFactory factory;
    rlc.enqueueSdu(factory.create(std::make_shared<ByteBuffer>(20, 0x11), "Test"));

    auto pdus = rlc.requestPdu(0);
    EXPECT_TRUE(pdus.empty());
}