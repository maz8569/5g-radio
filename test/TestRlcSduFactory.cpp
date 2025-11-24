#include <gtest/gtest.h>
#include "rlc/RlcSduFactory.h"

TEST(RlcSduFactoryTest, CreateFromPtr)
{
    ByteBuffer data(50, 0xAB);
    BufferPtr buffer = std::make_shared<ByteBuffer>(data);

    auto sdu = RlcSduFactory().create(buffer, "UnitTest");

    ASSERT_TRUE(sdu);
    EXPECT_EQ(sdu->size(), 50u);
    EXPECT_EQ(sdu->origin(), "UnitTest");
    EXPECT_EQ(*(sdu->getBuffer()), data);
    EXPECT_EQ(sdu->getSduId(), 0u);
}

TEST(RlcSduFactoryTest, RejectsEmpty)
{
    ByteBuffer emptyData;

    RlcSduFactory factory;

    auto sdu1 = factory.create(std::make_shared<ByteBuffer>(emptyData), "UnitTest");
    auto sdu2 = factory.create(ByteBuffer(), "UnitTest");
    auto sdu3 = factory.create(ByteBuffer{}, "UnitTest");

    EXPECT_FALSE(sdu1);
    EXPECT_FALSE(sdu2);
    EXPECT_FALSE(sdu3);
}

TEST(RlcSduFactoryTest, AutoIncrementsId)
{
    ByteBuffer data1(20, 0x01);
    ByteBuffer data2(30, 0x02);

    RlcSduFactory factory;

    auto sdu1 = factory.create(data1, "Test1");
    auto sdu2 = factory.create(data2, "Test2");

    ASSERT_TRUE(sdu1);
    ASSERT_TRUE(sdu2);

    EXPECT_EQ(sdu1->getSduId(), 0u);
    EXPECT_EQ(sdu2->getSduId(), 1u);
}