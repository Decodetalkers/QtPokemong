#include "mywidgets/models/pokemongmodel.h"

#include <gtest/gtest.h>

class Tst_PokeMongModel : public testing::Test
{
public:
    void SetUp() override { model = new PokeMonModel; }
    void TearDown() override
    {
        delete model;
        model = nullptr;
    }

public:
    PokeMonModel *model = nullptr;
    // PokemongIcon *obj = nullptr;
};

TEST_F(Tst_PokeMongModel, PokeMonModelTest)
{
    PokemongIcon icon;
    EXPECT_EQ(0, icon.getid());
    QList<PokemongIcon> icons = {
        PokemongIcon(),
        PokemongIcon(QVariant::fromValue(false), 1),
        PokemongIcon(QVariant::fromValue(false), 2),
    };
    QList<QString> names = {"alpha", "beta", "gamma"};
    QList<QString> namestodo = {"idea", "alpha", "beta", "gamma"};
    QList<int> tocompare = {0, 0, 1, 2};
    QList<QString> tocompare_str = {"0", "0", "1", "2"};
    model->populateData(icons, names);
    model->updateData(PokemongIcon(), "idea");
    QList<int> getids = model->get_ids();
    QList<QString> getids_str = model->get_ids_str();
    QList<QString> getnames = model->get_names();
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(getids[i], tocompare[i]);
        EXPECT_EQ(getids_str[i], tocompare_str[i]);
        EXPECT_EQ(getnames[i], namestodo[i]);
    }
}
TEST_F(Tst_PokeMongModel, PokeMonModelToVarient)
{
    QVariant::fromValue(PokemongIcon());
}
TEST_F(Tst_PokeMongModel, PokeMonModelColumnTest)
{
    EXPECT_EQ(model->columnCount(), 2);
}
