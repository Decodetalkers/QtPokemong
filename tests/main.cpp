#include <QApplication>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    setenv("QT_QPA_PLATFORM", "offscreen", 1);

    QApplication app(argc, argv);

    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();


    return ret;
}
