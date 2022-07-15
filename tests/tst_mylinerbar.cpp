#include "mywidgets/mylinerbar.h"
#include <gtest/gtest.h>

class Tst_Table : public testing::Test
{
public:
    void SetUp() override { obj = new MyLinerBar; }
    void TearDown() override
    {
        delete obj;
        obj = nullptr;
    }

public:
    MyLinerBar *obj = nullptr;
};

TEST_F(Tst_Table, tabletest)
{
    // kill 10 life should get 90
    obj->damage(10);
    EXPECT_EQ(90, obj->life());
    // 100 is bigger than 90 ,get 0
    obj->damage(100);
    EXPECT_EQ(0, obj->life());
    // rebase get 100
    obj->rebase();
    EXPECT_EQ(100, obj->life());
}
