#include "mainwindow.h"
#include "mybattlemap.h"
#include "mybutton.h"
#include "mydrawer.h"
#include "mylinerbar.h"
#include "mypopupwindow.h"
#include "myprogress.h"
#include <QObject>
#include <QtWidgets>
QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QListWidget;
class QPushButton;
class QStackedLayout;
class QHBoxLayout;
QT_END_NAMESPACE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centerwidget = new QWidget;

    QHBoxLayout *layout = new QHBoxLayout;
    centerwidget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    QListWidget *list = new QListWidget;

    layout->addWidget(list);
    layout->addLayout(stack);
    layout->setStretch(1, 2);

    setCentralWidget(centerwidget);

    QVBoxLayout *center = new QVBoxLayout;
    center->addWidget(new MyButton);
    center->addWidget(new MyButton);
    center->addWidget(new MyButton);

    // buttons
    {
        list->addItem("Buttons");
        QWidget *buttoncenter = new QWidget;
        buttoncenter->setLayout(center);
        stack->addWidget(buttoncenter);
    }

    {
        list->addItem("progress");
        stack->addWidget(new MyProgress);
    }
    // drawer

    {
        list->addItem("Drawer");
        QWidget *thewidget = new QWidget;
        QVBoxLayout *mainlayout = new QVBoxLayout;
        mainlayout->addWidget(new QLabel("Drawer"));
        QPushButton *pb = new QPushButton("clicked");
        mainlayout->addWidget(pb);
        thewidget->setLayout(mainlayout);

        MyDrawer *drawer = new MyDrawer;
        drawer->setParent(thewidget);

        QVBoxLayout *drawerlayout = new QVBoxLayout;
        QPushButton *exit = new QPushButton("exit");
        drawerlayout->addWidget(exit);
        drawer->setDrawerLayout(drawerlayout);

        connect(exit, &QPushButton::pressed, drawer, &MyDrawer::closeDrawer);
        connect(pb, &QPushButton::pressed, drawer, &MyDrawer::openDrawer);
        stack->addWidget(thewidget);
    }

    // enddrawer
    // popup

    {
        list->addItem("Popup");
        QWidget *thewidget = new QWidget;
        QVBoxLayout *mainlayout = new QVBoxLayout;
        mainlayout->addWidget(new QLabel("Test"));
        QPushButton *pb = new QPushButton("clicked");
        mainlayout->addWidget(pb);

        MyPopWindow *popup = new MyPopWindow;
        popup->setParent(thewidget);

        QVBoxLayout *poplayout = new QVBoxLayout;

        QPushButton *pbpop = new QPushButton("exit");
        poplayout->addWidget(pbpop);
        popup->setWindowLayout(poplayout);

        thewidget->setLayout(mainlayout);
        connect(pb, &QPushButton::clicked, popup, &MyPopWindow::showDialog);
        connect(pbpop, &QPushButton::clicked, popup, &MyPopWindow::hideDialog);
        stack->addWidget(thewidget);
    }
    // endpopup
    {
        list->addItem("Map");
        QWidget *thewidget = new QWidget;
        QVBoxLayout *mainlayout = new QVBoxLayout;
        QHBoxLayout *buttons = new QHBoxLayout;

        QPushButton *meattack = new QPushButton("You attack");
        QPushButton *enermyattack = new QPushButton("Enermy attack");

        buttons->addWidget(meattack);
        buttons->addWidget(enermyattack);

        MyBattleMap *map = new MyBattleMap;
        mainlayout->addWidget(map);
        mainlayout->addLayout(buttons);

        thewidget->setLayout(mainlayout);

        stack->addWidget(thewidget);

        connect(meattack, &QPushButton::clicked, map, &MyBattleMap::myAttack);
        connect(enermyattack, &QPushButton::clicked, map, &MyBattleMap::enermyAttack);
    }

    {
        list->addItem("life");
        QWidget *thewidget = new QWidget;
        QVBoxLayout *mainlayout = new QVBoxLayout;
        QHBoxLayout *buttons = new QHBoxLayout;

        QPushButton *attack = new QPushButton("You attack");
        QPushButton *rebase = new QPushButton("rebase");

        buttons->addWidget(attack);
        buttons->addWidget(rebase);

        MyLinerBar *linerbar = new MyLinerBar;
        connect(attack, &QPushButton::clicked, linerbar, [=] { linerbar->damage(40); });
        mainlayout->addWidget(linerbar);
        mainlayout->addLayout(buttons);

        thewidget->setLayout(mainlayout);

        stack->addWidget(thewidget);

        connect(rebase, &QPushButton::clicked, linerbar, &MyLinerBar::rebase);
    }
    connect(list, &QListWidget::currentItemChanged, stack, [=] { stack->setCurrentIndex(list->currentRow()); });
    // QWidget *centerwidget = new QWidget;

    // centerwidget->setLayout(center);
}

MainWindow::~MainWindow() {}
