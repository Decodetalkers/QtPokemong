#include "mywidgets/myprogress.h"
#include <gtest/gtest.h>

class Tst_Progress : public testing::Test
{
public:
    void SetUp() override { obj = new MyProgress; }
    void TearDown() override
    {
        delete obj;
        obj = nullptr;
    }

public:
    MyProgress *obj = nullptr;
};

TEST_F(Tst_Progress, ProgressTest) {}
