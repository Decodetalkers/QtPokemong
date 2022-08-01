#include "mywidgets/mypopupwindow.h"
#include <gtest/gtest.h>

class Tst_MyPopWindow : public testing::Test
{
public:
    void SetUp() override { obj = new MyPopWindow; }
    void TearDown() override
    {
        delete obj;
        obj = nullptr;
    }

public:
    MyPopWindow *obj = nullptr;
};

TEST_F(Tst_MyPopWindow, PopWindowTest)
{
    obj->showDialog();
    obj->hideDialog();
}
