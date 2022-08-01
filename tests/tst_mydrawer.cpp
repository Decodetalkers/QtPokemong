#include "mywidgets/mydrawer.h"
#include <gtest/gtest.h>

class Tst_Drawer : public testing::Test
{
public:
    void SetUp() override { obj = new MyDrawer; }
    void TearDown() override
    {
        delete obj;
        obj = nullptr;
    }

public:
    MyDrawer *obj = nullptr;
};

TEST_F(Tst_Drawer, DrawerTest)
{
    // kill 10 life should get 90
    obj->openDrawer();
    obj->closeDrawer();
}
