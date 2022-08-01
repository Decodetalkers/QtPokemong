#include "pokemengmap.h"
#include <QtTest/qtestkeyboard.h>
#include <gtest/gtest.h>
#include <qtestkeyboard.h>
class Tst_PokeMongMap : public testing::Test
{
public:
    void SetUp() override { map = new PokemonMap; }
    void TearDown() override
    {
        delete map;
        map = nullptr;
    }

public:
    PokemonMap *map = nullptr;
    // PokemongIcon *obj = nullptr;
};

TEST_F(Tst_PokeMongMap, PokeMonMapMoveTest)
{
    EXPECT_EQ(map->position(), QPoint(0, 0));

    QTest::keyPress(map, Qt::Key_D);
    EXPECT_EQ(map->position(), QPoint(1, 0));
    map->reset();

    QTest::keyPress(map, Qt::Key_Right);
    EXPECT_EQ(map->position(), QPoint(1, 0));
    map->reset();

    QTest::keyPress(map, Qt::Key_S);
    EXPECT_EQ(map->position(), QPoint(0, 1));
    map->reset();

    QTest::keyPress(map, Qt::Key_Down);
    EXPECT_EQ(map->position(), QPoint(0, 1));
    map->reset();

    QTest::keyPress(map, Qt::Key_A);
    EXPECT_EQ(map->position(), QPoint(0, 0));
    QTest::keyPress(map, Qt::Key_Left);
    EXPECT_EQ(map->position(), QPoint(0, 0));
    QTest::keyPress(map, Qt::Key_Up);
    EXPECT_EQ(map->position(), QPoint(0, 0));
    QTest::keyPress(map, Qt::Key_W);
    EXPECT_EQ(map->position(), QPoint(0, 0));

    QTest::keyPress(map, Qt::Key_D);
    QTest::keyPress(map, Qt::Key_R);
    EXPECT_EQ(map->position(), QPoint(1, 0));

    QTest::keyPress(map, Qt::Key_S);
    EXPECT_EQ(map->position(), QPoint(1, 1));

    QTest::keyPress(map, Qt::Key_W);
    EXPECT_EQ(map->position(), QPoint(1, 0));

    QTest::keyPress(map, Qt::Key_A);
    EXPECT_EQ(map->position(), QPoint(0, 0));
}
TEST_F(Tst_PokeMongMap, PokemonMapMessageTest)
{
    map->drawMessageUpdate("sandstorm");
}
TEST_F(Tst_PokeMongMap, PokemonMapDrawerTest)
{
    QTest::keyPress(map, Qt::Key_F);
}
