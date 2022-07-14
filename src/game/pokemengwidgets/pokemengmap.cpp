#include "pokemengmap.h"
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>
#include <QVBoxLayout>
const QString grass = ":/resources/grass.jpg";
const QString playerred = ":/resources/red.png";
const QColor white = QColor(255, 255, 255);
PokemonMap::PokemonMap(QWidget *parent)
    : QWidget(parent)
{
    //[0] make it can be focused by clicked
    setFocusPolicy(Qt::ClickFocus);
    mydrawer = new MyDrawer;
    mydrawer->setParent(this);
    QVBoxLayout *drawerlayout = new QVBoxLayout;
    QPushButton *exit = new QPushButton("exit");
    drawerlayout->addWidget(exit);
    mydrawer->setDrawerLayout(drawerlayout);
    connect(exit, &QPushButton::pressed, mydrawer, &MyDrawer::closeDrawer);

    qrand = QRandomGenerator::global();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&] {
        for (int i = 0; i < 16; ++i) {
            enermys[i] = {qrand->bounded(30), qrand->bounded(60)};
        }
        hasmessage = false;
    });
    timer->start(100);
    setMinimumSize(500, 500);
}

void PokemonMap::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto width = qMin(size().width() * 1 / 2, size().height());
    int startpointx = size().width() / 2 - width;
    int startpointy = size().height() / 2 - width / 2;
    int scalesize = width / 30;
    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, size().width(), size().height()), 0, 0);
    painter.setPen(QPen(Qt::black, 10));
    painter.fillPath(path, Qt::black);
    QPixmap image = QPixmap(grass).scaled(width * 2, width);
    QPixmap player = QPixmap(playerred).scaled(scalesize, scalesize);
    painter.drawPixmap(startpointx, startpointy, image);
    painter.drawPixmap(playerposition.x() * scalesize + startpointx, playerposition.y() * scalesize + startpointy, player);

    // message draw
    // it will draw a white message block on the right corner of the page
    if (hasmessage) {
        QPainterPath messagetext;
        messagetext.addRoundedRect(QRectF(size().width() - 100, 0, 100, 50), 0, 0);
        painter.setPen(QPen(white, 10));
        painter.fillPath(messagetext, white);
        painter.setPen(QPen(Qt::black, 10));
        painter.drawText(size().width() - 100, 25, message);
    }
    // painter.drawPixmap
}

void PokemonMap::drawMessageUpdate(QString weather)
{
    hasmessage = true;
    this->message = weather;
    update();
}
void PokemonMap::keyPressEvent(QKeyEvent *event)
{
    // qDebug() << "Hello";
    switch (event->key()) {
        case Qt::Key_A:
        case Qt::Key_Left: {
            if (playerposition.x() > 0) {
                playerposition.rx() -= 1;
            }
            break;
        }
        case Qt::Key_D:
        case Qt::Key_Right: {
            if (playerposition.x() <= 58) {
                playerposition.rx() += 1;
            }
            break;
        }
        case Qt::Key_W:
        case Qt::Key_Up: {
            if (playerposition.y() > 0) {
                playerposition.ry() -= 1;
            }
            break;
        }
        case Qt::Key_S:
        case Qt::Key_Down: {
            if (playerposition.y() <= 28) {
                playerposition.ry() += 1;
            }
            break;
        }
        case Qt::Key_F: {
            mydrawer->openDrawer();
        } break;
        default:
            break;
    }
    for (auto point : enermys) {
        if (playerposition == point) {
            emit MeetEnermy();
        }
    }
    update();
}
