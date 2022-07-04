#include "linerbar.h"
#include <gtest/gtest.h>

class Tst_lifeUpdate : public testing::Test
{
public:
    void SetUp() override { obj = new Linerbar(); }
    void TearDown() override
    {
        delete obj;
        obj = nullptr;
    }

public:
    Linerbar *obj = nullptr;
};

//TEST(HelloTest, BasicAssertions)
//{
//    // Expect two strings not to be equal.
//    EXPECT_STRNE("hello", "world");
//    // Expect equality.
//    EXPECT_EQ(7 * 6, 42);
//}
TEST_F(Tst_lifeUpdate, linerbartest) 
{
	obj->lifeupdate(100);
	obj->lifeupdate(10);
}