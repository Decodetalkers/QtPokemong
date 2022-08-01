#include "mywidgets/mybattlemap.h"
#include <gtest/gtest.h>

class Tst_MyBattlemap : public testing::Test
{
public:
    void SetUp() override { obj = new MyBattleMap; }
    void TearDown() override
    {
        delete obj;
        obj = nullptr;
    }

public:
    MyBattleMap *obj = nullptr;
};

TEST_F(Tst_MyBattlemap, BattleMapTest)
{
    obj->enermyAttack();
    obj->myAttack();
}
