#include "mywidgets/mybutton.h"
#include <QTest>
#include <gtest/gtest.h>
#include <qtestkeyboard.h>
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

TEST_F(Tst_MyButton, MyButtonTest)
{
    QTest::mouseClick(obj, Qt::LeftButton);
}
