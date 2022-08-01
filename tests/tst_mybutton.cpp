#include "mywidgets/mybutton.h"
#include <gtest/gtest.h>

class Tst_MyButton : public testing::Test
{
public:
    void SetUp() override { obj = new MyButton; }
    void TearDown() override
    {
        delete obj;
        obj = nullptr;
    }

public:
    MyButton *obj = nullptr;
};

TEST_F(Tst_MyButton, BattleMapTest) {}
